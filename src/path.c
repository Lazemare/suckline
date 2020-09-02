/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suckline.h"

/* Check if two chars are parts of a Chinese word. */
#define IS_ZH_CN(p, p1) ((p & 0x80 && p1 & 0x80) > 0)

/* Copy len chars from str2[pos2] to str1[pos1] */
#define STRCPY(str1, str2, pos1, pos2, len) do { \
	for (int pppp = 0; pppp < len; pppp++) {     \
		str1[pos1 + pppp] = str2[pos2 + pppp];   \
	}                                            \
} while (0)


/* Copy len chars from str2[pos2] to str1[pos1] */
#define STRRCPY(str1, str2, pos1, pos2, len) do {          \
	for (int pppp = 0; pppp < len; pppp++) {               \
		str1[pos1 + len - pppp] = str2[pos2 + len - pppp]; \
	}                                                      \
} while (0)

/* Determine if we are at home or under home dir. */
static int is_at_home(char *pwd, const char *home)
{
	int len_pwd = 0;
	int len_home = 0;

	len_pwd  = strlen(pwd);
	len_home = strlen(home);
	if (home == NULL)
		return -1; /* homeless, wtf */
	if (strncmp(pwd, home,len_home) == 0) {
		if (len_home == len_pwd)
			return 2; /* at home dir */
		else
			return 1; /* at somewhere under home dir */
	} else if (strlen(pwd) == 1) {
		return 3; /* at / */
	} else {
		return 0; /* not at home */
	}
}

/* substitute home directory with a `' */
static void strip_home(char *pwd, const char *home, int is_at_home)
{
	int len_pwd = 0;
	int len_home = 0;

	len_pwd  = strlen(pwd);
	len_home = strlen(home);
	if (is_at_home == 2) {
		memset(pwd, 0, len_pwd);
		strcpy(pwd, "");
	} else if (is_at_home == 1) {
		memset(pwd, 0, len_home);
		STRCPY(pwd, "", 0, 0, len_utf_8);
		STRCPY(pwd, pwd, len_utf_8, len_home, (len_pwd - len_home));
		memset((pwd + len_utf_8 + len_pwd - len_home), \
			0, (len_home - len_utf_8));
	} else {
		STRRCPY(pwd, pwd, len_utf_8, 0, len_pwd);
		STRCPY(pwd, "", 0, 0, len_utf_8);
	}
}

/* format path string */
static void format_path(char *pwd, int mode)
{
	/*
	 * mode :
	 * 0 for printing full name of directory,
	 * 1 for printing first letter of directory names,
	 * 2 for only printing name of last directory.
	 * e.g.
	 * 0: ~  aaa  bbb  ccc  ddd
	 * 1: ~  a  b  c  ddd
	 * 2: ~  ddd
	 */

	int len_seg = 0;
	int len_pwd = 0;
	char *buff = NULL;
	char *pos = NULL;
	char *pos_old = NULL;

	len_pwd = strlen(pwd);
	buff = calloc(len_pwd + 1, 1);
	strcpy(buff, pwd);
	memset(pwd, 0, len_pwd);
	strncpy(pwd, buff, len_utf_8);
	pos_old = buff + len_utf_8;

	do {
		pos = strchr(pos_old + 1, '/');
		len_seg = pos - pos_old -1;
		if (len_seg <= 0 || pos == NULL) {
			break;
		} else {
			if (mode == 0) {
				strcat(pwd, "  ");
				strncat(pwd, pos_old + 1, len_seg);
			} else if (mode == 1) {
				strcat(pwd, "  ");
				if (IS_ZH_CN(*(pos + 1), *(pos + 2)))
					strncat(pwd, pos_old + 1, 4);
				else
					strncat(pwd, pos_old + 1, 1);
			}
		}
		pos_old = pos;
	} while (1);
	strcat(pwd, "  ");
	strncat(pwd, pos_old + 1, (buff + len_pwd - pos_old));
	free(buff);
}

/*
 * Same as getcwd, but could only print the first letter of cwd.
 */
static void my_getcwd(char *pwd, int len, int mode)
{
	int is_at_home_ = 0;
	const char *home = NULL;

	getcwd(pwd, len);
	home = getenv("HOME");
	is_at_home_ = is_at_home(pwd, home);
	strip_home(pwd, home, is_at_home_);
	if (is_at_home_ != 2 && is_at_home_ != 3)
		format_path(pwd, mode);
}

/*
 * Get current path. The output string contains path and
 * permission statement.
 */
void get_cwd(char *buff, int mode)
{
	char buff_local[MAXLPS];
	memset(buff_local, 0, MAXLPS);

	strcat(buff," ");
	/* Get path. */
	my_getcwd(buff_local, MAXLPS, mode);
	strcat(buff, buff_local);
	/* Check if we have write permission here. */
	if (access(".",W_OK))
		strcat(buff," ");
	strcat(buff," ");
}

/* Get Conda paths */
void get_conda_path(char *buff)
{
	const char *conda_path;

	conda_path = getenv("CONDA_DEFAULT_ENV");
	if (conda_path != NULL) {
		strcat(buff," ");
		strcat(buff,conda_path);
		strcat(buff," ");
	}
}
