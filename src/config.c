#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suckline.h"

/* Convert configurations into coresponding strings and arrays. */
void conv_conf(struct CONFIG config, struct PROMPT *prompt)
{
	int i = 0;
	int git_info = 0;

	for (i = 0; i < prompt->segnum; i++) {
		/* strings */
		switch (config.segment_type[i]) {
		case 1:
			get_username(prompt->string[i]);
			break;
		case 2:
			my_getcwd(prompt->string[i],MAXLPS,config.directory_mode);
			break;
		case 3:
			if (!prompt->errno) {
				prompt->string[i] = config.prompt_symbol;
			} else {
				prompt->string[i] = config.prompt_symbol_err;
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
				memset(prompt->string[i], 0, MAXLPS);
				break;
			case 2:
				/* git dir, give a warning */
				config.color_bg[i] = config.color_bg_repo_dirty;
				break;
			case 3:
				/* repo dirty */
				config.color_bg[i] = config.color_bg_repo_dirty;
				break;
			}
			break;
		default:
			memset(prompt->string[i], 0, MAXLPS);
		}
		/* colors */
		prompt->color_fg[i] = config.color_fg[i];
		prompt->color_bg[i] = config.color_bg[i];
	}
}
