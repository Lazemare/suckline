/* Basically I don't need this personally,
 * thus this routine could be buggy. Use this with care.
 */
#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "suckline.h"

/* Get git branch name. */
static int get_git_branch(char *str)
{
	int errno = 0;
	char *get_tag;
	char *get_branch;
	char buff[MAXLPS];
	static FILE *shell = NULL;

	/* This is the fastest one. Let us try this first. */
	get_branch = "git symbolic-ref --short HEAD 2> /dev/null";
	/* This one is slower, we try this when the first command failed. */
	get_tag = "git describe --tags --always 2> /dev/null";
	shell = popen(get_branch, "r");
	fgets(buff, MAXLPS, shell);
	errno = WEXITSTATUS(pclose(shell)); /* get exit number */
	if (!errno) {
		buff[strlen(buff) - 1] = '\0'; /* purge the '\n' */
		strcat(str,buff);
		return 0;
	} else {
		shell = popen(get_tag, "r");
		fgets(buff, MAXLPS, shell);
		errno = WEXITSTATUS(pclose(shell)); /* get exit number */
	}
	if (!errno) {
		buff[strlen(buff) - 1] = '\0'; /* purge the '\n' */
		strcat(str,buff);
		return 0;
	} else {
		return 1; /* Git not installed, not a repo, whatever */
	}
	return 0;
}

/* Check if cwd is git dir */
static int is_git_dir(void)
{
	char buff[MAXLPS];

	getcwd(buff,MAXLPS);
	if (strstr(buff,"/.git"))
		return 1;
	else
		return 0;
}

/* Get git repo information. */
static int get_git_info(int *ahead, int *behind)
{
	int i = 0;
	int count = 0;
	char *errchar;
	char *get_info;
	char *info_rst;
	char buff[MAXLPS];
	char info_buff[12]; /* enough for an int. */
	static FILE *shell = NULL;

	get_info = "git status --porcelain -b 2> /dev/null";
	shell = popen(get_info, "r");
	fgets(buff, MAXLPS, shell); /* read in one line first */
	/* If get_info gives more than one line,
	 * we know that repo is dirty. That's enough. */
	errchar = fgets(buff, MAXLPS, shell);
	pclose(shell); /* We do not need exit code this time. */
	if (errchar) {
		return 1;
	}
	/* parse */
	if ((info_rst = strstr(buff,"behind"))) {
		/* info_rst looks like "behind xxx]"
		 *                      ↑      ↑
		 *                      0      7
		 */
		for (i = 7; i < strlen(info_rst); i++) {
			if (info_rst[i] != ']') {
				info_buff[count] = info_rst[i];
				count++;
			}
		}
		*behind = atoi(info_buff);
	} else if ((info_rst = strstr(buff,"ahead"))) {
		/* info_rst looks like "ahead xxx]"
		 *                      ↑     ↑
		 *                      0     6
		 */
		for (i = 6; i < strlen(info_rst); i++) {
			if (info_rst[i] != ']') {
				info_buff[count] = info_rst[i];
				count++;
			}
		}
		*ahead = atoi(info_buff);
	}
	return 0;
}

/* Get git repo information. */
int git(char *str)
{
	int ahead = 0;
	int behind = 0;
	char tmp[12];
	strcat(str," ");
	if (get_git_branch(str)) {
		str[0] = '\0';
		return 1; /* Return 1 if not a repo. */
	}
	if (is_git_dir()) {
		memset(str, 0, strlen(str));
		strcat(str," ");
		strcat(str,"!GITDIR!");
		strcat(str," ");
		return 2; /* Return 2 if git dir. */
	}
	if (get_git_info(&ahead, &behind)) {
		strcat(str," ");
		return 3; /* Return 3 if repo dirty. */
	}
	strcat(str," ");
	if (ahead > 0) {
		sprintf(tmp,"%d",ahead);
		strcat(str,tmp);
		strcat(str,"⇡ ");
	} else if (behind > 0) {
		sprintf(tmp,"%d",behind);
		strcat(str,tmp);
		strcat(str,"⇣ ");
	}
	return 0;
}
