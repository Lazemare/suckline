/* This file is part of the suckline program.
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details. */

/* Configurations */

/*
 * Segment types:
 * USER, CONDA, PATH,
 * GIT,  SYMBO, ERRNO
 *
 * Colors:
 * BLK, RED, GRN, CYN,
 * YEL, BLU, MAG, WHT
 */

#define SEGMENT_NUMBER      6
#define DIRECTORY_MODE      FIRST
#define PROMPT_SYMBOL       " $ "
#define PROMPT_SYMBOL_ERROR " 🤔 "
#define REPO_DIRTY_BG       YEL

static struct SEGMENT segment[] = {
	{USER,  BLK, YEL},
	{CONDA, WHT, MAG},
	{PATH,  WHT, BLU},
	{GIT,   BLK, CYN},
	{SYMBO, WHT, BLK},
	{ERRNO, WHT, RED},
};
