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
	extern struct CONFIG config;
	prompt.segnum = config.segment_number;
	prompt.string = (char **) malloc(prompt.segnum*sizeof(char *));
	for (int i = 0; i < prompt.segnum; i++) {
		prompt.string[i] = (char *) malloc(MAXLPS*sizeof(char));
		memset(prompt.string[i], 0, MAXLPS*sizeof(char));
	}
	prompt.buff = (char *) malloc(MAXLEN*sizeof(char));
	memset(prompt.buff, 0, MAXLEN*sizeof(char));

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
	conv_conf(config, &prompt);
	make_segment(&prompt);
	write(1,prompt.buff,strlen(prompt.buff));

	for (int i = 0; i < prompt.segnum; i++) {
		free(prompt.string[i]);
	}
	free(prompt.string);
	free(prompt.buff);
}
