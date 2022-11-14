#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Get an integer from the user
 *
 * @param message char* - the message to print to the user.
 * @param min int - the minimum value of the integer.
 * @param max int - the maximum value of the integer.
 * @return int - the integer entered by the user.
 */
int get_integer_input(const char* message, int min, int max);

/**
 * @brief Get an float from the user
 *
 * @param message char* - the message to print to the user.
 * @param min float - the minimum value of the float.
 * @param max float - the maximum value of the float.
 * @return float - the float entered by the user.
 */
float get_float_input(const char* message, float min, float max);