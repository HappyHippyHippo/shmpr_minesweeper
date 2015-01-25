#ifndef HHH_CONSOLE_H
#define HHH_CONSOLE_H

#include <stdlib.h>

/**
 * @brief Console clearing function
 * Function used to clear the console of all the presented content
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_clear(void);

/**
 * @brief Char option reading function
 * Function used to request and read a character option from the standard input
 * stream.
 *
 * @param[out] readed Pointer to the character readed from the input stream.
 * @param[in] options C-style string with the list of options values to be accepted by the function.
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_option(char * readed, char * options, const char * message, ...);

/**
 * @brief String reading function
 * Function used to request and read a string from the standard input stream.
 *
 * @param[out] readed Pointer to the buffer that will store the readed string.
 * @param[in] buffer_size Size of the buffer that will store the readed string.
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_string(char * readed, size_t buffer_size, const char * message, ...);

/**
 * @brief Integer reading function
 * Function used to request and read a integer value from the standard input stream.
 *
 * @param[out] readed Pointer to the integer value readed from the input.
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_int(int * readed, const char * message, ...);

/**
 * @brief Integer reading function
 * Function used to request and read a integer value from the standard input stream.<br />
 * Thre readed value will be validated against a low and high limit value.
 *
 * @param[out] readed Pointer to the integer value readed from the input.
 * @param[in] min Minimum accpeted value of the readed value.
 * @param[in] max Maximum accpeted value of the readed value.
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_int_limit(int * readed, int min, int max, const char * message, ...);

/**
 * @brief Double reading function
 * Function used to request and read a double value from the standard input stream.
 *
 * @param[out] readed Pointer to the double value readed from the input.
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_double(double * readed, const char * message, ...);

/**
 * @brief Double reading function
 * Function used to request and read a double value from the standard input stream.<br />
 * Thre readed value will be validated against a low and high limit value.
 *
 * @param[out] readed Pointer to the double value readed from the input.
 * @param[in] min Minimum accpeted value of the readed value.
 * @param[in] max Maximum accpeted value of the readed value.
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_double_limit(double * readed, double min, double max, const char * message, ...);

/**
 * @brief Enter wait function
 * Function used to request and wait for the ENTER key press.
 *
 * @param[in] message C-style string with the string/format of the request message.<br />
 *                    If is a NULL value, no request message will be presented.
 * @param[in] ... List of arguments to populate the request message format.
 *
 * @return Error value representing the operation successfulness (hhh_error.h)
 */
int console_read_enter(const char * message, ...);

#endif
