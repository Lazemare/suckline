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

/* Copy len chars from str2[pos2] to str1[pos1] */
inline static void my_strcpy(char *str1, char *str2,
	int pos1, int pos2, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		str1[pos1 + i] = str2[pos2 + i];
	}
}

/* Check if two chars are parts of a Chinese word. */
inline static int is_zh_ch(char p, char p1)
{
	int is_zh_ch = 0;

	if (p & 0x80 && p1 & 0x80) {
		is_zh_ch = 1;
	} else {
		is_zh_ch = 0;
	}
	return is_zh_ch;
}

/* substitute home directory with a `~' */
static int strip_home(char *str)
{
	int i = 0;
	int if_home = 0;
	int len_str = 0;
	int len_home = 0;
	const char *home;

	/* determine if we are at home */
	home = getenv("HOME");
	if (home == NULL) {
		return -1; /* homeless */
	}
	len_str  = strlen(str);
	len_home = strlen(home);
	if (len_home == strlen(str)) {
		if_home = 1;
	}
	/* strip */
	if (strncmp(str,home,len_home) == 0) {
		str[0] = '~';
		for (i = 1; i < len_home; i++) {
			str[i] = '\0';
		}
		for (i = len_home; i < len_str; i++) {
			str[i - len_home + 1] = str[i];
			str[i] = '\0';
		}
	}
	return if_home;
}

/* Same as getcwd, but could only print the first letter
 * of cwd. */
static void my_getcwd(char *buff, int len, int mode)
{
	/*
	 * mode :
	 * 0 for printing full name of directory,
	 * 1 for printing first letter of directory names,
	 * 2 for only printing name of last directory.
	 * e.g.
	 * 0: ~/aaa/bbb/ccc/ddd
	 * 1: ~/a/b/c/d
	 * 2: ddd
	 */

	int i = 0;
	int home = 0;
	int last = 0;
	int count = 0;
	char buff_local[len];
	memset(buff_local, 0, len);

	getcwd(buff_local,len);
	home = strip_home(buff_local);
	switch (mode) {
	case 0:
		strcat(buff,buff_local);
		break;
	case 1:
		if (buff_local[0] == '~') {
			buff[count] = '~';
			count++;
		}
		if (home == 1) {
			break;
		}
		for (i = 0; i < len; i++) {
			if (buff_local[i] == '/') {
				if (is_zh_ch(buff_local[i+1], buff_local[i+2])) {
					my_strcpy(buff,buff_local,count,i,4);
					count += 4;
				} else {
					my_strcpy(buff,buff_local,count,i,2);
					count += 2;
				}
				last = i;
			}
		}
		if (is_zh_ch(buff[count-1],buff[count-2])) {
			last += 4;
		} else {
			last += 2;
		}
		my_strcpy(buff,buff_local,count,last,len-last);
		break;
	case 2:
		if (home == 1) {
			buff[count] = '~';
		} else {
			for (i = 0; i < len; i++) {
				if (buff_local[i] == '/') {
					last = i;
				}
			}
			last++;
			my_strcpy(buff,buff_local,count,last,len-last);
		}
		break;
	}
}

/* Get current path. The output string contains path and
 * permission statement. */
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
