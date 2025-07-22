#include <MY_LIB/inputsDisplays.h>
#include <MY_LIB/my_calculator.h>

int main()
{
    char var_name[50] = {0};
    short int index = 0;
    
    // Add lowercase letters 'a' to 'z' (excluding 'c', 'e', 'g')
    for (short int i = 'a'; i <= 'z'; i++)
    {
        if(i != 'c' && i != 'e' && i != 'g') {
            var_name[index] = i;
            index++;
        }
    }
    
    // Add uppercase letters 'A' to 'Z' (all of them, including 'C', 'E', 'G')
    for (short int i = 'A'; i <= 'Z'; i++)
    {
        var_name[index] = i;
        index++;
    }
    
    // Ensure null termination (already initialized to 0, but being explicit)
    var_name[index] = '\0';
    
    printf("%s\n", var_name);

    return 0;
}