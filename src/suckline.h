/* prompt length */
#define MAXLEN 10000 /* Big enough I think */
#define MAXSEG 10
#define MAXLPS 1000

/* segment name */
#define USER  1
#define PATH  2
#define SYMBO 3
#define ERROR 4
#define CONDA 5
#define GIT   6
/* segment color */
#define BLK   0
#define RED   1
#define GRN   2
#define YEL   3
#define BLU   4
#define MAG   5
#define CYN   6
#define WHT   7
/* directory mode */
#define FULL  0
#define FIRST 1
#define LAST  2

/* structures */

struct CONFIG {
	/* Number of segments */
	int   segment_number;
	/* Type of each segment */
	int   segment_type[MAXSEG];
	/* foreground color number of each segment */
	int   color_fg[MAXSEG];
	/* background color number of each segment */
	int   color_bg[MAXSEG];
	/* background color when repo is dirty */
	int   color_bg_repo_dirty;
	/* directory showing mode */
	int   directory_mode;
	/* prompt symbol */
	char *prompt_symbol;
	/* prompt symbol when errno != 0 */
	char *prompt_symbol_err;
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
	int    color_fg[MAXSEG];
	/* background color of each segment  */
	int    color_bg[MAXSEG];
	/* Output string */
	char   *buff;
};

/* functions */

void my_getcwd(char *buff, int len, int mode);

void conv_conf(struct CONFIG config, struct PROMPT *prompt);

void make_segment(struct PROMPT *prompt);

void get_conda_path(char *buff);

int git(char *str);