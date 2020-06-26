#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "suckline.h"

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
			strcat(prompt->buff,
				COLOR_FG[prompt->shell][prompt->color_fg[i]]);
			strcat(prompt->buff,
				COLOR_BG[prompt->shell][prompt->color_bg[i]]);
			strcat(prompt->buff,prompt->string[i]);
			strcat(prompt->buff,RESET[prompt->shell]);
			strcat(prompt->buff,
				COLOR_FG[prompt->shell][prompt->color_bg[i]]);
			if (i != (prompt->segnum - 1)) {
				if (strlen(prompt->string[i+1])) {
					strcat(prompt->buff,
						COLOR_BG[prompt->shell][prompt->color_bg[i+1]]);
				} else if ((i+2) < (prompt->segnum - 1)) {
					strcat(prompt->buff,
						COLOR_BG[prompt->shell][prompt->color_bg[i+2]]);
				}
			}
			strcat(prompt->buff,"");
			strcat(prompt->buff,RESET[prompt->shell]);
		}
	}
	strcat(prompt->buff," \n");
}