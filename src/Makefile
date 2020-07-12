# GNU Flags
CC      = gcc
AR      = ar
CFLAGS  = -O3 -Wall
ARFLAGS = -rc

# Objects
INCS    = -I../include
OBJS    = readdlm.o writedlm.o
LIB     = ../lib/libdlm.a
EXE     = ../test/test.x

# All: lib
.PHONY : all
all: lib

readdlm.o:
	$(CC) $(INCS) $(CFLAGS) -c readdlm.c
writedlm.o:
	$(CC) $(INCS) $(CFLAGS) -c writedlm.c

lib: $(OBJS)
	mkdir -p ../lib
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

test: lib
	$(CC) -o $(EXE) $(INCS) ../test/main.c -L../lib -ldlm
	cd ../test && ./test.x txt

# Remove all object files.
.PHONY : clean
clean:
	rm -f $(OBJS)

# Remove all object files and executables.
.PHONY : veryclean
veryclean:
	rm -rf $(OBJS) ../lib ../test/test.x ../test/out
