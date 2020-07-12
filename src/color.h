/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

/* Texts */

#define BLK_IB "\\[\\e[38;5;237m\\]"
#define RED_IB "\\[\\e[38;5;161m\\]"
#define GRN_IB "\\[\\e[38;5;10m\\]"
#define YEL_IB "\\[\\e[38;5;11m\\]"
#define BLU_IB "\\[\\e[38;5;31m\\]"
#define MAG_IB "\\[\\e[38;5;69m\\]"
#define CYN_IB "\\[\\e[38;5;50m\\]"
#define WHT_IB "\\[\\e[38;5;252m\\]"

#define BLK_I "\e[38;5;237m"
#define RED_I "\e[38;5;161m"
#define GRN_I "\e[38;5;10m"
#define YEL_I "\e[38;5;11m"
#define BLU_I "\e[38;5;31m"
#define MAG_I "\e[38;5;69m"
#define CYN_I "\e[38;5;50m"
#define WHT_I "\e[38;5;252m"

/* Backgrounds */

#define BLKB_IB "\\[\\e[48;5;237m\\]"
#define REDB_IB "\\[\\e[48;5;161m\\]"
#define GRNB_IB "\\[\\e[48;5;10m\\]"
#define YELB_IB "\\[\\e[48;5;11m\\]"
#define BLUB_IB "\\[\\e[48;5;31m\\]"
#define MAGB_IB "\\[\\e[48;5;69m\\]"
#define CYNB_IB "\\[\\e[48;5;50m\\]"
#define WHTB_IB "\\[\\e[48;5;252m\\]"

#define BLKB_I "\e[48;5;237m"
#define REDB_I "\e[48;5;161m"
#define GRNB_I "\e[48;5;10m"
#define YELB_I "\e[48;5;11m"
#define BLUB_I "\e[48;5;31m"
#define MAGB_I "\e[48;5;69m"
#define CYNB_I "\e[48;5;50m"
#define WHTB_I "\e[48;5;252m"

/* Misc */

#define BOLD_I   "\e[1m"
#define ULINE_I  "\e[4m"
#define BLINK_I  "\e[5m"
#define RESET_I  "\e[0m"
#define BOLD_IB  "\\[\\e[1m\\]"
#define ULINE_IB "\\[\\e[4m\\]"
#define BLINK_IB "\\[\\e[5m\\]"
#define RESET_IB "\\[\\e[0m\\]"

/* Arrays */

const char COLOR_FG[2][8][20] = {{
	BLK_IB, RED_IB, GRN_IB, YEL_IB,
	BLU_IB, MAG_IB, CYN_IB, WHT_IB,
} , {
	BLK_I, RED_I, GRN_I, YEL_I,
	BLU_I, MAG_I, CYN_I, WHT_I,
}};

const char COLOR_BG[2][8][20] = {{
	BLKB_IB, REDB_IB, GRNB_IB, YELB_IB,
	BLUB_IB, MAGB_IB, CYNB_IB, WHTB_IB,
} , {
	BLKB_I, REDB_I, GRNB_I, YELB_I,
	BLUB_I, MAGB_I, CYNB_I, WHTB_I,
}};

const char RESET[2][20] = {
	RESET_IB, RESET_I,
};
