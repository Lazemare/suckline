/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

/* Configurations */
struct CONFIG config = {
	.segment_number      = 6,       /* number of segments */
	.directory_mode      = FIRST,   /* FIRST, LAST, FULL */
	.prompt_symbol       = " $ ",
	.prompt_symbol_err   = " 🤔 ",
	.color_bg_repo_dirty = YEL,

	.segment_type[0]     = USER,    /* Segment type:  */
	.segment_type[1]     = CONDA,   /* USER, CONDA, PATH, */
	.segment_type[2]     = PATH,    /* GIT,  SYMBO, ERRNO */
	.segment_type[3]     = GIT,
	.segment_type[4]     = SYMBO,
	.segment_type[5]     = ERRNO,

	.color_fg[0]         = BLK,     /* Colors: */
	.color_fg[1]         = WHT,     /* BLK, RED, GRN, CYN, */
	.color_fg[2]         = WHT,     /* YEL, BLU, MAG, WHT  */
	.color_fg[3]         = BLK,
	.color_fg[4]         = WHT,
	.color_fg[5]         = WHT,

	.color_bg[0]         = YEL,
	.color_bg[1]         = MAG,
	.color_bg[2]         = BLU,
	.color_bg[3]         = CYN,
	.color_bg[4]         = BLK,
	.color_bg[5]         = RED,
};
