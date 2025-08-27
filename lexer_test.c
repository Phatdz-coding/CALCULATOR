#include <MY_LIB/lexer_and_format.h>
#include <MY_LIB/my_calculator.h>

int main()
{
    turn_on_advanced_character_mode();
    char string[] = "Ꮤ";

    for (unsigned short int i = 0; i < strlen(string); i++)
    {
        printf("input_code == %d ||\n",(unsigned char) string[i]);
    }
    
    

    return 0;
}