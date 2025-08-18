#ifndef CALCULATOR_INFO_H
#define CALCULATOR_INFO_H

#include <MY_LIB/inputsDisplays.h>

// ======================================================================================================= //
// ======================================================================================================= //
// ======================================================================================================= //

void display_menu();

void usualcal_display_func();

void usualcal_display_help();

void derivative_calculator_display_help();

void derivative_calculator_display_func();

void solve_quadratic_display_help();

void solve_n_degree_poly_display_help();

void solve_equation_display_help();

void solve_cubic_display_help();

void solve_quartic_display_help();

void solve_system_of_linear_equation_display_help();

// ======================================================================================================= //
// ======================================================================================================= //
// ======================================================================================================= //

void solve_system_of_linear_equation_display_help()
{
    const char *help[] = {
        "🔢 Solve System of Linear Equation\n",
        "### Shortcut keys:",
        "Esc                    : Go to menu OR quit input section",
        "F1                     : To start input number of unknown and coefficient",
        "Ctrl + L               : See list of available funtion",
        "Ctrl + C               : See list of available constant & variable",
        "Ctrl + D               : Refresh",
        "Ctrl + Enter           : Assign value for variables",
        "\n「 ✦ NOTE ✦ 」 You can only use [Ctrl + L] [Ctrl + C] [Ctrl + Enter] while working with coefficients"
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void solve_equation_display_help()
{
    const char *help[] = {
        "🔢 Solve Any Equation (single variable)\n",
        "### Shortcut keys:",
        "Esc                    : Go to menu",
        "F1                     : To type your function",
        "F2                     : Type your variable",
        "F3 & F4                : Type your expression to decide lower & upper bound",
        "F5                     : Start solving section",
        "Ctrl + L               : See list of available funtion",
        "Ctrl + C               : See list of available constant & variable",
        "Ctrl + D               : Refresh",
        "Ctrl + Enter           : Assign value for variables",
        "\n「 ✦ NOTE ✦ 」 You can only use [Ctrl + L] [Ctrl + C] [Ctrl + Enter] while working with lower & upper bound"
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void solve_n_degree_poly_display_help()
{
    const char *help[] = {
        "🔢 Solve nᵗʰ degree Polynomial Equation\n",
        "### Shortcut keys:",
        "Esc                    : Go to menu",
        "Ctrl + L               : See list of available funtion",
        "Ctrl + C               : See list of available constant & variable",
        "Ctrl + D               : Refresh",
        "Ctrl + Enter           : Assign value for variables",
        "\n「 ✦ NOTE ✦ 」 You can only use [Ctrl + L] [Ctrl + C] [Ctrl + Enter] while working with coefficients"
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void solve_quadratic_display_help()
{
    const char *help[] = {
        "🔢 Solve Quadratic Equation\n",
        "### Shortcut keys:",
        "Esc                    : Go to menu",
        "Ctrl + L               : See list of available funtion",
        "Ctrl + C               : See list of available constant & variable",
        "Ctrl + D               : Refresh",
        "Ctrl + S               : Start solving",
        "Ctrl + Enter           : Assign value for variables",
        "Press Shift + a, b, c  : To switch coefficients",
        "\n「 ✦ NOTE ✦ 」 You can only use [Ctrl + L] [Ctrl + C] [Ctrl + Enter] while working with coefficients"
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void solve_cubic_display_help()
{
    const char *help[] = {
        "🔢 Solve Cubic Equation\n",
        "### Shortcut keys:",
        "Esc                        : Go to menu",
        "Ctrl + L                   : See list of available funtion",
        "Ctrl + C                   : See list of available constant & variable",
        "Ctrl + D                   : Refresh",
        "Ctrl + S                   : Start solving",
        "Ctrl + Enter               : Assign value for variables",
        "Press Shift + a, b, c, d   : To switch coefficients",
        "\n「 ✦ NOTE ✦ 」 You can only use [Ctrl + L] [Ctrl + C] [Ctrl + Enter] while working with coefficients"
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void solve_quartic_display_help()
{
    const char *help[] = {
        "🔢 Solve Quartic Equation\n",
        "### Shortcut keys:",
        "Esc                          : Go to menu",
        "Ctrl + L                     : See list of available funtion",
        "Ctrl + C                     : See list of available constant & variable",
        "Ctrl + D                     : Refresh",
        "Ctrl + S                     : Start solving",
        "Ctrl + Enter                 : Assign value for variables",
        "Press Shift + a, b, c, d, e  : To switch coefficients",
        "\n「 ✦ NOTE ✦ 」 You can only use [Ctrl + L] [Ctrl + C] [Ctrl + Enter] while working with coefficients"
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void display_menu()
{
    system("cls");
    const char *mode_list[] = {
        "0/ Close window",
        "1/ Usual Calculation",
        "2/ Derivative Calculator",
        "3/ Integral Calculator (in-dev)",
        "4/ Solve Quadratic Equation (2-degree polynomial equation)",
        "5/ Solve Cubic Equation (3-degree polynomial equation)",
        "6/ Solve Quartic Equation (4-degree polynomial equation)",
        "7/ Solve nᵗʰ Degree Polynomial Equation",
        "8/ Solve any Equation",
        "9/ Solve System of Linear Equation"};
    int size = sizeof(mode_list) / sizeof(mode_list[0]);
    for (int i = 0; i < size; i++)
    {
        puts(mode_list[i]);
        delay(40);
    }
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

    unsigned short int list_size = sizeof(list_of_func) / sizeof(list_of_func[0]);

    for (unsigned short int i = 0; i < list_size; i++)
        puts(list_of_func[i]);

    puts("### NOTE: These functions are availablle int this mode");

    system("pause >nul");
}

void usualcal_display_help()
{
    const char *help[] = {
        "🔢 Usual Calculation\n",
        "### Shortcut keys:",
        "Esc       : Go to menu",
        "Ctrl + L  : See list of available function",
        "Ctrl + C  : See list of available constant",
        "Ctrl + D  : Clear screen",
        "Enter ↳   : Assign value for variables and calculate",
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy",
        "\nSameple expressions:\n",
        "integral( 5pi/3 * abs( sin( (pi/3) * t - 2pi/5 ) ) , t , 0 , sqrt.5)\n",
        "dif(e^( 1/x ) , x = sqrt.5) - ln2\n",
        "2e/5 - 3pi/7 + sinh(arctanh( pi/6 )) + ln2 ^ e\n",
        "100!\n",
        "gamma(7) - 7!\n"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
        printf("%s\n", help[i]);

    system("pause >nul");
}

void derivative_calculator_display_help()
{
    const char *help[] = {
        "🔢 Derivative Calculator\n",
        "### Shortcut keys:",
        "Esc      : Go to menu",
        "Enter    : Start differentiating (Leave the input field empty to find the next higher derivative)",
        "Ctrl + D : Refresh screen and data",
        "\n🖱️: ̗̀➛ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy",
        "\n### Sample functions:\n",
        "3x^8 - ex^pi + 2   --- Differentiate with respect to: x",
        "k^k - x^2 --- Differentiate with respect to: k",
        "pi - 3m^a - ln(a + ln2) --- Differentiate with respect to: a"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
        puts(help[i]);

    system("pause >nul");
}

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

    unsigned short int list_size = sizeof(list_of_func) / sizeof(list_of_func[0]);

    for (unsigned short int i = 0; i < list_size; i++)
        puts(list_of_func[i]);

    puts("\n### NOTE: These functions are available in this mode");

    system("pause >nul");
}

#endif