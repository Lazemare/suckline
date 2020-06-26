# GNU Flags
CC      = gcc
CFLAGS  = -O3 -Wall -std=c99
LDFLAGS = -static

# Install path
INSPATH = /usr/bin

# Include
INCS    =

# Objects
OBJS    = config.o git.o path.o segment.o suckline.o

# Executable
EXE     = suckline

# All: suckline
.PHONY : all
all: suckline

config.o:
	$(CC) $(INCS) $(CFLAGS) -c config.c
git.o:
	$(CC) $(INCS) $(CFLAGS) -c git.c
path.o:
	$(CC) $(INCS) $(CFLAGS) -c path.c
segment.o:
	$(CC) $(INCS) $(CFLAGS) -c segment.c
suckline.o:
	$(CC) $(INCS) $(CFLAGS) -c suckline.c

suckline: $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS)

# Install
.PHONY : install
install: suckline
	cp $(EXE) $(INSPATH)

# Remove all object files.
.PHONY : clean
clean:
	rm -f $(OBJS)

# Remove all object files and executables.
.PHONY : veryclean
veryclean:
	rm -f $(EXE) $(OBJS)
