/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suckline.h"
#include "config.h"

/* Convert configurations into coresponding strings and arrays. */
void conv_conf(struct PROMPT *prompt)
{
	int i = 0;
	int git_info = 0;
	extern struct SEGMENT segment[];

	for (i = 0; i < prompt->segnum; i++) {
		/* strings */
		switch (segment[i].segment_type) {
		case 1:
			get_username(prompt->string[i]);
			break;
		case 2:
			my_getcwd(prompt->string[i],MAXLPS,DIRECTORY_MODE);
			break;
		case 3:
			if (!prompt->errno) {
				strcat(prompt->string[i],PROMPT_SYMBOL);
			} else {
				strcat(prompt->string[i],PROMPT_SYMBOL_ERROR);
			}
			break;
		case 4:
			/* only print something when errno != 0 */
			if (prompt->errno) {
				sprintf(prompt->string[i]," %d ",prompt->errno);
			}
			break;
		case 5:
			get_conda_path(prompt->string[i]);
			break;
		case 6:
			git_info = git(prompt->string[i]);
			switch (git_info) {
			case 1:
				/* if not a repo, purge this segment */
				break;
			case 2:
				/* git dir, give a warning */
				segment[i].color_bg = REPO_DIRTY_BG;
				break;
			case 3:
				/* repo dirty */
				segment[i].color_bg = REPO_DIRTY_BG;
				break;
			}
			break;
		default:
			memset(prompt->string[i], 0, MAXLPS);
		}
		/* colors */
		prompt->color_fg[i] = segment[i].color_fg;
		prompt->color_bg[i] = segment[i].color_bg;
	}
}
