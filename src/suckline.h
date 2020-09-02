/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

/* segment length */
#define MAXLPS 1000 /* Big enough I think */

/* segment name */
#define USER   1
#define PATH   2
#define SYMBO  3
#define ERRNO  4
#define CONDA  5
#define GIT    6
/* segment color */
#define BLK    0
#define RED    1
#define GRN    2
#define YEL    3
#define BLU    4
#define MAG    5
#define CYN    6
#define WHT    7
/* directory mode */
#define FULL   0
#define FIRST  1
#define LAST   2

/* structures */

struct SEGMENT {
	/* Type of each segment */
	int    segment_type;
	/* foreground color number of each segment */
	int    color_fg;
	/* background color number of each segment */
	int    color_bg;
};

struct PROMPT {
	/* shell type. 0 for bash, 1 for fish */
	int    shell;
	/* shell error number */
	int    errno;
	/* number of segments */
	int    segnum;
	/* strings of each segment */
	char **string;
	/* foreground color of each segment  */
	int    *color_fg;
	/* background color of each segment  */
	int    *color_bg;
	/* Output string */
	char   *buff;
};

/* functions */

void make_segment(struct PROMPT *prompt);

void conv_conf(struct PROMPT *prompt);

void get_cwd(char *buff, int mode);

void get_conda_path(char *buff);

void get_username(char *str);

int git(char *str);

/* lengths */

static const size_t len_utf_8 = strlen("");
