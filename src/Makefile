# GNU Flags
CC      = gcc
CFLAGS  = -O3 -Wall -std=c99
LDFLAGS = -static

# Install path
INSPATH = /usr/bin

# Include
INCS    =

# Objects
OBJS    = config.o git.o path.o segment.o suckline.o user.o

# Executable
EXE     = suckline

# All: suckline
.PHONY : all
all: suckline

$(OBJS): %.o: %.c
	$(CC) $(INCS) $(CFLAGS) -c $<

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
