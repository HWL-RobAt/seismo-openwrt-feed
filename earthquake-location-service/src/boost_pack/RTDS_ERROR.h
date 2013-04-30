
#ifndef RTDS_ERROR_H_INCLUDED
#define RTDS_ERROR_H_INCLUDED

/* these funky macros are needed in order to transform the line number into a
 * C string at compile-time */
#define SX_STRSTR(param)  #param
#define SX_STR(param)     SX_STRSTR(param)
#define SX_LINE           SX_STR(__LINE__)

/**@brief Prints out an SDL-RT runtime-error including file and line.
 */
#define SX_ERROR(msg) \
	fprintf(stderr, "Error occurred in file " __FILE__ \
	        " at line " SX_LINE ":\n\t" #msg "\n")

/**@brief Defines a print for debugging purposes.
 */
#ifdef DEBUG
	#define SX_DEBUG(...) fprintf(stdout, __VA_ARGS__)
#else
	#define SX_DEBUG(...) while(0)
#endif

#endif
