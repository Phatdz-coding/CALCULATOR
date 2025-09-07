#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdbool.h>
#include <windows.h>

// -------------------- shared variables (exp) -------------------- //
typedef struct shared_variables
{
    double num;
    char var_name;
} shared_variables;

// global set
// This pointer holds the address of the shared memory block
static shared_variables *variable_set = (void *)0;
static HANDLE handle_var_set;

// This table is used to access the variable in the set using characters input
static short int index_table[256] = {
    ['a'] = 0, ['b'] = 1, ['d'] = 2, ['f'] = 3, ['h'] = 4, ['i'] = 5, ['j'] = 6, ['k'] = 7, ['l'] = 8, ['m'] = 9, ['n'] = 10, ['o'] = 11, ['p'] = 12, ['q'] = 13, ['r'] = 14, ['s'] = 15, ['t'] = 16, ['u'] = 17, ['v'] = 18, ['w'] = 19, ['x'] = 20, ['y'] = 21, ['z'] = 22, ['A'] = 23, ['B'] = 24, ['C'] = 25, ['D'] = 26, ['E'] = 27, ['F'] = 28, ['G'] = 29, ['H'] = 30, ['I'] = 31, ['J'] = 32, ['K'] = 33, ['L'] = 34, ['M'] = 35, ['N'] = 36, ['O'] = 37, ['P'] = 38, ['Q'] = 39, ['R'] = 40, ['S'] = 41, ['T'] = 42, ['U'] = 43, ['V'] = 44, ['W'] = 45, ['X'] = 46, ['Y'] = 47, ['Z'] = 48};


// ---------------------------------------------------------------- //

// global roots
// This pointer holds the address of the shared memory block
// This pointer is used in solve_equation feature
typedef struct solution_pack
{
    unsigned short int numof_solutions;
    double *solutions_array;
    char *str_function;
    unsigned short int str_function_len;
    char var;
    double l_bound;
    double u_bound;
} solution_pack;

static solution_pack *shared_solution_pack;

static bool open_menu;

// ---------------------------------------------------------------- //

#define PROGRAM_NAME "Scientific Calculator En.exe" // This macro must have the exact name of the program
#define NUM_OF_VARIABLES 49
#define SHARED_MEM_NAME "Local\\Shared_Variables"

#define SHARED_MEM_NAME_SOLUTION_PACK "Local\\Shared_Solutions_Pack"
#define SHARED_MEM_NAME_ROOT_ARRAY "Local\\Root_Array"
#define SHARED_MEM_NAME_STR_FUNCTION "Local\\Str_Function"

#define SHARED_MEM_NAME_IC_FUNCTION "Local\\Str_Function"
#define SHARED_MEM_NAME_IC_LEN "Local\\Len"
#define SHARED_MEM_NAME_IC_VARIABLE "Local\\Variable"
#define SHARED_MEM_NAME_IC_A "Local\\a"
#define SHARED_MEM_NAME_IC_B "Local\\b"
#define SHARED_MEM_NAME_IC_METHOD "Local\\Method"
#define SHARED_MEM_NAME_IC_RESULT "Local\\Result"

#endif