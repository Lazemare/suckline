#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suckline.h"

#define CAT2BUF(str) strcat(prompt->buff,str)
#define FG_NUM(num)  prompt->color_fg[num]
#define BG_NUM(num)  prompt->color_bg[num]
#define SHELL        prompt->shell

/* Make the powerline-like segment. */
void make_segment(struct PROMPT *prompt)
{
	/* buff        : output string
	 * string      : strings of each segment
	 * color_fg    : foreground color number of each segment
	 * color_bg    : background color number of each segment
	 * segment_num : number of segments
	 * errno       : shell error number
	 */

	int i = 0;
	extern const char COLOR_BG[2][8][20];
	extern const char COLOR_FG[2][8][20];
	extern const char RESET[2][20];

	/* skip blank segments. */
	/* make segment */
	for (i = 0; i < prompt->segnum; i++) {
		if (strlen(prompt->string[i])) {
			CAT2BUF(COLOR_FG[SHELL][FG_NUM(i)]);
			CAT2BUF(COLOR_BG[SHELL][BG_NUM(i)]);
			CAT2BUF(prompt->string[i]);
			CAT2BUF(RESET[SHELL]);
			CAT2BUF(COLOR_FG[SHELL][BG_NUM(i)]);
			if (i != (prompt->segnum - 1)) {
				if (strlen(prompt->string[i+1])) {
					CAT2BUF(COLOR_BG[SHELL][BG_NUM(i+1)]);
				} else if ((i+2) < (prompt->segnum - 1)) {
					CAT2BUF(COLOR_BG[SHELL][BG_NUM(i+2)]);
				}
			}
			CAT2BUF("");
			CAT2BUF(RESET[SHELL]);
		}
	}
	CAT2BUF(" \n");
}
