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

void solve_system_of_nonlinear_equation_display_help();

void integral_calculator_display_help();

// ======================================================================================================= //
// ======================================================================================================= //
// ======================================================================================================= //

void solve_system_of_nonlinear_equation_display_help()
{
    const char *help[] = {
        "🔢 Solve System of Non-Linear Equations\n",
        "This feature solves a system of n non-linear equations with n variables.",
        "\n❓ How to use",
        "1. Press [F1] to start.",
        "2. Enter the number of equations (and variables), n.",
        "3. Input each function f(x₁, x₂, ..., xₙ) = 0.",
        "4. Enter the set of variables (e.g., 'xy').",
        "5. Define the lower and upper bounds for the solution search.",
        "6. The calculator will display the system and then the solutions.",
        "\n⌨  Shortcut keys",
        "Esc                    : Go to menu OR quit input section",
        "F1                     : To start input number of unknown and coefficient",
        "Ctrl + G               : Show this help panel",
        "Ctrl + D               : Refresh",
        "\nℹ️ Input-specified shortcuts",
        "While inputting functions, lower & upper bound:",
        "  Ctrl + L             : See list of available funtions",
        "  Ctrl + C             : See list of available constant & variable",
        "  Ctrl + Enter         : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Let's solve the system:\n",
        "  f₁(x,y) = x² + y² - 4 = 0",
        "  f₂(x,y) = eˣ + y - 1 = 0",
        "1. Press [F1], enter n = 2.",
        "2. Function 1: x^2 + y^2 - 4",
        "3. Function 2: e^x + y - 1",
        "4. Variables: xy",
        "5. Lower bound: -2, Upper bound: 2",
        "   ➢ Solution: x ≈ -1.81626, y ≈ 0.837367",
        "\n「 ✦ Example ✦  」",
        "Solve the system:\n",
        "  f₁(x,y,z) =  3x - cos(yz) - 0.5 = 0",
        "  f₂(x,y,z) =  x^2 - 81(y + 0.1)^2 + sin(z) + 1.06 = 0",
        "  f₃(x,y,z) =  e^(-xy) + 20z + 10pi/3 - 1 = 0",
        "1. Press [F1] enter n = 3",
        "2. Type in the functions",
        "3. Enter variables: xyz",
        "4. Lower bound = -2",
        "5. Upper bound = 2",
        "   ➢ Solutions: x = 0.5; y ≈ 0; z = -0.5235...",
        "\n✨ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

void solve_system_of_linear_equation_display_help()
{
    const char *help[] = {
        "🔢 Solve System of Linear Equations\n",
        "This feature solves a system of n linear equations with n unknowns using Cramer's rule or Gaussian elimination.",
        "\n❓ How to use",
        "1. Press [F1] to begin.",
        "2. Enter the number of unknowns (n).",
        "3. Input the coefficients for each equation (aᵢⱼ) and the constant terms (bᵢ).",
        "4. The calculator will display the system and then show the solutions.",
        "\n⌨  Shortcut keys",
        "Esc                    : Go to menu OR quit input section",
        "F1                     : To start input number of unknown and coefficient",
        "Ctrl + G               : Show this help panel",
        "Ctrl + D               : Refresh",
        "\nℹ️ Input-specified shortcuts",
        "While inputting coefficients:",
        "  Ctrl + L             : See list of available funtions",
        "  Ctrl + C             : See list of available constant & variable",
        "  Ctrl + Enter         : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Solve the system:",
        "  2x₁ + 3x₂ = 8",
        "  x₁ - x₂ = -1",
        "1. Press [F1], enter n = 2.",
        "2. a₁₁=2, a₁₂=3, b₁=8",
        "3. a₂₁=1, a₂₂=-1, b₂=-1",
        "   Solution: x₁ = 1, x₂ = 2",
        "\n✨ Tip",
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
        "🔢 Solve Any Equation (one single unknown)\n",
        "This feature helps you find the root of an equation f(x) = 0 within a specified range.",
        "\n❓ How to use",
        "1. Press [F1] to input your function (e.g., 'x^2 - 2').",
        "2. Press [F2] to specify the variable to solve for (e.g., 'x').",
        "3. Press [F3] to set the lower bound of the search range.",
        "4. Press [F4] to set the upper bound of the search range.",
        "5. Press [F5] to start the calculation and find the solution.",
        "\n⌨  Shortcut keys",
        "Esc                    : Go back to the main menu.",
        "F1                     : Input the function f(x).",
        "F2                     : Define the variable to solve for.",
        "F3                     : Set the lower bound for the solution search.",
        "F4                     : Set the upper bound for the solution search.",
        "F5                     : Start solving the equation.",
        "Ctrl + G               : Show this help panel.",
        "Ctrl + D               : Refresh the screen and clear all inputs.",
        "\nℹ️ Input-specified shortcuts",
        "While inputting the function, lower bound, or upper bound:",
        "  Ctrl + L             : See a list of available functions.",
        "  Ctrl + C             : See a list of available constants and variables.",
        "  Ctrl + Enter         : Assign a value to a variable.",
        "\n「 ✦ Example ✦  」",
        "Let's solve the equation: x³ - x - 2 = 0",
        "1. Press [F1] and type: x^3 - x - 2",
        "2. Press [F2] and type: x",
        "3. Press [F3] and type: 1",
        "4. Press [F4] and type: 2",
        "5. Press [F5] to solve. The calculator will find a root between 1 and 2.",
        "   The approximate solution is x ≈ 1.521.",
        "\n✨ Tip",
        "Highlight text and right-click to copy.",
        "Right-click in the input area to paste."};

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
        "🔢 Solve nᵗʰ degree Polynomial Equation (n ≥ 5)\n",
        "Finds the roots of a polynomial equation of degree 5 or higher.",
        "\n❓ How to use",
        "1. Enter the degree of the polynomial (n).",
        "2. Input the coefficients for each term, from a₀ to aₙ.",
        "3. The calculator will display the equation and its roots.",
        "\n⌨  Shortcut keys",
        "Esc                    : Go to menu",
        "F1                     : To start input",
        "Ctrl + G               : Show this help panel",
        "Ctrl + D               : Refresh",
        "\nℹ️ Input-specified shortcuts",
        "While inputting coefficients:",
        "  Ctrl + L             : See list of available funtions",
        "  Ctrl + C             : See list of available constant & variable",
        "  Ctrl + Enter         : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Solve the equation: x⁵ - 15x⁴ + 85x³ - 225x² + 274x - 120 = 0",
        "1. Press F1 to start input",
        "2. Enter degree: 5",
        "3. a₀=1, a₁=-15, a₂=85, a₃=-225, a₄=274, a₅=-120",
        "   The roots are: 1, 2, 3, 4, 5",
        "\n✨ Tip",
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
        "🔢 Solve Quadratic Equation (ax² + bx + c = 0)\n",
        "This feature finds the roots of a quadratic equation.",
        "\n❓ How to use",
        "1. Use [Shift + a], [Shift + b], [Shift + c] to select a coefficient.",
        "2. Input the value for the selected coefficient.",
        "3. Repeat for all three coefficients (a, b, c).",
        "4. Press [F5] to solve the equation.",
        "\n⌨  Shortcut keys",
        "Esc                    : Go to menu",
        "F5                     : Start solving",
        "Ctrl + G               : Show this help panel",
        "Ctrl + D               : Refresh",
        "Shift + a/b/c          : Switch to input coefficient a, b, or c.",
        "\nℹ️ Input-specified shortcuts",
        "While inputting coefficients:",
        "  Ctrl + L             : See list of available funtions",
        "  Ctrl + C             : See list of available constant & variable",
        "  Ctrl + Enter         : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Solve: x² - 3x + 2 = 0",
        "1. Press [Shift + a], enter 1.",
        "2. Press [Shift + b], enter -3.",
        "3. Press [Shift + c], enter 2.",
        "4. Press [F5].",
        "   The roots are x₁ = 1, x₂ = 2.",
        "\n✨ Tip",
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
        "🔢 Solve Cubic Equation (ax³ + bx² + cx + d = 0)\n",
        "This feature finds the roots of a cubic equation.",
        "\n❓ How to use",
        "1. Use [Shift + a/b/c/d] to select a coefficient.",
        "2. Input the value for the selected coefficient.",
        "3. Repeat for all four coefficients (a, b, c, d).",
        "4. Press [F5] to solve the equation.",
        "\n⌨  Shortcut keys",
        "Esc                        : Go to menu",
        "F5                         : Start solving",
        "Ctrl + G                   : Show this help panel",
        "Ctrl + D                   : Refresh",
        "Shift + a/b/c/d            : Switch to input a coefficient.",
        "\nℹ️ Input-specified shortcuts",
        "While inputting coefficients:",
        "  Ctrl + L                 : See list of available funtions",
        "  Ctrl + C                 : See list of available constant & variable",
        "  Ctrl + Enter             : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Solve: x³ - 6x² + 11x - 6 = 0",
        "1. Set a=1, b=-6, c=11, d=-6 using the Shift keys.",
        "2. Press [F5].",
        "   The roots are x₁ = 1, x₂ = 2, x₃ = 3.",
        "\n✨ Tip",
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
        "🔢 Solve Quartic Equation (ax⁴ + bx³ + cx² + dx + e = 0)\n",
        "This feature finds the roots of a quartic equation.",
        "\n❓ How to use",
        "1. Use [Shift + a/b/c/d/e] to select a coefficient.",
        "2. Input the value for the selected coefficient.",
        "3. Repeat for all five coefficients (a, b, c, d, e).",
        "4. Press [F5] to solve the equation.",
        "\n⌨  Shortcut keys",
        "Esc                          : Go to menu",
        "F5                           : Start solving",
        "Ctrl + G                     : Show this help panel",
        "Ctrl + D                     : Refresh",
        "Shift + a/b/c/d/e            : Switch to input a coefficient.",
        "\nℹ️ Input-specified shortcuts",
        "While inputting coefficients:",
        "  Ctrl + L                   : See list of available funtions",
        "  Ctrl + C                   : See list of available constant & variable",
        "  Ctrl + Enter               : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Solve: x⁴ - 10x³ + 35x² - 50x + 24 = 0",
        "1. Set a=1, b=-10, c=35, d=-50, e=24 using the Shift keys.",
        "2. Press [F5].",
        "   The roots are 1, 2, 3, 4.",
        "\n✨ Tip",
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
    hide_cursor();
    system("cls");
    const char *mode_list[] = {
        "0/ Close window",
        "1/ Usual Calculation",
        "2/ Derivative Calculator",
        "3/ Integral Calculator",
        "4/ Solve Quadratic Equation (2-degree polynomial equation)",
        "5/ Solve Cubic Equation (3-degree polynomial equation)",
        "6/ Solve Quartic Equation (4-degree polynomial equation)",
        "7/ Solve nᵗʰ Degree Polynomial Equation",
        "8/ Solve any Equation",
        "9/ Solve System of Linear Equations",
        "10/ Solve System of Non-linear Equations"};
    int size = sizeof(mode_list) / sizeof(mode_list[0]);
    for (int i = 0; i < size; i++)
    {
        puts(mode_list[i]);
        delay(40);
    }
    show_cursor();
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
        "1/ Differentiation: dif( function , variable = expression )\n",
        "\tThis function find the derivative of a function at a certain point. Examples:\n",
        "\t\tdif( 3x^3 - 2x^2 + 6.6x , x = 3.2 )  --- Result: 85.96\n",
        "\t\tdif( e^( -1 / k ) , k = pi - e)  --- Result: 0.5256...\n",
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
        "A flexible calculator for evaluating mathematical expressions.",
        "\n❓ How to use",
        "1. Type your mathematical expression directly.",
        "2. The result is displayed automatically.",
        "3. To assign a variable, type the variable (e.g., 'a') and press [Enter].",
        "\n⌨  Shortcut keys",
        "Esc       : Go to menu",
        "Ctrl + L  : See list of available functions",
        "Ctrl + C  : See list of available constants and user-defined variables",
        "Ctrl + D  : Clear the current input and screen",
        "Enter     : An integrated panel will pop up to assign variables (e.g., 'x=3+2') and compute",
        "\n✨ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy",
        "\n### Sample expressions:",
        "integral(5*pi/3 * abs(sin((pi/3)*t - 2*pi/5)), t, 0, sqrt(0.5))",
        "dif(e^(1/x), x=sqrt(0.5)) - ln(2)",
        "2*e/5 - 3*pi/7 + sinh(arctanh(pi/6)) + ln(2)^e",
        "100!",
        "gamma(7) - 6!"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
        printf("%s\n", help[i]);

    system("pause >nul");
}

void derivative_calculator_display_help()
{
    const char *help[] = {
        "🔢 Derivative Calculator\n",
        "Calculates the symbolic derivative of a function.",
        "\n❓ How to use",
        "1. Input the function you want to differentiate.",
        "2. Press [Enter].",
        "3. Enter the variable with respect to which you want to differentiate.",
        "4. The derivative will be displayed.",
        "5. To find a higher-order derivative, leave the function input empty and press [Enter].",
        "\n⌨  Shortcut keys",
        "Esc      : Go to menu",
        "Enter    : Confirm input / Differentiate",
        "Ctrl + D : Refresh screen and clear all data",
        "Ctrl + G : Show this help panel",
        "\n✨ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy",
        "\n「 ✦ Example ✦  」",
        "Find the second derivative of 3k^4 - cos(k)",
        "1. Function: 3k^4 - cos(k)",
        "2. Press [Enter].",
        "3. Differentiate with respect to: k",
        "   Result (1st derivative): 12k^3 + sin(k)",
        "4. Leave function input empty and press [Enter].",
        "5. Differentiate with respect to: k",
        "   Result (2nd derivative): 36k^2 + cos(k)"};

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

void integral_calculator_display_help()
{
    const char *help[] = {
        "🔢 Numerical Integration Calculator\n",
        "This feature calculates the definite integral of a function over a specified interval.",
        "\n❓ How to use",
        "1. Press [F1] to input your function f(x).",
        "2. Press [F2] to specify the variable of integration (default: x).",
        "3. Press [F3] to set the lower bound (a) of the integration interval.",
        "4. Press [F4] to set the upper bound (b) of the integration interval.",
        "5. Press [F5] to calculate the integral ∫ₐᵇ f(x) dx.",
        "\n⌨  Shortcut keys",
        "Esc                    : Go to menu",
        "F1                     : Input the function f(x)",
        "F2                     : Define the variable of integration",
        "F3                     : Set the lower bound (a)",
        "F4                     : Set the upper bound (b)",
        "F5                     : Calculate the integral",
        "Ctrl + G               : Show this help panel",
        "Ctrl + D               : Refresh screen and clear all inputs",
        "\n🔧 Integration Methods",
        "• Default - Let the calculator decide  [Shift + 0]\n",
        "• Gaussian Quadrature with 700 nodes   [Shift + 1]",
        " - Performance: Extremely fast",
        " - Accuracy: High",
        " - Best for general use, polynomial function, large interval, below strong oscillatory function",
        " - Examples: sin(100x) on [0, 10] ; x^10 - 3x^5 + pix^7 on [-1, 1] . . .\n",
        "• Double Tanh-Sinh Quadrature          [Shift + 2]",
        " - Performance: Moderate",
        " - Accuracy: High",
        " - Design specificly for improper integral, intervals that have singularities at endpoints, semifinite and infinite intervals",
        " - Examples: e^(-x^2) on [0, +∞] ; 4/(16 + x^2) on [-∞, +∞] ; cos(x) / (5cbrt(x)) on [0, 1] . . .\n",
        "• Adaptive Quadrature                  [Shift + 3]",
        " - Perfomance: Slow or extremely slow in bad case",
        " - Accuracy: Extreme",
        " - Good for general use, but design specificly for trigonometric function, large interval, strong oscillatory function",
        " - Examples: cos(1000x) on [0, 10] ; pi * sin(pix - pi/3) on [0, 5] . . .\n",
        "• Simpson's Rule with 1.000.000 sub-intervals   [Shift + 4]",
        " - Performance: Slow",
        " - Accuracy Moderate (due to machine precision limit, not suitable for casual function) and extremely precesion with some functions below",
        " - Design specificly for extreme oscillatory function",
        " - Examples: sin(10000x) on [0, 10] ; cos(20000x) on [0, 10]",
        "\nℹ️ Input-specified shortcuts",
        "While inputting function, bounds:",
        "  Ctrl + L             : See list of available functions",
        "  Ctrl + C             : See list of available constants & variables",
        "  Ctrl + Enter         : Assign value for variables",
        "\n「 ✦ Example ✦  」",
        "Calculate ∫₀¹ x² dx",
        "1. Press [F1] and type: x^2",
        "2. Press [F2] and type: x (or leave default)",
        "3. Press [F3] and type: 0",
        "4. Press [F4] and type: 1",
        "5. Press [F5] to calculate",
        "   Result: ∫₀¹ x² dx = 0.3333...",
        "\n「 ✦ Another Example ✦  」",
        "Calculate ∫₀^π sin(t) dt",
        "1. Function: sin(t)",
        "2. Variable: t",
        "3. Lower bound: 0",
        "4. Upper bound: pi",
        "5. Press [F5]",
        "   Result: ∫₀^π sin(t) dt = 2",
        "\n✨ Tip",
        "Highlight the text and then right-click to copy",
        "Right-click to paste the copy"};

    unsigned short int help_size = sizeof(help) / sizeof(help[0]);

    for (unsigned short int i = 0; i < help_size; i++)
    {
        puts(help[i]);
    }

    system("pause >nul");
}

#endif