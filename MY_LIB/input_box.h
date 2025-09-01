#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <MY_LIB/lexer_and_format.h>
#include <MY_LIB/global_var.h>
#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <MY_LIB/cal_info.h>
#include <MY_LIB/sovle_equations.h>
#include <MY_LIB/numerical_integration.h>


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

    bool open_new_background_process(const char *feature, bool wait_for_child_process, PROCESS_INFORMATION *process_info);

    bool terminate_child_process(PROCESS_INFORMATION *process_info);

    bool terminate_process_by_id(DWORD process_id);

    bool is_child_process_running(PROCESS_INFORMATION *process_info);

    void cleanup_child_process(PROCESS_INFORMATION *process_info);

    void substitude_variables(__INFIX__ *I_exp);

    bool initialize_variables(HANDLE *hMapFile);

    void ib_get_valueof_var_set(void);

    void free_coefficients(double **coefficients);

    void assign_variables(void);

    short int ib_solve_poly_get_coef(double *coefficient);

    char *ib_se_get_function(void);

    char *ib_ic_get_function();

    void ib_ic_get_var(char *var);

    short int ib_ic_get_bounds(unsigned short int input_line, unsigned short int input_column, unsigned short int bottom_barrier, double *result);

    void ib_integrate_section(char *str_function, const char var, const double a, const double b, unsigned short int method, double *result);

    void ib_integrate_in_the_background();

    void start_solving_section(char *str_function,
                               const char var,
                               const double l_bound,
                               const double u_bound,
                               const unsigned short int output_line);

    void solve_equation_display_result(void);

    short int ib_for_system_o_l_e(int *ptr_input_line, unsigned short int input_column, unsigned short int bottom_barrier, double *result, const char *help_panel);

    char *ib_ssonle_get_function(int *ptr_input_line, unsigned short int input_column, unsigned short int bottom_barrier, const char *help_panel);

#ifdef __cplusplus
} // extern "C"
#endif

// ======================================================================================================= //
// ======================================================================================================= //
// ======================================================================================================= //

void assign_variables()
{
    show_cursor();
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
        puts("🛠️🔠🔡 Modify Variables");
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
        if (I_exp->tokens[i].variable <= 0)
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
        if (I_exp->tokens[i].variable <= 0)
            continue;

        I_exp->tokens[i].num = variable_set[index_table[I_exp->tokens[i].variable]].num;

        I_exp->tokens[i].variable = '\0';
    }

    // check 2
    // puts("\n\nCheck 2\n");
    // display_infix_exp(*I_exp);
}

bool open_new_background_process(const char *feature, bool wait_for_child_process, PROCESS_INFORMATION *process_info)
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
    snprintf(cmdLine, sizeof(cmdLine), "%s %s", PROGRAM_NAME, feature);

    BOOL success = CreateProcessA(
        NULL, cmdLine, NULL, NULL, FALSE,
        CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

    if (!success)
    {
        perror("open_new_background_process: Failed to create new process, wrong program name OR other errors");
        return false;
    }

    // Copy process information to the caller
    if (process_info != NULL)
    {
        *process_info = pi;
    }

    // Wait for the child process to finish if requested
    if (wait_for_child_process)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Clean up process handles if we waited
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        // Clear the process info since it's no longer valid
        if (process_info != NULL)
        {
            ZeroMemory(process_info, sizeof(PROCESS_INFORMATION));
        }
    }

    return true;
}

bool terminate_process_by_id(DWORD process_id)
{
    HANDLE h_process = OpenProcess(PROCESS_TERMINATE, FALSE, process_id);
    if (h_process == NULL)
        return false;

    BOOL success = TerminateProcess(h_process, 0);
    CloseHandle(h_process);
    return success;
}

bool terminate_child_process(PROCESS_INFORMATION *process_info)
{
    if (process_info == NULL || process_info->hProcess == NULL)
    {
        return false; // No valid process to terminate
    }

    // Try to terminate gracefully first
    BOOL success = TerminateProcess(process_info->hProcess, 0);

    if (success)
    {
        // Wait a bit for graceful termination
        DWORD wait_result = WaitForSingleObject(process_info->hProcess, 1); // 1m seconds

        if (wait_result == WAIT_TIMEOUT)
        {
            // Force kill if it doesn't terminate gracefully
            TerminateProcess(process_info->hProcess, 1);
            WaitForSingleObject(process_info->hProcess, 1);
        }

        // Clean up
        cleanup_child_process(process_info);
        return true;
    }

    return false;
}

bool is_child_process_running(PROCESS_INFORMATION *process_info)
{
    if (process_info == NULL || process_info->hProcess == NULL)
        return false;

    DWORD exit_code;
    if (GetExitCodeProcess(process_info->hProcess, &exit_code))
    {
        if (exit_code == STILL_ACTIVE)
            return true;
        else
        {
            // Process has terminated
            cleanup_child_process(process_info);
            return false;
        }
    }

    return false;
}

void cleanup_child_process(PROCESS_INFORMATION *process_info)
{
    if (process_info == NULL)
        return;

    if (process_info->hProcess != NULL)
    {
        CloseHandle(process_info->hProcess);
        process_info->hProcess = NULL;
    }

    if (process_info->hThread != NULL)
    {
        CloseHandle(process_info->hThread);
        process_info->hThread = NULL;
    }

    process_info->dwProcessId = 0;
    process_info->dwThreadId = 0;
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
    snprintf(cmdLine, sizeof(cmdLine), "%s %s", PROGRAM_NAME, feature);

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
    show_cursor();
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
            clear_line_in_range(top_barrier, bottom_barrier);

            printf("%s", str_input);
            new_input = false;

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);

            new_input = true;
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

short int ib_solve_poly_get_coef(double *coefficient)
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

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);
            new_input = true;
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

    int win_w, win_h;

    short int input_column = 0;
    short int input_line = C_Y + 1;

    short int top_barrier = input_line;
    short int bottom_barrier = top_barrier + 2;

    getWinSize(&win_w, &win_h);

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            // get for current row
            get_cursor_position(NULL, &C_Y);

            unsigned short int num_of_line = bottom_barrier - top_barrier;
            for (unsigned short int i = 1; i <= num_of_line; i++)
            {
                // clear current line
                clear_line_(C_Y + i - 1);
                putchar('\n');
            }

            if (win_h - C_Y <= num_of_line)
            {
                input_line -= num_of_line - (win_h - C_Y) + 1;
            }

            // move to input line
            move_cursor(input_line, 0);

            printf("%s", str_input);
            new_input = false;

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);
            new_input = true;
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

short int ib_for_system_o_l_e(int *ptr_input_line, unsigned short int input_column, unsigned short int bottom_barrier, double *result, const char *help_panel)
{
    unsigned short int input_line = *ptr_input_line;
    int input_code = 0;
    short int input_index = 0;
    bool new_input = false;
    int C_X, C_Y;
    int win_w, win_h;
    getWinSize(&win_w, &win_h);

    if (input_line == win_h)
    {
        putchar('\n');
        input_line--;
    }

    short int top_barrier = input_line;

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            // get for current row
            get_cursor_position(NULL, &C_Y);

            unsigned short int num_of_line = bottom_barrier - top_barrier;
            for (unsigned short int i = 1; i <= num_of_line; i++)
            {
                // clear current line
                clear_line_(C_Y + i - 1);
                putchar('\n');
            }

            if (win_h - C_Y <= num_of_line)
            {
                input_line -= num_of_line - (win_h - C_Y) + 1;
            }

            // move to input line
            move_cursor(input_line, 0);

            printf("%s", str_input);
            new_input = false;

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);
            new_input = true;
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

    *ptr_input_line = input_line;

    return 0;
}

char *ib_ssonle_get_function(int *ptr_input_line, unsigned short int input_column, unsigned short int bottom_barrier, const char *help_panel)
{
    unsigned short int input_line = *ptr_input_line;
    int input_code = 0;
    short int input_index = 0;
    bool new_input = false;
    int C_X, C_Y;
    int win_w, win_h;
    getWinSize(&win_w, &win_h);

    if (input_line == win_h)
    {
        putchar('\n');
        input_line--;
    }

    short int top_barrier = input_line;

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            // get for current row
            get_cursor_position(NULL, &C_Y);

            unsigned short int num_of_line = bottom_barrier - top_barrier;
            for (unsigned short int i = 1; i <= num_of_line; i++)
            {
                // clear current line
                clear_line_(C_Y + i - 1);
                putchar('\n');
            }

            if (win_h - C_Y <= num_of_line)
            {
                input_line -= num_of_line - (win_h - C_Y) + 1;
            }

            // move to input line
            move_cursor(input_line, 0);

            printf("%s", str_input);
            new_input = false;

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);
            new_input = true;
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

    // // compute input
    // __INFIX__ I_input = convert_string_to_INFIX(str_input);

    // substitude_variables(&I_input);
    // (*result) = evaluate_I_exp(I_input);

    // free(str_input);
    // free(I_input.tokens);

    // if (!isfinite(*result))
    //     return -1;

    // clear_line_(input_line);

    *ptr_input_line = input_line;

    return str_input;
}

char *ib_ic_get_function()
{
    show_cursor();
    int input_code = 0;

    short int input_index = 0;

    bool new_input = false;

    int C_X, C_Y;
    get_cursor_position(&C_X, &C_Y);

    int win_w, win_h;

    short int input_column = 0;
    short int input_line = C_Y + 1;

    short int top_barrier = input_line;
    short int bottom_barrier = top_barrier + 2;

    getWinSize(&win_w, &win_h);

    short int max_input_len = (bottom_barrier - top_barrier) * win_w;

    char *str_input = create_new_buffer_with_sizeof(max_input_len);

    move_cursor(input_line, input_column);
    get_cursor_position(&C_X, &C_Y);

    while (1)
    {
        if (new_input)
        {
            // get for current row
            get_cursor_position(NULL, &C_Y);

            unsigned short int num_of_line = bottom_barrier - top_barrier;
            for (unsigned short int i = 1; i <= num_of_line; i++)
            {
                // clear current line
                clear_line_(C_Y + i - 1);
                putchar('\n');
            }

            if (win_h - C_Y <= num_of_line)
            {
                input_line -= num_of_line - (win_h - C_Y) + 1;
            }

            // move to input line
            move_cursor(input_line, 0);

            printf("%s", str_input);
            new_input = false;

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_code != '=' &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);
            new_input = true;
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

void ib_ic_get_var(char *var)
{
    show_cursor();
    while (1)
    {
        (*var) = _getch();

        if (((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z')) && *var != 'c' && *var != 'e' && *var != 'g')
        {
            break;
        }

        else if ((*var) == 27)
        {
            (*var) = 'x';
            return;
        }
    }
}

short int ib_ic_get_bounds(unsigned short int input_line, unsigned short int input_column, unsigned short int bottom_barrier, double *result)
{
    show_cursor();
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
            clear_line_in_range(top_barrier, bottom_barrier);

            printf("%s", str_input);
            new_input = false;

            // safety & create smooth style- put a delay between each process
            delay(5);
        }

        input_code = _getch();

        if (laf_valid_input_code(input_code) &&
            input_index < max_input_len)
        {
            if (input_index == 0 && input_code == ' ')
                continue;
            str_input[input_index++] = input_code;

            laf_encode_math_symbols(str_input, &input_index);

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8 && input_index > 0)
        {
            laf_delete_input_code(str_input, &input_index);

            new_input = true;
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
            open_new_process("--der-cal-display-func", false);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("integral_calculator-display-help", false);
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

void ib_integrate_section(char *str_function, const char var, const double a, const double b, unsigned short int method, double *result)
{
    // ==========================================PREPARE========================================== //
    unsigned short int len = strlen(str_function);
    char *smem_function = NULL;
    unsigned short int *smem_len = NULL;
    char *smem_var = NULL;
    double *smem_a = NULL;
    double *smem_b = NULL;
    unsigned short int *smem_method = NULL;
    double *smem_result = NULL;

    // function
    HANDLE h_map_file_function = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(char) * (len + 1),
        SHARED_MEM_NAME_IC_FUNCTION);

    if (!h_map_file_function || h_map_file_function == INVALID_HANDLE_VALUE)
    {
        perror("ib_integrate_section_prepare: Failed to create function handle");
        return;
    }

    smem_function = (char *)MapViewOfFile(h_map_file_function, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char) * (len + 1));
    if (smem_function == NULL)
    {
        CloseHandle(h_map_file_function);
        return;
    }

    // len
    HANDLE h_map_file_len = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(unsigned short int),
        SHARED_MEM_NAME_IC_LEN);

    if (!h_map_file_len || h_map_file_len == INVALID_HANDLE_VALUE)
    {
        perror("ib_integrate_section_prepare: Failed to create function handle");
        CloseHandle(h_map_file_function);
        return;
    }

    smem_function = (char *)MapViewOfFile(h_map_file_function, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char) * (len + 1));
    if (smem_function == NULL)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_len);
        return;
    }

    // var
    HANDLE h_map_file_var = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(char),
        SHARED_MEM_NAME_IC_VARIABLE);

    if (!h_map_file_var || h_map_file_var == INVALID_HANDLE_VALUE)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_len);
        perror("ib_integrate_section_prepare: Failed to create var handle");
        return;
    }

    smem_var = (char *)MapViewOfFile(h_map_file_var, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char));
    if (smem_var == NULL)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_len);
        return;
    }

    // a
    HANDLE h_map_file_a = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(double),
        SHARED_MEM_NAME_IC_A);

    if (!h_map_file_a || h_map_file_a == INVALID_HANDLE_VALUE)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_len);
        perror("ib_integrate_section_prepare: Failed to create \"a\" handle");
        return;
    }

    smem_a = (double *)MapViewOfFile(h_map_file_a, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(double));
    if (smem_a == NULL)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_len);
        return;
    }

    // b
    HANDLE h_map_file_b = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(double),
        SHARED_MEM_NAME_IC_B);

    if (!h_map_file_b || h_map_file_b == INVALID_HANDLE_VALUE)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_len);
        perror("ib_integrate_section_prepare: Failed to create \"b\" handle");
        return;
    }

    smem_b = (double *)MapViewOfFile(h_map_file_b, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(double));
    if (smem_b == NULL)
    {
        CloseHandle(h_map_file_b);
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_b);
        CloseHandle(h_map_file_len);
        return;
    }

    // method
    HANDLE h_map_file_method = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(unsigned short int),
        SHARED_MEM_NAME_IC_METHOD);

    if (!h_map_file_method || h_map_file_method == INVALID_HANDLE_VALUE)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_b);
        CloseHandle(h_map_file_len);
        perror("ib_integrate_section_prepare: Failed to create method handle");
        return;
    }

    smem_method = (unsigned short int *)MapViewOfFile(h_map_file_method, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(unsigned short int));
    if (smem_method == NULL)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_b);
        CloseHandle(h_map_file_method);
        CloseHandle(h_map_file_len);
        return;
    }

    // result
    HANDLE h_map_file_result = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        sizeof(double),
        SHARED_MEM_NAME_IC_RESULT);

    if (!h_map_file_result || h_map_file_result == INVALID_HANDLE_VALUE)
    {
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_b);
        CloseHandle(h_map_file_method);
        CloseHandle(h_map_file_len);
        perror("ib_integrate_section_prepare: Failed to create result handle");
        return;
    }

    smem_result = (double *)MapViewOfFile(h_map_file_result, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(double));
    if (smem_result == NULL)
    {
        CloseHandle(h_map_file_b);
        CloseHandle(h_map_file_function);
        CloseHandle(h_map_file_var);
        CloseHandle(h_map_file_a);
        CloseHandle(h_map_file_method);
        CloseHandle(h_map_file_result);
        CloseHandle(h_map_file_len);
        return;
    }

    // coppy data to  shared memories
    {
        memcpy(smem_function, str_function, len + 1);
        *smem_var = var;
        *smem_a = a;
        *smem_b = b;
        *smem_method = method;
        *smem_result = NAN;
    }

    // =========================================================================================== //

    // ==========================================INTEGRATE SECTION========================================== //

    // open child process and integrate
    PROCESS_INFORMATION child_process;
    open_new_background_process("integral_calculator-integrate", false, &child_process);

    int C_Y;
    get_cursor_position(NULL, &C_Y);
    clear_line_in_range(C_Y, C_Y + 4);
    puts("(╭ರ_•́)✎📄 Working on it . . .");

    // wait for cihld process
    unsigned int counter = 0;
    bool cancel = false;
    while (is_child_process_running(&child_process))
    {
        counter++;

        if (counter >= 13000000)
        {
            puts("❓ Wait too long?\n👉 Press any key to Cancel . . .");

            while (is_child_process_running(&child_process))
            {
                if (kbhit())
                {
                    terminate_process_by_id(child_process.dwProcessId);
                    cleanup_child_process(&child_process);
                    cancel = true;
                    break;
                }
            }

            if (cancel)
                break;
        }
    }

    if (!cancel)
    {
        clear_line_in_range(C_Y, C_Y + 4);
        *result = *smem_result;
        puts("✅ Integrated Successfully");
        printf("▶ Result: I = %.15g\n", *result);
        puts("ℹ️ Result may have error");

        cleanup_child_process(&child_process);
    }
    else
        puts("❌ Canceled Integration process!");

    // ===================================================================================================== //

    // close handles
    CloseHandle(h_map_file_function);
    CloseHandle(h_map_file_len);
    CloseHandle(h_map_file_var);
    CloseHandle(h_map_file_a);
    CloseHandle(h_map_file_method);
    CloseHandle(h_map_file_b);
    CloseHandle(h_map_file_result);
}

void ib_integrate_in_the_background()
{
    HANDLE h_function = NULL;
    HANDLE h_len = NULL;
    HANDLE h_var = NULL;
    HANDLE h_a = NULL;
    HANDLE h_b = NULL;
    HANDLE h_method = NULL;
    HANDLE h_result = NULL;

    char *function = NULL;
    unsigned short int *len = NULL;
    char *var = NULL;
    double *a = NULL;
    double *b = NULL;
    unsigned short int *method = NULL;
    double *result = NULL;

    // ==========================================OPEN DATA========================================== //

    // open memory
    h_len = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_LEN);
    if (!h_len)
        goto clean_up;

    // map the memory
    len = (unsigned short int *)MapViewOfFile(h_len, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(unsigned short int));
    if (!len)
        goto clean_up;

    // open memory
    h_function = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_FUNCTION);
    if (!h_function)
        goto clean_up;

    // map the memory
    function = (char *)MapViewOfFile(h_function, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char) * (*len));
    if (!function)
        goto clean_up;

    // open memory
    h_var = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_VARIABLE);
    if (!h_var)
        goto clean_up;

    // map the memory
    var = (char *)MapViewOfFile(h_var, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(char));
    if (!var)
        goto clean_up;

    // open memory
    h_a = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_A);
    if (!h_a)
        goto clean_up;

    // map the memory
    a = (double *)MapViewOfFile(h_a, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(double));
    if (!a)
        goto clean_up;

    // open memory
    h_b = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_B);
    if (!h_b)
        goto clean_up;

    // map the memory
    b = (double *)MapViewOfFile(h_b, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(double));
    if (!b)
        goto clean_up;

    // open memory
    h_method = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_METHOD);
    if (!h_method)
        goto clean_up;

    // map the memory
    method = (unsigned short int *)MapViewOfFile(h_method, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(unsigned short int));
    if (!method)
        goto clean_up;

    // open memory
    h_result = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME_IC_RESULT);
    if (!h_result)
        goto clean_up;

    // map the memory
    result = (double *)MapViewOfFile(h_result, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(double));
    if (!result)
        goto clean_up;

    // ============================================================================================= //

    // ==========================================INTEGRATE========================================== //

    __INFIX__ I_function = convert_string_to_INFIX(function);

    ib_get_valueof_var_set();

    const char exception[2] = {*var, '\0'};
    ni_substitude_variables(&I_function, exception);

    (*result) = ni_integrate(I_function, *var, *a, *b, method);

    free(I_function.tokens);

    // ============================================================================================= //

clean_up:
    if (h_function)
        CloseHandle(h_function);
    if (h_len)
        CloseHandle(h_len);
    if (h_var)
        CloseHandle(h_var);
    if (h_a)
        CloseHandle(h_a);
    if (h_b)
        CloseHandle(h_b);
    if (h_method)
        CloseHandle(h_method);
    if (h_result)
        CloseHandle(h_result);

    CloseHandle(handle_var_set);

    if (function)
        UnmapViewOfFile(function);
    if (len)
        UnmapViewOfFile(len);
    if (var)
        UnmapViewOfFile(var);
    if (a)
        UnmapViewOfFile(a);
    if (b)
        UnmapViewOfFile(b);
    if (method)
        UnmapViewOfFile(method);
    if (result)
        UnmapViewOfFile(result);

    UnmapViewOfFile(variable_set);
}

void ib_get_valueof_var_set(void)
{
    // Open the existing shared memory block
    handle_var_set = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM_NAME);
    if (!handle_var_set || handle_var_set == INVALID_HANDLE_VALUE)
    {
        // If shared memory doesn't exist, variable_set remains NULL
        variable_set = NULL;
        return;
    }

    // Map the shared memory to the global variable_set pointer
    variable_set = (shared_variables *)MapViewOfFile(handle_var_set,
                                                     FILE_MAP_ALL_ACCESS,
                                                     0,
                                                     0,
                                                     sizeof(shared_variables) * NUM_OF_VARIABLES);

    // Close the handle as we only need the mapped view
    CloseHandle(handle_var_set);

    // If mapping failed, set variable_set to NULL
    if (!variable_set)
    {
        variable_set = NULL;
    }
}

#endif