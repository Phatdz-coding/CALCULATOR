#ifndef INPUT_DISPLAY_H
#define INPUT_DISPLAY_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <math.h>
#include <MY_LIB/lexer_and_format.h>

#define MAX_STRING_INPUT_SIZE 2048

// ============================================================================ //
// ==========================FUNCTION PROTOTYPES=============================== //
// ============================================================================ //

typedef struct
{
    int Len;
    char *Content;
} string_;

void debuger(const char *message);
void move_cursor(int x, int y);
void get_cursor_position(int *x, int *y);
void turn_on_advanced_character_mode();
void delay(int mili_sec);
void display_each_char(const char *text, int milisec_Delay);
void print_each_word(int milisec_Delay, const char *format, ...);
void print_each_char(int milisec_Delay, char *format, ...);
void input_with_message(char *message, const char *format, ...);
char *input_String(const char *message);
void display_2D_array(char **frame, int row, int col);
void display_2D_array_backward(char **frame, int row, int col);
int compare_strings_by_first_second_letter(const void *a, const void *b);
void sort_string_array_by_first_second_letter(char **arr, int size);
void getWinSize(int *, int *);
char *create_new_buffer_with_sizeof(const int);
void re_size_buffer(char **buffer, const int new_size);
char *copy_from_string(char **string);
void clear_line_(const int line_number);
void clear_line_in_range(const short int lower_bound, const short int upper_bound);
double input_double();
int input_int();
long long int input_longlongint();
void setWindowSize(SHORT width, SHORT height);
void display_number(const double number);
void display_number_with_max_3_dec_places(const double number);
bool is_integer___(double x);
void print_sub_script_number(const int number);
void print_super_script_number(const int number);
void free_buffer(char **buffer);
void display_infix_exp(const __INFIX__ expression);
void display_postfix_exp(_POSTFIX__ P_exp);

// ============================================================================ //
// ==========================FUNCTION DEFINITIONS============================== //
// ============================================================================ //

void display_postfix_exp(_POSTFIX__ P_exp)
{
    if (P_exp.size < 1 || P_exp.tokens == NULL)
        return;

    double num_;
    char var_, op_;

    for (short int i = 0; i < P_exp.size; i++)
    {
        num_ = P_exp.tokens[i].num;
        var_ = P_exp.tokens[i].variable;
        op_ = P_exp.tokens[i].operator;

        if (!isnan(num_))
            printf("Num: %.17lf\n", num_);
        else if (var_ != '\0')
            printf("Var: %c\n", var_);
        else
            printf("Op: %c\n", op_);
    }
}

void display_infix_exp(const __INFIX__ expression)
{
    if (expression.tokens == NULL)
        return;
    for (int i = 0; i < expression.size; i++)
    {
        if (expression.tokens[i].variable != '\0')
            printf("Var: %c\n", expression.tokens[i].variable);
        if (expression.tokens[i].operator!= '\0')
            printf("Op: %c\n", expression.tokens[i].operator);
        if (!isnan(expression.tokens[i].num))
            printf("Num: %.17lf\n", expression.tokens[i].num);
    }
}

void free_buffer(char **buffer)
{
    if (*buffer != NULL)
    {
        free(*buffer);
        *buffer = NULL;
    }
}

bool is_integer___(double x)
{
    // NaN and infinity are not integers
    if (!isfinite(x))
        return false;
    return floor(x) == x;
}

void clear_line_in_range(const short int lower_bound, const short int upper_bound)
{
    if (lower_bound >= upper_bound)
    {
        if (lower_bound == upper_bound)
            clear_line_(lower_bound);
        return;
    }

    int win_width;
    getWinSize(&win_width, NULL);

    char blanks[win_width];
    blanks[win_width] = '\0';
    memset(blanks, ' ', sizeof(blanks));
    move_cursor(lower_bound, 0);
    for (short int i = 0; i < upper_bound - lower_bound + 1; i++)
        puts(blanks);
    move_cursor(lower_bound, 0);
}

// Set terminal size
void setWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get current screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        fprintf(stderr, "Failed to get console buffer info. Error: %lu\n", GetLastError());
        return;
    }

    // The buffer size must be at least as large as the window size
    COORD newSize = csbi.dwSize;
    if (newSize.X < width)
        newSize.X = width;
    if (newSize.Y < height)
        newSize.Y = height;

    if (!SetConsoleScreenBufferSize(hStdout, newSize))
    {
        fprintf(stderr, "Failed to set console screen buffer size. Error: %lu\n", GetLastError());
        return;
    }

    // Now set the window size
    SMALL_RECT windowSize;
    windowSize.Top = 0;
    windowSize.Left = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    if (!SetConsoleWindowInfo(hStdout, TRUE, &windowSize))
    {
        fprintf(stderr, "Failed to set console window size. Error: %lu\n", GetLastError());
        return;
    }
}

// // Get long long integer from keyboard --- auto-blocking characters
long long int input_longlongint()
{
    COORD cursor_pos;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    unsigned int win_width;
    getWinSize(&win_width, NULL);
    cursor_pos.X = csbi.dwCursorPosition.X;
    cursor_pos.Y = csbi.dwCursorPosition.Y;
    char string[51] = {0};
    int input_code;
    int string_index = 0;

    while (1)
    {
        input_code = _getch();

        if (((input_code >= '0' && input_code <= '9') || (input_code == '-' && string[0] == 0)) && string_index <= 50)
        {
            string[string_index++] = input_code;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            putchar(input_code);
        }

        else if (input_code == 8 && string_index > 0)
        {
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            string[--string_index] = '\0';
            if (csbi.dwCursorPosition.X != 0)
                cursor_pos.X = csbi.dwCursorPosition.X - 1;
            cursor_pos.Y = csbi.dwCursorPosition.Y;
            if (csbi.dwCursorPosition.X != 0)
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
                putchar(' ');
            }

            else if (cursor_pos.Y != 0 && csbi.dwCursorPosition.X == 0)
            {
                --(cursor_pos.Y);
                cursor_pos.X = win_width - 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
                putchar(' ');
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
            }
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        }

        else if (input_code == 13)
        {
            putchar('\n');
            return atoll(string);
        }
    }
}

// Get int number from keyboard --- auto-blocking characters
int input_int()
{
    COORD cursor_pos;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    unsigned int win_width;
    getWinSize(&win_width, NULL);
    cursor_pos.X = csbi.dwCursorPosition.X;
    cursor_pos.Y = csbi.dwCursorPosition.Y;
    char string[12] = {0};
    int input_code;
    int string_index = 0;

    while (1)
    {
        input_code = _getch();

        if (((input_code >= '0' && input_code <= '9') || (input_code == '-' && string[0] == 0)) && string_index <= 11)
        {
            string[string_index++] = input_code;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            putchar(input_code);
        }

        else if (input_code == 8 && string_index > 0)
        {
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            string[--string_index] = '\0';
            if (csbi.dwCursorPosition.X != 0)
                cursor_pos.X = csbi.dwCursorPosition.X - 1;
            cursor_pos.Y = csbi.dwCursorPosition.Y;
            if (csbi.dwCursorPosition.X != 0)
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
                putchar(' ');
            }

            else if (cursor_pos.Y != 0 && csbi.dwCursorPosition.X == 0)
            {
                --(cursor_pos.Y);
                cursor_pos.X = win_width - 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
                putchar(' ');
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
            }
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        }

        else if (input_code == 13)
        {
            putchar('\n');
            return atoi(string);
        }
    }
}

// Get double number from keyboard --- auto-blocking characters
double input_double()
{
    COORD cursor_pos;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    unsigned int win_width;
    getWinSize(&win_width, NULL);
    cursor_pos.X = csbi.dwCursorPosition.X;
    cursor_pos.Y = csbi.dwCursorPosition.Y;
    char string[31] = {0};
    int input_code;
    int string_index = 0;
    bool dot = false;

    while (1)
    {
        input_code = _getch();

        if (input_code == '.' && dot)
            continue;

        if (((input_code >= '0' && input_code <= '9') || input_code == '.' || (input_code == '-' && string[0] == 0)) && string_index <= 30)
        {
            if (input_code == '.')
                dot = true;
            string[string_index++] = input_code;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            putchar(input_code);
        }

        else if (input_code == 8 && string_index > 0)
        {
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
            if (string[string_index - 1] == '.')
                dot = false;
            string[--string_index] = '\0';
            if (csbi.dwCursorPosition.X != 0)
                cursor_pos.X = csbi.dwCursorPosition.X - 1;
            cursor_pos.Y = csbi.dwCursorPosition.Y;
            if (csbi.dwCursorPosition.X != 0)
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
                putchar(' ');
            }

            else if (cursor_pos.Y != 0 && csbi.dwCursorPosition.X == 0)
            {
                --(cursor_pos.Y);
                cursor_pos.X = win_width - 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
                putchar(' ');
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
            }
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        }

        else if (input_code == 13)
        {
            putchar('\n');
            return atof(string);
        }
    }
}

void clear_line_(const int line_number)
{
    int win_width;
    getWinSize(&win_width, NULL);

    char blanks[win_width];
    blanks[win_width] = '\0';
    memset(blanks, ' ', sizeof(blanks));
    move_cursor(line_number, 0);
    printf("%s", blanks);
    move_cursor(line_number, 0);
}

char *copy_from_string(char **string)
{
    char *copyof_string = (char *)malloc((strlen(*string) + 1) * sizeof(char));
    if (copyof_string == NULL)
    {
        perror("Failed to create copyof_string");
        return NULL;
    }
    strcpy(copyof_string, *string);
    return copyof_string;
}

void re_size_buffer(char **buffer, const int new_size)
{
    if (new_size <= 0 || new_size > 10000)
    {
        fprintf(stderr, "New_size is invalid");
        if ((*buffer) != NULL)
            free((*buffer));
        return;
    }
    (*buffer) = (char *)realloc(*buffer, (new_size + 1) * sizeof(char));
    if ((*buffer) == NULL)
    {
        perror("Unable to re-allocate buffer");
        if ((*buffer) != NULL)
            free((*buffer));
        return;
    }
    (*buffer)[new_size] = '\0';
}

/*
This function allocates a new character buffer of a specified size,
ensuring the size is within a valid range,
and returns a pointer to the buffer with a null terminator at the end.
*/
char *create_new_buffer_with_sizeof(const int buffer_size)
{
    if (buffer_size <= 0 || buffer_size > 10000)
    {
        fprintf(stderr, "Invalid buffer size: %d\n", buffer_size);
        return NULL;
    }
    char *buffer = (char *)calloc(buffer_size + 1, sizeof(char));
    if (buffer == NULL)
    {
        perror("Error creating new buffer");
        return NULL;
    }
    return buffer;
}

void getWinSize(int *width, int *height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hStdout, &csbi))
    {
        if (width != NULL)
            *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        if (height != NULL)
            *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    else
    {
        // Fallback to default values if unable to get size
        if (width != NULL)
            *width = 80;
        if (height != NULL)
            *height = 25;
    }
}

/**
 * Comparison function for qsort to sort strings by first and second letter.
 */
int compare_strings_by_first_second_letter(const void *a, const void *b)
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    // Compare first character
    if (str1[0] != str2[0])
        return (unsigned char)str1[0] - (unsigned char)str2[0];

    // If first character is the same, compare second character
    return (unsigned char)str1[1] - (unsigned char)str2[1];
}

/**
 * Sorts an array of strings by their first and second letter in increasing order.
 * @param arr Pointer to the array of strings (char*).
 * @param size Number of strings in the array.
 */
void sort_string_array_by_first_second_letter(char **arr, int size)
{
    qsort(arr, size, sizeof(char *), compare_strings_by_first_second_letter);
}

void debuger(const char *message)
{
    printf("%s\n", message);
}

// move cursor to a certain poosition on the console screen
void move_cursor(int row, int column)
{
    COORD coord;
    coord.X = column;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// get the current x & y position of the cursor
void get_cursor_position(int *x, int *y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    if (x != NULL)
        (*x) = (int)csbi.dwCursorPosition.X;
    if (y != NULL)
        (*y) = (int)csbi.dwCursorPosition.Y;
}

// switch the terminal to be able to display vn characters
void turn_on_advanced_character_mode()
{
    system("chcp 65001 >nul");
}

// Create a delay between each action
void delay(int mili_sec)
{
    struct timespec ts;
    ts.tv_sec = mili_sec / 1000;
    ts.tv_nsec = (mili_sec % 1000) * 1000000;

    nanosleep(&ts, NULL);
}

/*
Print out the message slowly
#Note: No formats or arguments supported
*/
void display_each_char(const char *text, int milisec_Delay)
{
    if (text == NULL)
        return;
    for (int i = 0; text[i] != '\0'; i++)
    {
        putchar(text[i]);
        delay(milisec_Delay);
    }
}

// Print out each word of the text with formats & arguments supported
void print_each_word(int milisec_Delay, const char *format, ...)
{
    int string_length = strlen(format) + 100;
    char content[string_length];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(content, sizeof(content), format, arguments);
    va_end(arguments);

    int content_len = strlen(content);
    char word[21];
    memset(word, '\0', sizeof(word));
    int k = 0;
    for (int i = 0; i <= content_len; i++)
    {
        if (content[i] != ' ' && content[i] != '\0' && content[i] != '\n' && content[i] != '\t' && content[i] != '\r')
        {
            word[k++] = content[i];
        }
        else
        {
            printf("%s%c", word, content[i]);
            memset(word, '\0', sizeof(word));
            k = 0;
            delay(milisec_Delay);
        }
    }
}

// Print out each character of the text with formats & arguments supported
void print_each_char(int milisec_Delay, char *format, ...)
{
    int string_length = strlen(format) + 100;
    char content[string_length];
    va_list arguments;
    va_start(arguments, format);
    vsnprintf(content, sizeof(content), format, arguments);
    va_end(arguments);
    display_each_char(content, milisec_Delay);
}

// get int, float, double, char with message
void input_with_message(char *message, const char *format, ...)
{
    display_each_char(message, 10);
    va_list addresss;
    va_start(addresss, format);
    vscanf(format, addresss);
    va_end(addresss);
    getchar();
}

/*
get a string without newline \n character
message included
#NOTE max input length = 1000 (characters)
*/
char *input_String(const char *message)
{
    display_each_char(message, 10);

    char *storage = (char *)malloc(1001 * sizeof(char));

    fgets(storage, 1001, stdin);
    const int last_char = strcspn(storage, "\n");
    storage[last_char] = '\0'; // terminate newline \n character

    // re-allocate memory for storage
    storage = (char *)realloc(storage, (last_char + 1) * sizeof(char));

    return storage;
}

void display_2D_array(char **frame, int row, int col)
{
    system("cls");
    // print out the frame
    for (int i = 0; i < row; i++)
        fwrite(frame[i], sizeof(char), col, stdout);
}

void display_2D_array_backward(char **frame, int row, int col)
{
    system("cls");
    // print out the frame
    for (int i = row - 1; i >= 0; i++)
        fwrite(frame[i], sizeof(char), col, stdout);
}

void display_number(const double number)
{
    if (isfinite(number))
    {
        printf("%.15g", number);
    }
    else if (isinf(number) && number < 0.0)
        printf("-∞");
    else if (isinf(number) && number > 0.0)
        printf("+∞");
    else
        printf("⚠  Syntax Error ⚠");
}

void display_number_with_max_3_dec_places(const double number)
{
    if (isfinite(number))
    {
        if (is_integer___(number))
            printf("%.0lf", number);

        else if (is_integer___(10.0 * number))
            printf("%.1lf", number);

        else if (is_integer___(100.0 * number))
            printf("%.2lf", number);
        else
            printf("%.3lf", number);
    }
    else if (isinf(number) && number < 0.0)
        printf("-∞");
    else if (isinf(number) && number > 0.0)
        printf("+∞");
    else
        printf("⚠  Syntax Error ⚠");
}

void print_sub_script_number(const int number)
{
    // Convert number to string
    char num_str[32];
    sprintf(num_str, "%d", number);

    // Map of regular digits to subscript Unicode characters
    const char *subscripts[] = {"₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉"};

    // Print each digit as subscript
    for (int i = 0; num_str[i] != '\0'; i++)
    {
        if (num_str[i] >= '0' && num_str[i] <= '9')
        {
            printf("%s", subscripts[num_str[i] - '0']);
        }
        else if (num_str[i] == '-')
        {
            printf("₋"); // Unicode subscript minus
        }
    }
}

void print_super_script_number(const int number)
{
    // Convert number to string
    char num_str[32];
    sprintf(num_str, "%d", number);

    // Map of regular digits to superscript Unicode characters
    const char *superscripts[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};

    // Print each digit as superscript
    for (int i = 0; num_str[i] != '\0'; i++)
    {
        if (num_str[i] >= '0' && num_str[i] <= '9')
        {
            printf("%s", superscripts[num_str[i] - '0']);
        }
        else if (num_str[i] == '-')
        {
            printf("⁻"); // Unicode superscript minus
        }
    }
}

#endif