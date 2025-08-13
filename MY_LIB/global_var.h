#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <stdbool.h>

// -------------------- shared variables (exp) -------------------- //
typedef struct shared_variables
{
    double num;
    char var_name;
} shared_variables;

// global set
// This pointer holds the address of the shared memory block
static shared_variables *variable_set;

// global roots
// This pointer holds the address of the shared memory block
// This pointer is used in solve_equation feature
typedef struct solution_pack
{
    unsigned short int numof_solutions;
    double * solutions_array;
    char * str_function;
    unsigned short int str_function_len;
    char var;
    double l_bound;
    double u_bound;
} solution_pack;

solution_pack * shared_solution_pack;


static bool open_menu;

// ---------------------------------------------------------- //

#define PROGRAM_NAME "sci_cal.exe" // This macro must have the exact name of the program
#define NUM_OF_VARIABLES 49
#define SHARED_MEM_NAME "Local\\Shared_Variables"
#define SHARED_MEM_NAME_SOLUTION_PACK "Local\\Shared_Solutions_Pack"
#define SHARED_MEM_NAME_ROOT_ARRAY "Local\\Root_Array"
#define SHARED_MEM_NAME_STR_FUNCTION "Local\\Str_Function"

#endif