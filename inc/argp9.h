#include <stddef.h>

/*
 * Parser for strings with nine or fewer ascii characters
 * hence the name argp9
 */

#ifndef ARGP9_H
#define ARGP9_H

enum arg_option_type{
	DOUBLE,
	UNSIGNED_LONG
};

typedef struct{
	char* long_name;
	char* short_name;
	enum arg_option_type *arg_types;
	size_t nargs;
} usr_option;

/*
 * Hash a null terminated string 
 * @param str, null terminated string to hash
 * @return hash value for string 
 */
unsigned long long str_hash(char *str);

#endif
