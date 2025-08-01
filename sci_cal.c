#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>

#define NUM_OF_VARIABLES 49
#define SHARED_MEM_NAME "Local\\SharedVariables"
#define PROGRAM_NAME "sci_cal.exe"

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
void derivative_calculator();
void display_menu();
void display_const();
void usualcal_display_func();
void usualcal_display_help();
void derivative_calculator_display_help();
void derivative_calculator_display_func();
void integral_calculator();
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
    // derivative_calculator();
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
        else if (!strcmp(arg[1], "--der-cal-display-help"))
            derivative_calculator_display_help();
        else if (!strcmp(arg[1], "--der-cal-display-func"))
            derivative_calculator_display_func();
        return 0;
    }

    // initialize variable set
    HANDLE hMapFile;
    if (!initialize_variables(&hMapFile))
        return 1;

    open_menu = true;
    while (central_control())
        ;

    CloseHandle(hMapFile);
    return 0;
}

// -------------------------------------------- //

void derivative_calculator_display_func()
{
    const char *list_of_func[] = {
        "1/ Trigonometric functions: sin(), cos(), tan(), cot(), sec(), csc().\n",
        "2/ Inverse trigonometric functions: arcsin(), arccos(), arctan(), arccot(), arcsec(), arccsc().\n",
        "3/ Hyperbolic functions: sinh(), cosh(), tanh(), coth(), sech(), csch().\n",
        "4/ Inverse hyperbolic functions: arcsinh(), arccosh(), arctanh(), arccoth(), arcsech(), arccsch().\n",
        "5/ Square root function: sqrt().\n"
        "6/ Cube root function: cbrt().\n",
        "7/ Absolute value function: abs().\n",
        "8/ Natural logarithm function: ln().\n",
        "9/ Logarithm base 10 function: lg().\n",
        "10/ Gamma function: gamma().\n",
        "11/ Ceiling function: ceil().\n",
        "12/ Floor function: floor().\n",
        "13/ Lambert W function: lambertw().\n",
        "14/ Logarithm function: log(base , expression)\n"};
    //

    short int list_size = sizeof(list_of_func) / sizeof(list_of_func[0]);

    for (short int i = 0; i < list_size; i++)
        puts(list_of_func[i]);

    puts("\n### NOTE: These functions are available in this mode");

    system("pause >nul");
}

void derivative_calculator_display_help()
{
    const char *help[] = {
        "[_MODE_] Derivative Calculator\n",
        "### Shortcut keys:",
        "Esc      : Go to menu",
        "Enter    : Start differentiating (Leave the input field empty to find the next higher derivative)",
        "Ctrl + D : Refresh screen and data",
        "\n### Tip:",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy.",
        "\n### Sample functions:\n",
        "3x^8 - ex^pi + 2   --- Differentiate with respect to: x",
        "k^k - x^2 --- Differentiate with respect to: k",
        "pi - 3m^a - ln(a + ln2) --- Differentiate with respect to: a"};

    short int help_size = sizeof(help) / sizeof(help[0]);

    for (short int i = 0; i < help_size; i++)
        puts(help[i]);

    system("pause >nul");
}

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
        "Esc       : Go to menu",
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

    puts("### NOTE: These functions are availablle int this mode");

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
    system("cls");
    if (open_menu)
    {
        display_menu();
        open_menu = false;
    }

    print_each_char(30, "\nChoose mode: ");
    int user_option = input_int();

    system("cls");

    switch (user_option)
    {
    case 1:
        usual_calculation();
        break;
    case 2:
        derivative_calculator();
        break;
    case 3:
        integral_calculator();
        break;
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
        "2/ Derivative Calculator",
        "3/ Integral Calculator (in-dev)"};
    int size = sizeof(mode_list) / sizeof(mode_list[0]);
    for (int i = 0; i < size; i++)
    {
        puts(mode_list[i]);
        delay(40);
    }
}

// ---------------------------------------------------------------------------------------------------------------------- //

void usual_calculation()
{
    puts("[_MODE_] Usual Calculation");
    delay(40);
    puts("Press [ Ctrl + G ] for help & guidance\n");
    delay(40);
    puts("↓ Type your expression ↓");

    int input_code;
    int input_line = 4, output_line = 7;
    int top_barrier = input_line;
    int win_width, win_height;
    int input_index = 0;
    int C_X = 0, C_Y = top_barrier;
    bool new_input = false;

    getWinSize(&win_width, &win_height);
    // win_width--;

    int max_input_len = (output_line - input_line) * win_width;

    string_ raw_input;
    raw_input.Len = 0;
    raw_input.Content = create_new_buffer_with_sizeof(win_width * (output_line - input_line));

    move_cursor(input_line, 0);
    while (1)
    {
        static double result;

        if (new_input)
        {
            __INFIX__ I_exp = convert_string_to_INFIX(raw_input.Content);

            substitude_variables(&I_exp);

            result = evaluate_I_exp(I_exp);

            free(I_exp.tokens);

            // move_cursor(output_line, 0);
            clear_line_in_range(input_line, output_line + 2);

            // print out result
            printf("%s", raw_input.Content);

            get_cursor_position(&C_X, &C_Y);

            if (raw_input.Content[0] != '\0')
            {
                putchar('\n');
                if (isfinite(result))
                {
                    if (is_integer(result) && (result < (double)INT_MAX && result > (double)INT_MIN))
                        printf(" = %d", (int)result);
                    else
                        printf(" = %.17lf", result);
                }
                else
                    puts(" __Syntax Error__");
            }

            move_cursor(C_Y, C_X);

            new_input = false;
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
            if (input_index == 0 && input_code == ' ')
                continue;
            raw_input.Content[input_index++] = input_code;
            raw_input.Len = input_index;

            new_input = true;
        }

        // Backspace - Delete input
        else if (input_code == 8)
        {

            if (input_index > 0)
            {
                raw_input.Content[--input_index] = '\0';
                (raw_input.Len)--;
                new_input = true;
            }
        }

        // assign var & compute
        else if (input_code == 13)
        {
            open_new_process("global-assign-variables", true);
            new_input = true;
        }

        // Esc
        else if (input_code == 27)
        {
            open_menu = true;
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

void derivative_calculator()
{
    puts("[_MODE_] Derivative Calculator");
    delay(40);
    puts("[Ctrl + G] For help");
    delay(40);
    // puts("Function:");

    int win_w, win_h;

    getWinSize(&win_w, &win_h);

    short int input_code = 0;
    int input_index = 0;
    int max_index = win_w * 2;
    bool new_input = false;
    bool invalid = false;
    bool use_result = false;
    int input_line;

    __INFIX__ I_func = {0, NULL}, I_derivative = {0, NULL};
    string_ str_derivative = {0, NULL};
    char *str_function = create_new_buffer_with_sizeof(max_index);

    while (1)
    {
        puts("\n[F] Function:");
        if (invalid)
        {
            printf("Invalid function or operator !!!");
            invalid = false;
        }
        get_cursor_position(NULL, &input_line);

        // prepare for the next / new input
        input_code = 0;
        memset(str_function, '\0', max_index);
        input_index = 0;
        new_input = false;

        while (1)
        {
            if (new_input)
            {
                short int n = win_h - input_line;
                if (n <= 3)
                {
                    for (short int l = 0; l < 4 - n; l++)
                        putchar('\n');
                    input_line -= 4 - n;
                }

                clear_line_in_range(input_line, input_line + 2);
                printf("%s", str_function);

                new_input = false;
            }

            // input_code = 3;
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
                input_index < max_index - 1)
            {
                if (input_index == 0 && input_code == ' ')
                    continue;
                str_function[input_index++] = input_code;

                new_input = true;
            }

            // del
            else if (input_code == 8 && input_index > 0)
            {
                str_function[--input_index] = '\0';
                new_input = true;
            }

            // Esc
            else if (input_code == 27)
            {
                if (str_function != NULL)
                    free(str_function);
                if (I_derivative.tokens != NULL)
                    free(I_derivative.tokens);
                if (I_func.tokens != NULL)
                    free(I_func.tokens);

                str_function = NULL;
                I_derivative.tokens = NULL;
                I_func.tokens = NULL;

                open_menu = true;
                return;
            }

            // enter
            else if (input_code == 13)
            {
                if (str_function[0] != '\0')
                {
                    if (I_derivative.tokens != NULL)
                    {
                        free(I_derivative.tokens);
                        I_derivative.size = 0;
                        I_derivative.tokens = NULL;
                    }
                    if (I_func.tokens != NULL)
                    {
                        free(I_func.tokens);
                        I_func.size = 0;
                        I_func.tokens = NULL;
                    }
                    use_result = false;
                    break;
                }

                else if (str_function[0] == '\0' && I_derivative.tokens != NULL)
                {
                    printf("__ Use previous result __");
                    // if (I_func.tokens != NULL)
                    //     free(I_func.tokens);
                    use_result = true;
                    break;
                }
            }

            // clear screen
            else if (input_code == 4)
            {
                system("cls");

                puts("[_MODE_] Derivative Calculator");
                puts("[Ctrl + G] For help");
                puts("[F] Function:");

                memset(str_function, '\0', win_w * 2);
                input_index = 0;
                get_cursor_position(NULL, &input_line);

                if (I_derivative.tokens != NULL)
                    free(I_derivative.tokens);
                if (I_func.tokens != NULL)
                    free(I_func.tokens);
                if (str_derivative.Content != NULL)
                    free(str_derivative.Content);

                I_func.size = 0;
                I_derivative.size = 0;
                str_derivative.Len = 0;

                I_func.tokens = NULL;
                I_derivative.tokens = NULL;
                str_derivative.Content = NULL;

                use_result = false;
            }

            // ctrl + g
            else if (input_code == 7)
            {
                open_new_process("--der-cal-display-help", false);
            }

            // ctrl + c
            else if (input_code == 3)
            {
                open_new_process("display-const", false);
            }

            // ctrl + l
            else if (input_code == 12)
            {
                open_new_process("--der-cal-display-func", false);
            }

            // handle non-standard keys
            else if (input_code == 224)
            {
                input_code = _getch();
            }
        }

        // use new function
        if (!use_result)
        {
            I_func = convert_string_to_INFIX(str_function);
            // putchar('\n');
            // display_infix_exp(I_func);

            // check for special & invalid functions
            {
                invalid = false;
                for (short int i = 0; i < I_func.size; i++)
                {
                    if (I_func.tokens[i].operator == SPECIFIER_OF_DIF ||
                        I_func.tokens[i].operator == SPECIFIER_OF_INTEGRAL ||
                        I_func.tokens[i].operator == SPECIFIER_OF_SIGMA_SUM ||
                        I_func.tokens[i].operator == SPECIFIER_OF_PRODUCT_OF_SEQUENCE ||
                        I_func.tokens[i].operator == SPECIFIER_OF_GCD ||
                        I_func.tokens[i].operator == SPECIFIER_OF_LCM ||
                        I_func.tokens[i].operator == SPECIFIER_OF_COMBINATIONS ||
                        I_func.tokens[i].operator == SPECIFIER_OF_PERMUTATIONS)
                    {
                        invalid = true;
                        break;
                    }

                    // handle log function
                    else if (I_func.tokens[i].operator == SPECIFIER_OF_LOG)
                    {
                        short int index_log = i;
                        short int index_outer_bracket_open = i + 1;
                        short int index_colon;
                        short int index_outer_bracket_close;

                        // find outer close bracket
                        {
                            short int open_ = 0;
                            short int close_ = 0;
                            for (short int k = i + 1; k < I_func.size; k++)
                            {
                                if (I_func.tokens[k].operator == '(')
                                    open_++;
                                else if (I_func.tokens[k].operator == ')')
                                    close_++;

                                if (open_ == close_)
                                {
                                    index_outer_bracket_close = k;
                                    break;
                                }
                            }
                        }

                        // find colon
                        {
                            short int skip_colon = 0;
                            for (short int k = i + 2; k < index_outer_bracket_close; k++)
                            {
                                if (I_func.tokens[k].operator == ',' && skip_colon == 0)
                                {
                                    index_colon = k;
                                    break;
                                }

                                else if (I_func.tokens[k].operator == SPECIFIER_OF_LOG)
                                    skip_colon += 1;
                                else if (I_func.tokens[k].operator == ',' && skip_colon != 0)
                                    skip_colon--;
                            }
                        }

                        __INFIX__ replacement;
                        // replacement  = ln(exp) / ln(base)
                        replacement.size = 5 + index_outer_bracket_close - index_colon + index_colon - index_outer_bracket_open;
                        replacement.tokens = (_infix_ *)malloc(replacement.size * sizeof(_infix_));

                        for (short int k = 0; k < replacement.size; k++)
                        {
                            replacement.tokens[k].num = NAN;
                            replacement.tokens[k].operator = '\0';
                            replacement.tokens[k].variable = '\0';
                        }

                        replacement.tokens[0].operator = SPECIFIER_OF_LN;
                        replacement.tokens[1].operator = '(';

                        short int j = 2;
                        for (short int k = index_colon + 1; k < index_outer_bracket_close; k++, j++)
                        {
                            replacement.tokens[j].num = I_func.tokens[k].num;
                            replacement.tokens[j].operator = I_func.tokens[k].operator;
                            replacement.tokens[j].variable = I_func.tokens[k].variable;
                        }

                        replacement.tokens[j++].operator = ')';
                        replacement.tokens[j++].operator = '/';
                        replacement.tokens[j++].operator = SPECIFIER_OF_LN;
                        replacement.tokens[j++].operator = '(';

                        for (short int k = index_outer_bracket_open + 1; k < index_colon; k++, j++)
                        {
                            replacement.tokens[j].num = I_func.tokens[k].num;
                            replacement.tokens[j].operator = I_func.tokens[k].operator;
                            replacement.tokens[j].variable = I_func.tokens[k].variable;
                        }

                        replacement.tokens[j++].operator = ')';

                        substitude_result(&I_func, replacement, index_log, index_outer_bracket_close);

                        if (replacement.tokens != NULL)
                        {
                            free(replacement.tokens);
                            replacement.size = 0;
                            replacement.tokens = NULL;
                        }
                    }
                }

                if (invalid)
                {
                    clear_line_in_range(input_line - 2, input_line + 2);

                    free(I_func.tokens);
                    memset(str_function, '\0', max_index);
                    input_index = 0;

                    input_code = 0;

                    continue;
                }
            }
        }

        // use pre result
        else
        {
            _infix_ *temp = (_infix_ *)malloc((I_derivative.size) * sizeof(_infix_));
            if (temp != NULL)
            {
                free(I_func.tokens);
                I_func.tokens = temp;
                I_func.size = I_derivative.size;
                for (short int i = 0; i < I_derivative.size; i++)
                {
                    I_func.tokens[i].num = I_derivative.tokens[i].num;
                    I_func.tokens[i].operator = I_derivative.tokens[i].operator;
                    I_func.tokens[i].variable = I_derivative.tokens[i].variable;
                }
                // check
                // display_infix_exp(I_func);
                // printf("SIZE = %d", I_func.size);
            }
        }

        // get variable
        printf("\n[V] Differentiate with respect to: ");
        char var;

        do
        {
            // var = 'x';
            var = _getch();
        } while (var == 'e' || var == 'g' || var == 'c' || var < 'a' || var > 'z' || var < 'A' || var > 'z');
        putchar(var);
        putchar('\n');

        // differentiate the function
        if (I_derivative.tokens != NULL)
        {
            // putchar('\n');
            // display_infix_exp(I_derivative);
            // putchar('\n');
            free(I_derivative.tokens);
            I_derivative.size = 0;
            I_derivative.tokens = NULL;
        }

        I_derivative = differentiate_I_exp(I_func, var);

        // reformat the result for readability
        reformat_I_exp(&I_derivative);

        // display the result
        str_derivative = convert_INFIX_to_string(I_derivative);

        printf("[R] The derivative of the function is:\n");
        puts(str_derivative.Content);

        if (str_derivative.Content != NULL)
        {
            free(str_derivative.Content);
            str_derivative.Len = 0;
            str_derivative.Content = NULL;
        }
        // memset(str_derivative.Content, '\0', str_derivative.Len);
    }
}

void integral_calculator()
{
}