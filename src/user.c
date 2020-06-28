#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suckline.h"

/* Get user name. */
void get_username(char *str)
{
	char *buff = NULL;

	strcat(str, " ");
	if ((buff = cuserid(NULL))) {
		strcat(str, buff);
	} else {
		strcat(str, "who?");
	}
	strcat(str, " ");
}