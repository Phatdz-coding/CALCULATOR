#include <MY_LIB/global_var.h>
#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>
#include <MY_LIB/sovle_equations.h>
#include <MY_LIB/cal_info.h>
#include <MY_LIB/input_box.h>

// --------------functions and menu------------- //

void handle_child_process(const char *[]);

void usual_calculation();

void derivative_calculator();

void integral_calculator();

void solve_quadratic_equation();

void solve_cubic_equation();

void solve_quartic_equation();

void solve_n_degree_poly_equation();

void solve_equation();

bool central_control();

void display_const();

// -------------------------------------------- //

int main(const int num_of_arg, const char *arg[])
{
    turn_on_advanced_character_mode();

    // get signal and work on child processes
    if (num_of_arg > 1)
    {
        handle_child_process(arg);
        return 0;
    }

    // initialize variable set
    HANDLE hMapFile;
    if (!initialize_variables(&hMapFile))
        return 1;

    // open_menu = true;
    // while (central_control())
    //     ;

    solve_equation();

    CloseHandle(hMapFile);
    return 0;
}

// -------------------------------------------- //

void handle_child_process(const char *arg[])
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
    else if (!strcmp(arg[1], "solve_quadratic-display-help"))
        solve_quadratic_display_help();
    else if (!strcmp(arg[1], "solve_cubic-display-help"))
        solve_cubic_display_help();
    else if (!strcmp(arg[1], "solve_quartic-display-help"))
        solve_quartic_display_help();
    else if (!strcmp(arg[1], "solve_n_degree_poly-display-help"))
        solve_n_degree_poly_display_help();
    else if (!strcmp(arg[1], "solve_equation-display-help"))
        solve_equation_display_help();
    else if (!strcmp(arg[1], "solve_equation-display-results"))
        solve_equation_display_result();
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

    puts("\n▤▤▤ Stored variables\n");

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

        // for (short int i = 0; i < NUM_OF_VARIABLES; i++)
        //     printf("  %c = %.10lf\n", stored_var[i].var_name, stored_var[i].num);

        for (unsigned short int i = 0; i < NUM_OF_VARIABLES; i++)
        {
            if (is_zero(stored_var[i].num))
                continue;

            printf("\n  %c = ", stored_var[i].var_name);
            display_number(stored_var[i].num);
        }

        puts("\nOther variables are equal to zero");

        UnmapViewOfFile(stored_var);
        CloseHandle(dc_hMapFile);
    }

    system("pause >nul");
}

bool central_control()
{
    system("cls");
    if (open_menu)
    {
        display_menu();
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
    case 4:
        solve_quadratic_equation();
        break;
    case 5:
        solve_cubic_equation();
        break;
    case 6:
        solve_quartic_equation();
        break;
    case 7:
        solve_n_degree_poly_equation();
        break;
    case 8:
        solve_equation();
        break;
    default:
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------------------------------------------------------- //

void usual_calculation()
{
    puts("[_MODE_] Usual Calculation");
    delay(40);
    puts("Press [ Ctrl + G ] For help\n");
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
                display_number(result);
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
    puts("Press [Ctrl + G] For help");
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

void integral_calculator() {}

void solve_quadratic_equation()
{
    puts("[_MODE_] Solve Quadratic Equation");
    delay(40);
    puts("Press [Ctrl + G] For help\n");
    delay(40);
    puts("Quadratic equation form: ax² + bx + c = 0 (where a, b & c are real numbers and a ≠ 0)");
    delay(40);
    puts("a = 0\nb = 0\nc = 0\n[Press Shift + a, b, c to switch coefficients]");

    short int input_code = 0;
    const unsigned short int inputvalue_coef_line = 8;

    double a = 0, b = 0, c = 0;

    while (1)
    {
        input_code = _getch();

        if (input_code == 'A')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("a =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &a, "solve_quadratic-display-help");

            if (status == -1)
                break;

            clear_line_(4);
            printf("a = ");
            display_number(a);
        }

        else if (input_code == 'B')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("b =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &b, "solve_quadratic-display-help");

            if (status == -1)
                break;

            clear_line_(5);
            printf("b = ");
            display_number(b);
        }

        else if (input_code == 'C')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("c =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &c, "solve_quadratic-display-help");

            if (status == -1)
                break;

            clear_line_(6);
            printf("c = ");
            display_number(c);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_quadratic-display-help", false);
        }

        // Ctrl + S
        else if (input_code == 19 && a != 0.0)
        {
            clear_line_in_range(12, 17);
            move_cursor(12, 0);
            printf("Delta △ = ");
            display_number(b * b - 4 * a * c);
            putchar('\n');
            puts("▶Solutions◀");
            gsl_complex x1, x2;
            short int solving_status = se_sovle_quadratic_equation(a, b, c, &x1, &x2);

            se_display_quadratic_solutions(x1, x2);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            system("cls");

            a = 0;
            b = 0;
            c = 0;

            puts("[_MODE_] Solve Quadratic Equation");
            delay(40);
            puts("Press [Ctrl + G] For help\n");
            delay(40);
            puts("Quadratic equation form: ax² + bx + c = 0 (where a, b & c are real numbers and a ≠ 0)");
            delay(40);
            puts("a = 0\nb = 0\nc = 0\n[Press Shift + a, b, c to switch coefficients]");
        }

        // Esc
        else if (input_code == 27)
        {
            break;
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }
}

void solve_cubic_equation()
{
    puts("[_MODE_] Solve Cubic Equation");
    delay(40);
    puts("Press [Ctrl + G] For help\n");
    delay(40);
    puts("Cubic equation form: ax³ + bx² + cx + d = 0 (where a, b, c & d are real numbers and a ≠ 0)");
    delay(40);
    puts("a = 0\nb = 0\nc = 0\nd = 0\n[Press Shift + a, b, c, d to switch coefficients]");

    short int input_code = 0;
    const unsigned short int display_coef_a_line = 4;
    const unsigned short int inputvalue_coef_line = 9;

    double a = 0, b = 0, c = 0, d = 0;

    while (1)
    {
        input_code = _getch();

        if (input_code == 'A')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("a =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &a, "solve_cubic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line);
            printf("a = ");
            display_number(a);
        }

        else if (input_code == 'B')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("b =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &b, "solve_cubic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 1);
            printf("b = ");
            display_number(b);
        }

        else if (input_code == 'C')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("c =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &c, "solve_cubic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 2);
            printf("c = ");
            display_number(c);
        }

        else if (input_code == 'D')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("d =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &d, "solve_cubic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 3);
            printf("d = ");
            display_number(d);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_cubic-display-help", false);
        }

        // Ctrl + S
        else if (input_code == 19 && a != 0.0)
        {
            clear_line_in_range(13, 18);
            move_cursor(13, 0);
            printf("Delta △ = ");
            display_number(b * b + 18 * a * b * c * d + 6 * c * c - 4 * d * c * c - 46 * d * d - 27 * a * d * d);
            putchar('\n');
            puts("▶Solutions◀");
            gsl_complex x1, x2, x3;
            short int solving_status = se_solve_cubic_equation(a, b, c, d, &x1, &x2, &x3);

            se_display_cubic_equation_solutions(x1, x2, x3);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            system("cls");

            a = 0;
            b = 0;
            c = 0;
            d = 0;

            puts("[_MODE_] Solve Cubic Equation");
            delay(40);
            puts("Press [Ctrl + G] For help\n");
            delay(40);
            puts("Quadratic equation form: ax³ + bx² + cx + d = 0 (where a, b, c & d are real numbers and a ≠ 0)");
            delay(40);
            puts("a = 0\nb = 0\nc = 0\nd = 0\n[Press Shift + a, b, c, d to switch coefficients]");
        }

        // Esc
        else if (input_code == 27)
        {
            break;
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }
}

void solve_quartic_equation()
{
    puts("[_MODE_] Solve Quartic Equation");
    delay(40);
    puts("Press [Ctrl + G] For help\n");
    delay(40);
    puts("Quartic equation form: ax⁴ + bx³ + cx² + dx + e = 0 (where a, b, c, d & e are real numbers and a ≠ 0)");
    delay(40);
    puts("a = 0\nb = 0\nc = 0\nd = 0\ne = 0\n[Press Shift + a, b, c, d, e to switch coefficients]");

    short int input_code = 0;
    const unsigned short int display_coef_a_line = 4;
    const unsigned short int inputvalue_coef_line = 10;

    double a = 0, b = 0, c = 0, d = 0, e = 0;

    while (1)
    {
        input_code = _getch();

        if (input_code == 'A')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("a =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &a, "solve_quartic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line);
            printf("a = ");
            display_number(a);
        }

        else if (input_code == 'B')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("b =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &b, "solve_quartic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 1);
            printf("b = ");
            display_number(b);
        }

        else if (input_code == 'C')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("c =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &c, "solve_quartic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 2);
            printf("c = ");
            display_number(c);
        }

        else if (input_code == 'D')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("d =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &d, "solve_quartic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 3);
            printf("d = ");
            display_number(d);
        }

        else if (input_code == 'E')
        {
            move_cursor(inputvalue_coef_line, 0);
            printf("e =");

            short int status = ib_2_3_4_poly_equation(inputvalue_coef_line, 3, inputvalue_coef_line + 3, &e, "solve_quartic-display-help");

            if (status == -1)
                break;

            clear_line_(display_coef_a_line + 4);
            printf("e = ");
            display_number(e);
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_quartic-display-help", false);
        }

        // Ctrl + S
        else if (input_code == 19 && a != 0.0)
        {
            clear_line_in_range(14, 19);
            move_cursor(14, 0);
            // display delta
            printf("Delta △ = ");
            display_number(256 * pow(a, 5) * pow(e, 3) -
                           192 * pow(a, 2) * b * d * pow(e, 2) -
                           128 * pow(a, 2) * pow(c, 2) * pow(e, 2) +
                           144 * pow(a, 2) * c * pow(d, 2) * e -
                           27 * pow(a, 2) * pow(d, 4) +
                           144 * a * pow(b, 2) * c * pow(e, 2) -
                           6 * a * pow(b, 2) * pow(d, 2) * e -
                           80 * a * b * pow(c, 2) * d * e +
                           18 * a * b * c * pow(d, 3) +
                           16 * a * pow(c, 4) * e -
                           4 * a * pow(c, 3) * pow(d, 2) -
                           27 * pow(b, 4) * pow(e, 2) +
                           18 * pow(b, 3) * c * d * e -
                           4 * pow(b, 3) * pow(d, 3) -
                           4 * pow(b, 2) * pow(c, 3) * e +
                           pow(b, 2) * pow(c, 2) * pow(d, 2));
            putchar('\n');
            puts("▶Solutions◀");
            gsl_complex x1, x2, x3, x4;
            short int solving_status = se_solve_quartic_equation(a, b, c, d, e, &x1, &x2, &x3, &x4);

            se_display_quartic_equation_solutions(x1, x2, x3, x4);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            system("cls");

            a = 0;
            b = 0;
            c = 0;
            d = 0;
            e = 0;

            puts("[_MODE_] Solve Quartic Equation");
            delay(40);
            puts("Press [Ctrl + G] For help\n");
            delay(40);
            puts("Quartic equation form: ax⁴ + bx³ + cx² + dx + e = 0 (where a, b, c, d & e are real numbers and a ≠ 0)");
            delay(40);
            puts("a = 0\nb = 0\nc = 0\nd = 0\ne = 0\n[Press Shift + a, b, c, d, e to switch coefficients]");
        }

        // Esc
        else if (input_code == 27)
        {
            break;
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }
}

void solve_n_degree_poly_equation()
{
    puts("[__MODE__] Solve nᵗʰ degree polynomial equation");
    delay(40);
    puts("Press [Ctrl + G] For help\n");
    delay(40);
    puts("The nᵗʰ degree polynomial equation form:");
    puts("a₀xⁿ + a₁xⁿ⁻¹ + a₂xⁿ⁻² + . . . + aₙ₋₁x + aₙ = 0 (Where a₀ , a₁ , ... , aₙ are real numbers and a₀ ≠ 0 | And n ≥ 5)");

    short int degree;
    unsigned short int numof_coef;

    double *coefficients = NULL;

    while (1)
    {
        printf("Enter degree: ");
        degree = (short int)input_int();
        if (degree <= 4)
        {
            puts("⚠  Invalid input ⚠");
            continue;
        }

        numof_coef = degree + 1;

        coefficients = (double *)calloc(numof_coef, sizeof(double));
        if (coefficients == NULL)
        {
            perror("Failed to calloc coefficients");
            return;
        }

        bool invalid_input = false;

        for (unsigned short int i = 0; i < numof_coef; i++)
        {
            int C_Y;
            get_cursor_position(NULL, &C_Y);
            printf("a_[%d] = ", i);

            short int input_status = solve_poly_get_coef(coefficients + i);

            // Esc
            if (input_status == 27)
            {
                free_coefficients(&coefficients);
                return;
            }

            if (!isfinite(coefficients[i]) || coefficients[0] == 0.0)
            {
                puts("⚠  Syntax Error ⚠");
                --i;
                continue;
            }

            int pre_C_Y = C_Y;
            get_cursor_position(NULL, &C_Y);

            clear_line_in_range(pre_C_Y, C_Y);
            printf("a_[%d] = ", i);
            display_number(coefficients[i]);
            putchar('\n');
        }

        // display the equation
        printf("Your %dᵗʰ degree polynomial equation:\n", degree);
        for (unsigned short int a = 0, n = degree; a < numof_coef && n >= 0; a++, n--)
        {
            if (coefficients[a] != 0.0)
            {
                if (coefficients[a] > 0.0)
                {
                    if (a != 0)
                        putchar('+');
                    display_number_with_max_3_dec_places(coefficients[a]);
                }

                else
                {
                    if (a != 0)
                        putchar('-');
                    display_number_with_max_3_dec_places(-coefficients[a]);
                }

                if (n > 0)
                {
                    putchar('x');
                    print_super_script_number(n);
                }
                putchar(' ');
            }
        }

        puts("\nHas the following solutions:\n");

        gsl_complex *solutions;
        se_solve_polynomial_equation(coefficients, degree, &solutions);

        // display solutions
        for (unsigned short int i = 0; i < degree; i++)
        {
            putchar('x');
            print_sub_script_number(i + 1);
            printf(" = ");
            se_display_complex_number_2(solutions[i]);
            putchar('\n');
        }

        if (solutions != NULL)
        {
            free(solutions);
            solutions = NULL;
        }
        free_coefficients(&coefficients);

        puts("Press [Esc] to go to menu OR press any key to continue . . .");
        short int input_code = _getch();
        if (input_code == 27)
            return;
        else if (input_code == 4)
        {
            system("cls");

            puts("[__MODE__] Solve nᵗʰ degree polynomial equation");
            delay(40);
            puts("Press [Ctrl + G] For help\n");
            delay(40);
            puts("The nᵗʰ degree polynomial equation form:");
            puts("a₀xⁿ + a₁xⁿ⁻¹ + a₂xⁿ⁻² + . . . + aₙ₋₁x + aₙ = 0 (Where a₀ , a₁ , ... , aₙ are real numbers and a₀ ≠ 0 | And n ≥ 5)");
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_n_degree_poly-display-help", false);
            _getch();
        }
    }
}

void solve_equation()
{
    puts("[__MODE__] Solve Any Equation");
    delay(40);
    puts("Press [Ctrl + G] For help");

    const unsigned short int fx_line = 4;
    const unsigned short int variable_line = fx_line + 4;
    const unsigned short int l_bound_line = variable_line + 2;
    const unsigned short int u_bound_line = l_bound_line + 2;

    const unsigned short int output_line = u_bound_line + 4;

    int win_w;
    getWinSize(&win_w, NULL);

    unsigned short int max_fx_len = (variable_line - fx_line) * win_w;
    short int input_code = 0;

    char *str_function = create_new_buffer_with_sizeof(1);
    char var = 'x';
    double l_bound = -1.0, u_bound = 1.0;

    while (1)
    {
        move_cursor(fx_line - 1, 0);
        printf("Equation form: f(%c) = 0\nf(%c) = %s\n\n\n\nSolve for: %c\nSolve the equation in range:\nLower bound = %.6lf\n\n\nUpper bound = %.6lf\n\n\n", var, var, str_function, var, l_bound, u_bound);

        input_code = _getch();

        clear_line_in_range(output_line, output_line + 3);

        if (input_code == 0)
        {
            input_code = _getch();

            // F1
            if (input_code == 59)
            {
                clear_line_in_range(fx_line, variable_line - 1);
                printf("f(%c) = ", var);
                free_buffer(&str_function);
                str_function = ib_se_get_function();
            }

            // F2
            else if (input_code == 60)
            {
                move_cursor(variable_line, 11);
                while (1)
                {
                    var = _getch();

                    if (((var >= 'a' && var <= 'z') || (var >= 'A' && var <= 'Z')) && var != 'c' && var != 'e' && var != 'g')
                    {
                        break;
                    }
                }
            }

            // F3
            else if (input_code == 61)
            {
                ib_2_3_4_poly_equation(l_bound_line + 1, 0, l_bound_line + 2, &l_bound, "solve_equation-display-help");
            }

            // F4
            else if (input_code == 62)
            {
                ib_2_3_4_poly_equation(u_bound_line + 2, 0, u_bound_line + 3, &u_bound, "solve_equation-display-help");
            }

            // F5 - start solving section
            else if (input_code == 63)
            {
                start_solving_section(str_function, var, l_bound, u_bound, output_line);
            }
        }

        // Ctrl + G
        else if (input_code == 7)
        {
            open_new_process("solve_equation-display-help", false);
        }

        // Ctrl + D
        else if (input_code == 4)
        {
            clear_line_in_range(fx_line - 1, output_line + 3);

            free_buffer(&str_function);
            str_function = create_new_buffer_with_sizeof(1);
            l_bound = -1;
            u_bound = 1;
            var = 'x';
        }

        // Esc
        else if (input_code == 27)
        {
            break;
        }

        else if (input_code == 224)
        {
            _getch();
        }
    }

    free_buffer(&str_function);
}




