#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <MY_LIB/global_var.h>
#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <MY_LIB/cal_info.h>
#include <MY_LIB/sovle_equations.h>

static short int index_table[256] = {
    ['a'] = 0, ['b'] = 1, ['d'] = 2, ['f'] = 3, ['h'] = 4, ['i'] = 5, ['j'] = 6, ['k'] = 7, ['l'] = 8, ['m'] = 9, ['n'] = 10, ['o'] = 11, ['p'] = 12, ['q'] = 13, ['r'] = 14, ['s'] = 15, ['t'] = 16, ['u'] = 17, ['v'] = 18, ['w'] = 19, ['x'] = 20, ['y'] = 21, ['z'] = 22, ['A'] = 23, ['B'] = 24, ['C'] = 25, ['D'] = 26, ['E'] = 27, ['F'] = 28, ['G'] = 29, ['H'] = 30, ['I'] = 31, ['J'] = 32, ['K'] = 33, ['L'] = 34, ['M'] = 35, ['N'] = 36, ['O'] = 37, ['P'] = 38, ['Q'] = 39, ['R'] = 40, ['S'] = 41, ['T'] = 42, ['U'] = 43, ['V'] = 44, ['W'] = 45, ['X'] = 46, ['Y'] = 47, ['Z'] = 48};

// ======================================================================================================= //
// ======================================================================================================= //
// ======================================================================================================= //

/*
    Add/ensure these prototypes appear in input_box.h after the includes.
    They cover all functions defined in this header's implementation section.
*/

#ifdef __cplusplus
extern "C"
{
#endif

    short int ib_2_3_4_poly_equation(unsigned short int input_line,
                                     unsigned short int input_column,
                                     unsigned short int bottom_barrier,
                                     double *result,
                                     const char *help_panel);

    bool open_new_process(const char *feature, bool wait_for_child_process);

    void substitude_variables(__INFIX__ *I_exp);

    bool initialize_variables(HANDLE *hMapFile);

    void free_coefficients(double **coefficients);

    void assign_variables(void);

    short int solve_poly_get_coef(double *coefficient);

    char *ib_se_get_function(void);

    void start_solving_section(char *str_function,
                               const char var,
                               const double l_bound,
                               const double u_bound,
                               const unsigned short int output_line);

    void solve_equation_display_result(void);

#ifdef __cplusplus
} // extern "C"
#endif

// ======================================================================================================= //
// ======================================================================================================= //
// ======================================================================================================= //

void assign_variables()
{
    HANDLE av_hMapFile;

    {
        // get access to memory block
        av_hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, SHARED_MEM_NAME);
        if (!av_hMapFile || av_hMapFile == INVALID_HANDLE_VALUE)
            return;

        // get the address of the shared memory
        variable_set = (shared_variables *)MapViewOfFile(av_hMapFile,
                                                         FILE_MAP_ALL_ACCESS,
                                                         0,
                                                         0,
                                                         sizeof(shared_variables) * NUM_OF_VARIABLES);
        //
        if (!variable_set)
        {
            CloseHandle(av_hMapFile);
            return;
        }
    }

    // modify the value of variables
    {
        puts("-----Modify Variables-----");
        puts("  [Esc] To exit this panel");
        puts("  [Enter ↳] Enter variable name then press Enter to assign its value\n");
        printf("Variable name: ");

        const short int vn_input_line = 4;
        const short int vn_output_line = 5;
        const short int vn_input_col = strlen("Variable name: ") + 1;
        short int vn_input_code;
        char var;

        const short int exp_input_line = 7;

        while (1)
        {
            vn_input_code = _getch();

            // standard var
            if (((vn_input_code >= 'a' && vn_input_code <= 'z') || (vn_input_code >= 'A' && vn_input_code <= 'Z')) && vn_input_code != 'c' && vn_input_code != 'e' && vn_input_code != 'g')
            {
                var = vn_input_code;
                move_cursor(vn_input_line, vn_input_col - 1);
                putchar(var);

                clear_line_(vn_output_line);
                printf("Current value: %.17lf", variable_set[index_table[var]].num);
                move_cursor(vn_input_line, vn_input_col);
            }

            // enter
            else if (vn_input_code == 13)
            {
                move_cursor(exp_input_line, 0);
                printf("Type your expression: ");

                // compute & store new value
                {
                    char *str_exp = input_String("");

                    __INFIX__ I_exp = convert_string_to_INFIX(str_exp);

                    //
                    substitude_variables(&I_exp);

                    variable_set[index_table[var]].num = evaluate_I_exp(I_exp);
                    //
                    free(I_exp.tokens);
                    free(str_exp);
                }

                clear_line_in_range(vn_output_line, exp_input_line + 5);
                printf("Current value: %.17lf", variable_set[index_table[var]].num);

                move_cursor(vn_input_line, vn_input_col);
            }

            // esc
            else if (vn_input_code == 27)
                break;
        }
    }

    UnmapViewOfFile(variable_set);
    CloseHandle(av_hMapFile);
}

bool initialize_variables(HANDLE *hMapFile)
{
    (*hMapFile) = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(shared_variables) * NUM_OF_VARIABLES,
        SHARED_MEM_NAME);

    if (!(*hMapFile) || (*hMapFile) == INVALID_HANDLE_VALUE)
    {
        perror("initialize_variable: Failed to create shared memory");
        printf("Last error: %lu\n", GetLastError());
        return false;
    }

    // pass the address of the shared memory block to the main process
    variable_set = (shared_variables *)MapViewOfFile((*hMapFile),
                                                     FILE_MAP_ALL_ACCESS,
                                                     0,
                                                     0,
                                                     sizeof(shared_variables) * NUM_OF_VARIABLES);
    //
    if (!variable_set)
    {
        perror("initialize_variables: Failed to pass address of shared memory");
        return false;
    }

    // initialize value for variables
    const char var_set_name[] = "abdfhijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (short int i = 0; i < NUM_OF_VARIABLES; i++)
    {
        variable_set[i].num = 0;
        variable_set[i].var_name = var_set_name[i];
    }

    return true;
}

void substitude_variables(__INFIX__ *I_exp)
{
    char special_vars[NUM_OF_VARIABLES + 1] = {0};
    short int index_sv = 0;

    // scan for functions' special var
    for (short int i = 0; i < I_exp->size; i++)
    {
        if (I_exp->tokens[i - 3].operator!= ',' && I_exp->tokens[i - 1].operator== ',' && I_exp->tokens[i].variable != '\0' &&(I_exp->tokens[i + 1].operator== ',' || I_exp->tokens[i + 1].operator== '='))
        {
            special_vars[index_sv++] = I_exp->tokens[i].variable;
        }
    }

    // first substitution

    for (short int i = 0; i < I_exp->size; i++)
    {
        if (I_exp->tokens[i].variable == '\0')
            continue;

        bool special_var = false;
        for (short int k = 0; k < index_sv; k++)
        {
            if (I_exp->tokens[i].variable == special_vars[k])
            {
                special_var = true;
                break;
            }
        }
        if (special_var)
            continue;

        I_exp->tokens[i].num = variable_set[index_table[I_exp->tokens[i].variable]].num;

        I_exp->tokens[i].variable = '\0';
    }

    // check
    // puts("Check 1\n");
    // display_infix_exp(*I_exp);
    // putchar('\n');
    // system("pause");

    if (special_vars[0] == 0 || !handle_special_functions_(I_exp))
        return;

    // second substitution

    for (short int i = 0; i < I_exp->size; i++)
    {
        if (I_exp->tokens[i].variable == '\0')
            continue;

        I_exp->tokens[i].num = variable_set[index_table[I_exp->tokens[i].variable]].num;

        I_exp->tokens[i].variable = '\0';
    }

    // check 2
    // puts("\n\nCheck 2\n");
    // display_infix_exp(*I_exp);
}

bool open_new_process(const char *feature, bool wait_for_child_process)
{
    STARTUPINFOA si = {sizeof(STARTUPINFOA)};
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // Configure startup info to use normal console handles
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    char cmdLine[256];
    snprintf(cmdLine, sizeof(cmdLine), "cmd /c \"%s %s\"", PROGRAM_NAME, feature);

    BOOL success = CreateProcessA(
        NULL, cmdLine, NULL, NULL, TRUE,
        CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

    if (!success)
    {
        perror("open_new_process: Failed to create new process, wrong program name OR other errors");
        return false;
    }

    // Wait for the child process to finish
    if (wait_for_child_process)
        WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up process handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

short int ib_2_3_4_poly_equation(unsigned short int input_line, unsigned short int input_column, unsigned short int bottom_barrier, double *result, const char *help_panel)
{
    int input_code = 0;
    short int input_index = 0;
    bool new_input = false;
    int C_X, C_Y;
    int win_w, win_h;
    short int top_barrier = input_line;

    getWinSize(&win_w, &win_h);

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            get_cursor_position(&C_X, &C_Y);
            clear_line_in_range(top_barrier, bottom_barrier);
            printf("%s", str_input);
            new_input = false;
        }

        input_code = _getch();

        if (((input_code >= 'a' && input_code <= 'z') ||
             (input_code >= '0' && input_code <= '9') ||
             (input_code >= 'A' && input_code <= 'Z') ||
             input_code == '!' ||
             input_code == '%' ||
             input_code == '^' ||
             input_code == '*' ||
             input_code == '(' ||
             input_code == ')' ||
             input_code == '-' ||
             input_code == '+' ||
             input_code == '/' ||
             input_code == '.' ||
             input_code == ',' ||
             input_code == ' ' ||
             input_code == '=') &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8)
        {
            if (input_index > 0)
            {
                str_input[--input_index] = '\0';
                new_input = true;
            }
        }

        // assign var & compute [Ctrl + Enter]
        else if (input_code == 10)
        {
            open_new_process("global-assign-variables", true);
            new_input = true;
        }

        // enter
        else if (input_code == 13 && input_index != 0)
        {
            break;
        }

        // Esc
        else if (input_code == 27)
        {
            open_menu = true;
            *result = 0.0;
            return 27;
        }

        // Ctrl + C
        else if (input_code == 3)
        {
            open_new_process("display-const", false);
        }

        // Ctrl + L
        else if (input_code == 12)
        {
            open_new_process("usualcal-display-func", false);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process(help_panel, false);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            memset(str_input, 0, max_input_len);
            input_index = 0;
            input_line = top_barrier;
            C_X = 0;
            C_Y = input_line;
            clear_line_in_range(top_barrier, bottom_barrier);
            move_cursor(input_line, 0);
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }

    // compute input
    __INFIX__ I_input = convert_string_to_INFIX(str_input);

    substitude_variables(&I_input);
    (*result) = evaluate_I_exp(I_input);

    free(str_input);
    free(I_input.tokens);

    if (!isfinite(*result))
        return -1;

    clear_line_(input_line);

    return 0;
}

void free_coefficients(double **coefficients)
{
    if (*coefficients != NULL)
    {
        free(*coefficients);
        *coefficients = NULL;
    }
}

short int solve_poly_get_coef(double *coefficient)
{
    int input_code = 0;

    short int input_index = 0;

    bool new_input = false;

    int C_X, C_Y;
    get_cursor_position(&C_X, &C_Y);

    int win_w;

    short int input_column = C_X;
    short int input_line = C_Y;

    short int top_barrier = input_line;
    short int bottom_barrier = top_barrier + 3;

    getWinSize(&win_w, NULL);

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            get_cursor_position(&C_X, &C_Y);
            // clear_line_in_range(top_barrier, bottom_barrier);
            clear_line_in_range(top_barrier, C_Y);
            move_cursor(C_Y, 0);
            printf("%s", str_input);
            new_input = false;
        }

        input_code = _getch();

        if (((input_code >= 'a' && input_code <= 'z') ||
             (input_code >= '0' && input_code <= '9') ||
             (input_code >= 'A' && input_code <= 'Z') ||
             input_code == '!' ||
             input_code == '%' ||
             input_code == '^' ||
             input_code == '*' ||
             input_code == '(' ||
             input_code == ')' ||
             input_code == '-' ||
             input_code == '+' ||
             input_code == '/' ||
             input_code == '.' ||
             input_code == ',' ||
             input_code == ' ' ||
             input_code == '=') &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8)
        {
            if (input_index > 0)
            {
                str_input[--input_index] = '\0';
                new_input = true;
            }
        }

        // assign var & compute [Ctrl + Enter]
        else if (input_code == 10)
        {
            open_new_process("global-assign-variables", true);
            new_input = true;
        }

        // enter
        else if (input_code == 13 && input_index != 0)
        {
            break;
        }

        // Esc
        else if (input_code == 27)
        {
            open_menu = true;
            (*coefficient) = 0.0;
            return 27;
        }

        // Ctrl + C
        else if (input_code == 3)
        {
            open_new_process("display-const", false);
        }

        // Ctrl + L
        else if (input_code == 12)
        {
            open_new_process("usualcal-display-func", false);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_n_degree_poly-display-help", false);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            memset(str_input, 0, max_input_len);
            input_index = 0;
            input_line = top_barrier;
            C_X = 0;
            C_Y = input_line;
            clear_line_in_range(top_barrier, bottom_barrier);
            move_cursor(input_line, 0);
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }

    // compute input
    __INFIX__ I_input = convert_string_to_INFIX(str_input);

    substitude_variables(&I_input);
    (*coefficient) = evaluate_I_exp(I_input);

    free(str_input);
    free(I_input.tokens);

    if (!isfinite(*coefficient))
        return -1;

    clear_line_(input_line);

    return 0;
}

char *ib_se_get_function()
{
    int input_code = 0;

    short int input_index = 0;

    bool new_input = false;

    int C_X, C_Y;
    get_cursor_position(&C_X, &C_Y);

    int win_w;

    short int input_column = 0;
    short int input_line = C_Y + 1;

    short int top_barrier = input_line;
    short int bottom_barrier = top_barrier + 2;

    getWinSize(&win_w, NULL);

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            get_cursor_position(&C_X, &C_Y);
            clear_line_in_range(top_barrier, C_Y);
            move_cursor(C_Y, 0);
            printf("%s", str_input);
            new_input = false;
        }

        input_code = _getch();

        if (((input_code >= 'a' && input_code <= 'z') ||
             (input_code >= '0' && input_code <= '9') ||
             (input_code >= 'A' && input_code <= 'Z') ||
             input_code == '!' ||
             input_code == '%' ||
             input_code == '^' ||
             input_code == '*' ||
             input_code == '(' ||
             input_code == ')' ||
             input_code == '-' ||
             input_code == '+' ||
             input_code == '/' ||
             input_code == '.' ||
             input_code == ',' ||
             input_code == ' ' ||
             input_code == '=') &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8)
        {
            if (input_index > 0)
            {
                str_input[--input_index] = '\0';
                new_input = true;
            }
        }

        // assign var & compute [Ctrl + Enter]
        else if (input_code == 10)
        {
            open_new_process("global-assign-variables", true);
            new_input = true;
        }

        // enter
        else if (input_code == 13 && input_index != 0)
        {
            break;
        }

        // Esc
        else if (input_code == 27)
        {
            free_buffer(&str_input);
            return NULL;
        }

        // Ctrl + C
        else if (input_code == 3)
        {
            open_new_process("display-const", false);
        }

        // Ctrl + L
        else if (input_code == 12)
        {
            open_new_process("usualcal-display-func", false);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_equation-display-help", false);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            memset(str_input, 0, max_input_len);
            input_index = 0;
            input_line = top_barrier;
            C_X = 0;
            C_Y = input_line;
            clear_line_in_range(top_barrier, bottom_barrier);
            move_cursor(input_line, 0);
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }

    clear_line_in_range(top_barrier, bottom_barrier);

    return str_input;
}

void start_solving_section(char *str_function, const char var, const double l_bound, const double u_bound, const unsigned short int output_line)
{
    // convert string to infix
    __INFIX__ I_function = convert_string_to_INFIX(str_function);

    // check for valid function
    bool var_found = false;
    for (unsigned short int i = 0; i < I_function.size; i++)
    {
        if (I_function.tokens[i].variable == var)
        {
            var_found = true;
            break;
        }
    }
    if (!var_found)
    {
        clear_line_in_range(output_line, output_line + 3);
        printf("⚠  Variable %c was not found in your function ⚠", var);
        free(I_function.tokens);
        return;
    }

    // substitude variables
    // substitude_variables(&I_function);

    // start solving
    double *roots = NULL;
    short int numof_root = se_solve_equation(I_function, var, l_bound, u_bound, &roots);

    free(I_function.tokens);

    if (roots == NULL || numof_root < 0)
    {
        clear_line_(output_line);
        puts("Failed to solve equation");
        printf("GetLastError: %llu", GetLastError());
        return;
    }
    else if (numof_root == 0)
    {
        clear_line_in_range(output_line, output_line + 3);
        puts("No solution found\nTIP: You can change the range to find other solution(s)");
        if (roots != NULL)
            free(roots);
        return;
    }

    // pass results to child process and display
    {
        // ====== Create Handles ====== \\_
        HANDLE h_map_file_solution_pack = CreateFileMappingA(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            sizeof(solution_pack),
            SHARED_MEM_NAME_SOLUTION_PACK);

        if (!h_map_file_solution_pack || h_map_file_solution_pack == INVALID_HANDLE_VALUE)
        {
            perror("start_solving_section: Failed to create h_map_file_solution_pack");
            free(roots);
            return;
        }

        HANDLE h_map_file_root_array = CreateFileMappingA(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            sizeof(double) * numof_root,
            SHARED_MEM_NAME_ROOT_ARRAY);

        if (!h_map_file_root_array || h_map_file_root_array == INVALID_HANDLE_VALUE)
        {
            perror("satrt_solving_section: Failed to create h_map_file_root_array");
            free(roots);
            CloseHandle(h_map_file_solution_pack);
            return;
        }

        HANDLE h_map_file_str_function = CreateFileMappingA(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            0,
            sizeof(char) * strlen(str_function) + 1,
            SHARED_MEM_NAME_STR_FUNCTION);
        if (!h_map_file_str_function || h_map_file_str_function == INVALID_HANDLE_VALUE)
        {
            perror("start_solving_section: Failed to create h_map_file_function");
            free(roots);
            CloseHandle(h_map_file_solution_pack);
            CloseHandle(h_map_file_root_array);
            return;
        }

        // ================== \\ 

        // ====== Alloc shared memory ====== \\_

        shared_solution_pack = (solution_pack *)MapViewOfFile(h_map_file_solution_pack,
                                                              FILE_MAP_ALL_ACCESS,
                                                              0,
                                                              0,
                                                              sizeof(solution_pack));
        //
        if (shared_solution_pack == NULL)
        {
            perror("start_solving_section: Failed to pass pointer to shared_solution_pack");

            CloseHandle(h_map_file_solution_pack);
            CloseHandle(h_map_file_str_function);
            CloseHandle(h_map_file_root_array);
            free(roots);
            return;
        }

        char *temp_str_function = (char *)MapViewOfFile(h_map_file_str_function,
                                                        FILE_MAP_ALL_ACCESS,
                                                        0,
                                                        0,
                                                        sizeof(char) * strlen(str_function) + 1);
        //
        if (temp_str_function == NULL)
        {
            perror("start_solving_section: Failed to pass pointer to shared_solution_pack->str_function");

            CloseHandle(h_map_file_solution_pack);
            CloseHandle(h_map_file_str_function);
            CloseHandle(h_map_file_root_array);
            free(roots);
            return;
        }

        shared_solution_pack->solutions_array = (double *)MapViewOfFile(h_map_file_root_array,
                                                                        FILE_MAP_ALL_ACCESS,
                                                                        0,
                                                                        0,
                                                                        sizeof(double) * numof_root);
        //
        if (shared_solution_pack->solutions_array == NULL)
        {
            perror("start_solving_section: Failed to pass pointer to shared_solution_pack->solution_array");

            CloseHandle(h_map_file_solution_pack);
            CloseHandle(h_map_file_str_function);
            CloseHandle(h_map_file_root_array);
            free(roots);
            return;
        }

        // copy data to shared memory
        {
            shared_solution_pack->l_bound = l_bound;
            shared_solution_pack->u_bound = u_bound;
            shared_solution_pack->var = var;
            shared_solution_pack->numof_solutions = numof_root;
            shared_solution_pack->str_function_len = strlen(str_function);
            memcpy(temp_str_function, str_function, shared_solution_pack->str_function_len + 1);
            shared_solution_pack->str_function = temp_str_function;
            for (unsigned short int i = 0; i < numof_root; i++)
                shared_solution_pack->solutions_array[i] = roots[i];
        }

        // ================== \\_

        // open new process and display
        open_new_process("solve_equation-display-results", false);

        clear_line_in_range(output_line, output_line + 3);
        puts("Displaying results");
        system("pause");
        clear_line_in_range(output_line, output_line + 3);

        CloseHandle(h_map_file_root_array);
        CloseHandle(h_map_file_str_function);
        CloseHandle(h_map_file_solution_pack);
    }

    free(roots);
}

void solve_equation_display_result()
{
    // Create handles for all shared memory segments
    HANDLE h_solution_pack = NULL;
    HANDLE h_solution_array = NULL;
    HANDLE h_str_function = NULL;

    // Pointers for mapped memory
    solution_pack *solution_data = NULL;
    double *solutions = NULL;
    char *str_function = NULL; // Separate pointer for string

    // Open solution pack shared memory
    h_solution_pack = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_SOLUTION_PACK);
    if (!h_solution_pack || h_solution_pack == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Failed to open solution pack mapping. Error: %lu\n", GetLastError());
        goto cleanup;
    }

    // Map the solution pack
    solution_data = (solution_pack *)MapViewOfFile(h_solution_pack,
                                                   FILE_MAP_ALL_ACCESS, 0, 0, sizeof(solution_pack));
    if (!solution_data)
    {
        fprintf(stderr, "Failed to map solution pack view. Error: %lu\n", GetLastError());
        goto cleanup;
    }

    // Open solution array shared memory
    h_solution_array = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_ROOT_ARRAY);
    if (!h_solution_array || h_solution_array == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Failed to open solution array mapping. Error: %lu\n", GetLastError());
        goto cleanup;
    }

    // Map the solutions array
    solutions = (double *)MapViewOfFile(h_solution_array,
                                        FILE_MAP_ALL_ACCESS, 0, 0,
                                        sizeof(double) * solution_data->numof_solutions);
    if (!solutions)
    {
        fprintf(stderr, "Failed to map solutions array view. Error: %lu\n", GetLastError());
        goto cleanup;
    }

    // Open function string shared memory
    h_str_function = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_STR_FUNCTION);
    if (!h_str_function || h_str_function == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Failed to open string function mapping. Error: %lu\n", GetLastError());
        goto cleanup;
    }

    // Map the function string - FIXED VERSION
    str_function = (char *)MapViewOfFile(h_str_function,
                                         FILE_MAP_ALL_ACCESS, 0, 0,
                                         sizeof(char) * (solution_data->str_function_len + 1));
    if (!str_function)
    {
        fprintf(stderr, "Failed to map function string view. Error: %lu\n", GetLastError());
        goto cleanup;
    }

    // Display results
    // puts("\nResults:");
    // puts("The equation:");
    // printf("%s = 0\n", str_function); // Use str_function instead of solution_data->str_function

    // if (solution_data->numof_solutions > 0)
    // {
    //     puts("\nHas the following solution(s):");
    //     se_display_root_array(solutions, solution_data->numof_solutions);
    //     printf("\nSolution(s) are/is found in the range: [%.3lf , %.3lf]\n",
    //            solution_data->l_bound, solution_data->u_bound);
    // }
    // else
    // {
    //     puts("\nNo solutions found in the specified range.");
    // }
    puts("‿︵‿︵‿︵‿RESULT︵‿︵‿︵‿︵");
    puts("\nThe Equation:\n");
    printf("%s = 0", str_function);
    if (solution_data->numof_solutions == 1)
    {
        printf("\n\nHas 1 solution in the range [%.3lf , %.3lf]:\n\n  %c = ", solution_data->l_bound, solution_data->u_bound, solution_data->var);
        display_number(solutions[0]);
        putchar('\n');
    }

    else
    {
        printf("\n\nHas %d solutions:\n\n", solution_data->numof_solutions);
        se_display_root_array(solutions, solution_data->var, solution_data->numof_solutions);
        printf("\n\nSolutions are found in the range [%.3lf , %.3lf]\n", solution_data->l_bound, solution_data->u_bound);
    }
cleanup:
    // Cleanup all mapped views and handles
    if (str_function)
        UnmapViewOfFile(str_function);
    if (solutions)
        UnmapViewOfFile(solutions);
    if (solution_data)
        UnmapViewOfFile(solution_data);

    if (h_str_function)
        CloseHandle(h_str_function);
    if (h_solution_array)
        CloseHandle(h_solution_array);
    if (h_solution_pack)
        CloseHandle(h_solution_pack);

    system("pause >nul");
}

#endif