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
#define SFUNCTION_SIN 's'
#define SFUNCTION_SINH 'n'
#define SFUNCTION_ARCSIN 'Q'
#define SFUNCTION_ARCSINH 'N'
#define SFUNCTION_COS '<'
#define SFUNCTION_COSH 'm'
#define SFUNCTION_ARCCOS 'W'
#define SFUNCTION_ARCCOSH 'M'
#define SFUNCTION_TAN 't'
#define SFUNCTION_TANH 'p'
#define SFUNCTION_ARCTAN 'U'
#define SFUNCTION_ARCTANH 'P'
#define SFUNCTION_COT 'T'
#define SFUNCTION_COTH 'j'
#define SFUNCTION_ARCCOT 'O'
#define SFUNCTION_ARCCOTH 'J'
#define SFUNCTION_SEC 'S'
#define SFUNCTION_SECH 'g'
#define SFUNCTION_ARCSEC 'a'
#define SFUNCTION_ARCSECH 'A'
#define SFUNCTION_CSC '>'
#define SFUNCTION_CSCH 'v'
#define SFUNCTION_ARCCSC 'b'
#define SFUNCTION_ARCCSCH 'B'
#define SFUNCTION_SQRT 'r'
#define SFUNCTION_CBRT 'R'
#define SFUNCTION_ABS 'V'
#define SFUNCTION_LN 'L'
#define SFUNCTION_LG 'l'
#define SFUNCTION_GAMMA 'G'
#define SFUNCTION_CEIL 'C'
#define SFUNCTION_FLOOR 'F'
#define SFUNCTION_LAMBERTW 'w'
// --- many-parameters functions --- //
#define SFUNCTION_DIF 'd' // derivative
#define SFUNCTION_INTEGRAL 'I'
#define SFUNCTION_SIGMA_SUM 'k'
#define SFUNCTION_PRODUCT_OF_SEQUENCE 'K'
#define SFUNCTION_PERMUTATIONS 'z' // probalbilstic
#define SFUNCTION_COMBINATIONS 'Z' // probalbilstic
#define SFUNCTION_GCD 'y'          // Greatest Common Divisor
#define SFUNCTION_LCM 'Y'          // Least Common Multiplier
#define SFUNCTION_LOG 'x'          // Logarithm

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
} POSTFIX;

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
} INFIX;

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