#include <gui.h>

/**
 * @brief Get an integer from the user
 *
 * @param message char* - the message to print to the user.
 * @param min int - the minimum value of the integer.
 * @param max int - the maximum value of the integer.
 * @return int - the integer entered by the user.
 */
int get_integer_input(const char* message, int min, int max) {
    char inputstring[256];
    int tmp, input=max+1;
    do {
        printf("%s", message);
        scanf("%s", inputstring);
        fflush(stdin);
        tmp = atoi(inputstring);
        if (tmp >= min && tmp <= max) {
            input = tmp;
        }
    } while (input == max+1);

    return input;
}

/**
 * @brief Get an float from the user
 *
 * @param message char* - the message to print to the user.
 * @param min int - the minimum value of the float.
 * @param max int - the maximum value of the float.
 * @return int - the float entered by the user.
 */
float get_float_input(const char* message, float min, float max) {
    char inputstring[256];
    float tmp, input=max+1;
    do {
        printf("%s", message);
        scanf("%s", inputstring);
        fflush(stdin);
        tmp = atof(inputstring);
        if (tmp >= min && tmp <= max) {
            input = tmp;
        }
    } while (input == max+1);

    return input;
}