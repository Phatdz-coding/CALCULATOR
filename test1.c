#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>

#define NUM_OF_VARIABLES 49
#define SHARED_MEM_NAME "Local\\SharedVariables"
#define PROGRAM_NAME "test1.exe"

// -------------------- shared variables (exp) -------------------- //
typedef struct shared_variables
{
    double num;
    char var_name;
} shared_variables;

// global set
// This pointer holds the address of the shared memory block
shared_variables *variable_set;

// ---------------------------------------------------------- //

// --------------functions and menu------------- //

void usual_calculation();
void _complex_();
void display_menu();
void display_const();
void usualcal_display_func();
void usualcal_display_help();
bool open_new_process(const char *, const bool);
void assign_variables();
bool initialize_variables(HANDLE *hMapFile);
void substitude_variables(__INFIX__ *);
bool central_control();

// ------------------global var---------------- //

bool esc_win = false;
bool open_menu;

static short int index_table[256] = {
    ['a'] = 0, ['b'] = 1, ['d'] = 2, ['f'] = 3, ['h'] = 4, ['i'] = 5, ['j'] = 6, ['k'] = 7, ['l'] = 8, ['m'] = 9, ['n'] = 10, ['o'] = 11, ['p'] = 12, ['q'] = 13, ['r'] = 14, ['s'] = 15, ['t'] = 16, ['u'] = 17, ['v'] = 18, ['w'] = 19, ['x'] = 20, ['y'] = 21, ['z'] = 22, ['A'] = 23, ['B'] = 24, ['C'] = 25, ['D'] = 26, ['E'] = 27, ['F'] = 28, ['G'] = 29, ['H'] = 30, ['I'] = 31, ['J'] = 32, ['K'] = 33, ['L'] = 34, ['M'] = 35, ['N'] = 36, ['O'] = 37, ['P'] = 38, ['Q'] = 39, ['R'] = 40, ['S'] = 41, ['T'] = 42, ['U'] = 43, ['V'] = 44, ['W'] = 45, ['X'] = 46, ['Y'] = 47, ['Z'] = 48};

// -------------------------------------------- //

int main(const int num_of_arg, const char *arg[])
{
    turn_on_advanced_character_mode();

    // get signal and work on child processes
    if (num_of_arg > 1)
    {
        if (!strcmp(arg[1], "display-const"))
            display_const();
        else if (!strcmp(arg[1], "usualcal-display-func"))
            usualcal_display_func();
        else if (!strcmp(arg[1], "usualcal-display-help"))
            usualcal_display_help();
        else if (!strcmp(arg[1], "global-assign-variables"))
            assign_variables();
        return 0;
    }

    // initialize variable set
    HANDLE hMapFile;
    if (!initialize_variables(&hMapFile))
        return 1;

    usual_calculation();
    // {
    //     char * str_exp = input_String("");
    //     __INFIX__ I_exp = convert_string_to_INFIX(str_exp);

    //     substitude_variables(&I_exp, NULL);

    //     free(I_exp.tokens);
    //     free(str_exp);
    // }

    CloseHandle(hMapFile);
    return 0;
}

// -------------------------------------------- //

void substitude_variables(__INFIX__ *I_exp)
{
    char special_vars[NUM_OF_VARIABLES + 1] = {0};
    short int index_sv = 0;

    // scan for functions' special var
    for (short int i = 0; i < I_exp->size; i++)
    {
        if (I_exp->tokens[i - 3].operator != ',' && I_exp->tokens[i - 1].operator == ',' && I_exp->tokens[i].variable != '\0' && (I_exp->tokens[i + 1].operator == ',' || I_exp->tokens[i + 1].operator == '='))
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

    // variable_set[0].num = EULER_NUMBER / 7.0;

    return true;
}

void usualcal_display_help()
{
    const char *help[] = {
        "[_MODE_] Usual Calculation\n",
        "### Shortcut keys:",
        "Esc       : Exit mode",
        "Ctrl + O  : Open menu",
        "Ctrl + L  : See list of available function",
        "Ctrl + C  : See list of available constant",
        "Ctrl + D  : Clear screen",
        "Enter ↳   : Assign value for variables and calculate",
        "\n### Tip:",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy.",
        "\nSameple expressions:\n",
        "integral( 5pi/3 * abs( sin( (pi/3) * t - 2pi/5 ) ) , t , 0 , sqrt.5)\n",
        "dif(e^( 1/x ) , x = sqrt.5) - ln2\n",
        "2e/5 - 3pi/7 + sinh(arctanh( pi/6 )) + ln2 ^ e\n",
        "100!\n",
        "gamma(7) - 7!\n"};

    short int help_size = sizeof(help) / sizeof(help[0]);

    for (short int i = 0; i < help_size; i++)
        printf("%s\n", help[i]);

    system("pause >nul");
}

void display_const()
{
    puts("Available constants:\n");
    {
        const char *list_of_const[] = {
            "e = 2.718281828459045\n",
            "pi = 3.14159265358979323846\n",
            "g = 9.80665\n",
            "c = 299792458\n",
            "ln2 = 0.69314718055994530942\n",
            "sqrt3 = 1.73205080756887729353\n",
            "sqrt2 = 1.41421356237309504880\n",
            "sqrt.5 = 0.707106781186547524\n"};

        short int list_size = sizeof(list_of_const) / sizeof(list_of_const[0]);

        for (short int i = 0; i < list_size; i++)
            puts(list_of_const[i]);

        puts("\nPress V to see stored variables . . .\n");
    }

    int input_code = _getch();

    if (input_code != 'v' && input_code != 'V')
        return;

    puts("\n---Stored variables---\n\n");

    {
        HANDLE dc_hMapFile;
        shared_variables *stored_var;

        dc_hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, SHARED_MEM_NAME);
        if (!dc_hMapFile || dc_hMapFile == INVALID_HANDLE_VALUE)
            return;

        stored_var = (shared_variables *)MapViewOfFile(dc_hMapFile,
                                                       FILE_MAP_ALL_ACCESS,
                                                       0,
                                                       0,
                                                       sizeof(shared_variables) * NUM_OF_VARIABLES);
        //
        if (!stored_var)
        {
            CloseHandle(dc_hMapFile);
            return;
        }

        for (short int i = 0; i < NUM_OF_VARIABLES; i++)
            printf("  %c = %.10lf\n", stored_var[i].var_name, stored_var[i].num);

        UnmapViewOfFile(stored_var);
        CloseHandle(dc_hMapFile);
    }

    system("pause >nul");
}

void usualcal_display_func()
{
    const char *list_of_func[] = {
        "1/ Trigonometric functions: sin(), cos(), tan(), cot(), sec(), csc().\n\n",
        "2/ Inverse trigonometric functions: arcsin(), arccos(), arctan(), arccot(), arcsec(), arccsc().\n\n",
        "3/ Hyperbolic functions: sinh(), cosh(), tanh(), coth(), sech(), csch().\n\n",
        "4/ Inverse hyperbolic functions: arcsinh(), arccosh(), arctanh(), arccoth(), arcsech(), arccsch().\n\n",
        "5/ Square root function: sqrt().\n\n"
        "6/ Cube root function: cbrt().\n\n",
        "7/ Absolute value function: abs().\n\n",
        "8/ Natural logarithm function: ln().\n\n",
        "9/ Logarithm base 10 function: lg().\n\n",
        "10/ Gamma function: gamma().\n\n",
        "11/ Ceiling function: ceil().\n\n",
        "12/ Floor function: floor().\n\n",
        "13/ The lambert W function: lambertw().\n\n",
        "\n/*---------- Special Functions ----------*\\\n\n",
        "1/ Differentiation: ddx( function , variable = expression )\n",
        "\tThis function find the derivative of a function at a certain point. Examples:\n",
        "\t\tddx( 3x^3 - 2x^2 + 6.6x , x = 3.2 )  --- Result: 85.96\n",
        "\t\tddx( e^( -1 / k ) , k = pi - e)  --- Result: 0.5256...\n",
        "2/ Integration: integral( function , varibale , a , b )\n",
        "\tThis function find the integral of a function in the range a -> b, where a and b can be an expression. Example:\n",
        "\t\tintegral( ln(x + pi) , x , 9 , 10)   --- Result: 2.53673...\n",
        "3/ Sigma-sum or sum of a sequence: sumsequence( function , variable , start value , end value , step )\n",
        "\tThis function calculate the total sum of a sequence, where start | end value & step can be an expression. Examples:\n",
        "\t\tsumsequence( n , n , 1 , 100 , 1 )   --- Result: 5050\n",
        "\t\tsumsequence( k / (k - 1) , k , 0, 100, pi/3)   --- Result: 121.0142376...\n",
        "4/ Product of a sequence: productsequence( function , variable , start value , end value , step )\n",
        "\tThis function calculate the product of a sequence, where start | end value & step can be an expression. Example:\n",
        "\t\tproductsequence( (p + 1) / (p - 1), p , 2, 9, e/2 - pi/6)   --- Result: 75.634856...\n",
        "5/ Greatest Common Divisor: GCD( integer 1 , integer 2 )\n",
        "\tThis function calculate the GCD of 2 expressions, where integer 1 > integer 2. Example:\n",
        "\t\tGCD(12, 30)   --- Result: 6\n",
        "6/ Least Common Multiplier: LCM( integer 1 , integer 2 )\n",
        "\tThis function calculate the LCM of 2 expressions, where integer 1 > integer 2. Example:\n",
        "\t\tLCM(19, 30)   --- Result: 570\n",
        "7/ Permutations: permutations( integer 1 , integer 2 )\n",
        "\tThis probabilistic function calculate the number of permutations. Example:\n",
        "\t\tpermutations(5, 3)   --- Result: 60\n",
        "8/ Combinations: combinations( integer 1 , integer 2 )\n",
        "\tThis probabilistic function calculate the number of combinations. Example:\n",
        "\t\tcombinations(20, 5)   --- Result: 15504\n",
        "9/ Logarithm: log( base , expression )\n",
        "\tThis function calculate the logarithm where the base & the expression > 0. Example:\n",
        "\t\tlog(2, 10)   --- Result: 3.3219...\n"};

    short int list_size = sizeof(list_of_func) / sizeof(list_of_func[0]);

    for (short int i = 0; i < list_size; i++)
        puts(list_of_func[i]);
    system("pause >nul");
}

bool open_new_process(const char *feature, bool get_input)
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
    if (get_input)
        WaitForSingleObject(pi.hProcess, INFINITE);

    // Clean up process handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

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

bool central_control()
{
    if (open_menu)
    {
        display_menu();
        open_menu = false;
    }

    print_each_char(30, "\nChoose mode: ");
    int user_option = input_int();

    switch (user_option)
    {
    case 1:
    {
        system("cls");
        usual_calculation();
        break;
    }
    case 2:
    {
        system("cls");
        _complex_();
        break;
    }
    default:
        esc_win = true;
        break;
    }

    if (esc_win)
        return false;
    return true;
}

void display_menu()
{
    system("cls");
    const char *mode_list[] = {
        "0/ Close window",
        "1/ Usual Calculation",
        "2/ Complex"};
    int size = sizeof(mode_list) / sizeof(mode_list[0]);
    for (int i = 0; i < size; i++)
    {
        puts(mode_list[i]);
        delay(40);
    }
}

void usual_calculation()
{
    puts("[_MODE_] Usual Calculation");
    delay(40);
    puts("Press [ Ctrl + G ] for help & guidance");
    delay(40);
    puts("↓ Type your expression ↓");

    int input_code;
    int input_line = 3, output_line = 6;
    int top_barrier = input_line;
    int win_width, win_height;
    int input_index = 0;
    int C_X = 0, C_Y = top_barrier;

    getWinSize(&win_width, &win_height);
    win_width--;

    string_ raw_input;
    raw_input.Len = 0;
    raw_input.Content = create_new_buffer_with_sizeof(win_width * (output_line - input_line));

    move_cursor(input_line, 0);
    while (1)
    {
        static double result;

        if (!kbhit())
        {
            __INFIX__ I_exp = convert_string_to_INFIX(raw_input.Content);

            substitude_variables(&I_exp);

            result = evaluate_I_exp(I_exp);

            free(I_exp.tokens);

            move_cursor(output_line, 0);
            clear_line_in_range(output_line, output_line + 3);

            // print out result
            if (raw_input.Content[0] != '\0')
            {
                if (isfinite(result))
                {
                    if (is_integer(result) && (result < (double) INT_MAX && result > (double) INT_MIN))
                        printf(" = %d", (int) result);
                    else
                        printf(" = %.17lf", result);
                }
                else
                    puts("Syntax Error!");
            }

            move_cursor(C_Y, C_X);
        }

        input_code = _getch();

        if ((input_code >= 'a' && input_code <= 'z') ||
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
            input_code == '=')
        {
            if (is_integer(((double)input_index) / ((double)win_width)) && C_X != 0)
            {
                input_line++;
                C_X = 0;
            }

            if (input_index == 0 && input_code == ' ')
                continue;
            raw_input.Content[input_index++] = input_code;
            raw_input.Len = input_index;

            move_cursor(input_line, C_X);
            putchar(input_code);

            get_cursor_position(&C_X, &C_Y);
        }

        // Backspace - Delete input
        else if (input_code == 8)
        {
            if (C_X != 0)
            {
                move_cursor(C_Y, C_X - 1);
                putchar(' ');
                move_cursor(C_Y, C_X - 1);
            }
            else if (C_Y != top_barrier)
            {
                move_cursor(C_Y - 1, win_width - 1);
                putchar(' ');
                move_cursor(C_Y - 1, win_width - 1);

                input_line--;
            }

            if (input_index > 0)
            {
                raw_input.Content[--input_index] = '\0';
                (raw_input.Len)--;
            }
            get_cursor_position(&C_X, &C_Y);
        }

        // assign var & compute
        else if (input_code == 13)
        {
            open_new_process("global-assign-variables", true);
        }

        // Esc
        else if (input_code == 27)
        {
            esc_win = true;
            break;
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

        // Ctrl + O
        else if (input_code == 15)
        {
            open_menu = true;
            break;
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("usualcal-display-help", false);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            memset(raw_input.Content, 0, raw_input.Len);
            input_index = 0;
            input_line = top_barrier;
            C_X = 0;
            C_Y = input_line;
            clear_line_in_range(top_barrier, win_height - 2);
            move_cursor(input_line, 0);
        }
    }

    free(raw_input.Content);
}

void _complex_() {}
