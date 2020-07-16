/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

/* This prompt sucks! */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suckline.h"
#include "config.h"
#include "color.h"

int main(int argc, char *argv[])
{
	/* Load configurations. */
	struct PROMPT prompt;
	prompt.errno = 0;
	prompt.segnum = SEGMENT_NUMBER;
	prompt.color_fg = (int *) malloc(SEGMENT_NUMBER*sizeof(int));
	prompt.color_bg = (int *) malloc(SEGMENT_NUMBER*sizeof(int));
	prompt.string = (char **) malloc(prompt.segnum*sizeof(char *));
	for (int i = 0; i < prompt.segnum; i++) {
		prompt.string[i] = (char *) malloc(MAXLPS*sizeof(char));
		memset(prompt.string[i], 0, MAXLPS*sizeof(char));
	}
	prompt.buff = (char *) malloc(SEGMENT_NUMBER*MAXLPS*sizeof(char));
	memset(prompt.buff, 0, SEGMENT_NUMBER*MAXLPS*sizeof(char));

	if (argc > 1) {
		if (strcmp(argv[1],"bash") == 0) {
			prompt.shell = 0;
		} else {
			prompt.shell = 1;
		}
	} else {
		prompt.shell = 1;
	}
	if (argc > 2) {
		prompt.errno = atoi(argv[2]);
	}
	conv_conf(&prompt);
	make_segment(&prompt);
	write(1,prompt.buff,strlen(prompt.buff));

	for (int i = 0; i < prompt.segnum; i++) {
		free(prompt.string[i]);
	}
	free(prompt.color_fg);
	free(prompt.color_bg);
	free(prompt.string);
	free(prompt.buff);
}
