#ifndef TYPE_N_SPECIFIER
#define TYPE_N_SPECIFIER

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //
//                                                 MACROES
// ──────────────────────────────────────────────────────────────────────────────────────────────────────────── //

#define PI 3.14159265358979323846
#define EULER_NUMBER 2.718281828459045
#define SQRT_2 1.41421356237309504880
#define SQRT_2_2 0.707106781186547524
#define SQRT_3 1.73205080756887729353
#define LN_2 0.69314718055994530942
#define _G_ 9.80665
#define _C_ 299792458
#define _MAX_INT_VALUE_ 2147483647
// Function specifiers
// --- 1-parameter function --- //
#define SPECIFIER_OF_SIN 's'
#define SPECIFIER_OF_SINH 'n'
#define SPECIFIER_OF_ARCSIN 'Q'
#define SPECIFIER_OF_ARCSINH 'N'
#define SPECIFIER_OF_COS '<'
#define SPECIFIER_OF_COSH 'm'
#define SPECIFIER_OF_ARCCOS 'W'
#define SPECIFIER_OF_ARCCOSH 'M'
#define SPECIFIER_OF_TAN 't'
#define SPECIFIER_OF_TANH 'p'
#define SPECIFIER_OF_ARCTAN 'U'
#define SPECIFIER_OF_ARCTANH 'P'
#define SPECIFIER_OF_COT 'T'
#define SPECIFIER_OF_COTH 'j'
#define SPECIFIER_OF_ARCCOT 'O'
#define SPECIFIER_OF_ARCCOTH 'J'
#define SPECIFIER_OF_SEC 'S'
#define SPECIFIER_OF_SECH 'g'
#define SPECIFIER_OF_ARCSEC 'a'
#define SPECIFIER_OF_ARCSECH 'A'
#define SPECIFIER_OF_CSC '>'
#define SPECIFIER_OF_CSCH 'v'
#define SPECIFIER_OF_ARCCSC 'b'
#define SPECIFIER_OF_ARCCSCH 'B'
#define SPECIFIER_OF_SQRT 'r'
#define SPECIFIER_OF_CBRT 'R'
#define SPECIFIER_OF_ABS 'V'
#define SPECIFIER_OF_LN 'L'
#define SPECIFIER_OF_LG 'l'
#define SPECIFIER_OF_GAMMA 'G'
#define SPECIFIER_OF_CEIL 'C'
#define SPECIFIER_OF_FLOOR 'F'
#define SPECIFIER_OF_LAMBERTW 'w'
// --- many-parameters functions --- //
#define SPECIFIER_OF_DIF 'd' // derivative
#define SPECIFIER_OF_INTEGRAL 'I'
#define SPECIFIER_OF_SIGMA_SUM 'k'
#define SPECIFIER_OF_PRODUCT_OF_SEQUENCE 'K'
#define SPECIFIER_OF_PERMUTATIONS 'z' // probalbilstic
#define SPECIFIER_OF_COMBINATIONS 'Z' // probalbilstic
#define SPECIFIER_OF_GCD 'y'          // Greatest Common Divisor
#define SPECIFIER_OF_LCM 'Y'          // Least Common Multiplier
#define SPECIFIER_OF_LOG 'x'          // Logarithm

typedef struct
{
    double num;
    char operator;
} _postfix_;

typedef struct P_tokens_data
{
    double num;
    char operator;
    char variable;
} _TOKENS_DATA_;

typedef struct P_tokens_array
{
    _TOKENS_DATA_ *tokens;
    int size;
} _POSTFIX__;

typedef struct tokens_data
{
    double num;
    char operator;
    char variable;
} _infix_;

typedef struct tokens_array
{
    int size;
    _infix_ *tokens;
} __INFIX__;

/*
Γ∛√Ꮤ∫∑Π∞π

UTF-8 hex-byte:

. Γ - 0xCE 0x93
• ∛ - 0xE2 0x88 0x9B
• √ - 0xE2 0x88 0x9A
• Ꮤ - 0xE1 0x8E 0xB4
• ∫ - 0xE2 0x88 0xAB
• ∑ - 0xE2 0x88 0x91
• Π - 0xCE 0xA0
• ∞ - 0xE2 0x88 0x9E
• π - 0xCF 0x80

*/

#endif