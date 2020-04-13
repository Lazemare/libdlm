# GNU Flags
CC      = gcc
AR      = ar
CFLAGS  = -O3 -Wall
ARFLAGS = -rc
LDFLAGS = -fPIC -shared

# Intel Flags
# CC      = icc
# AR      = ar
# CFLAGS  = -O3 -xhost
# LDFLAGS = 

# Objects
INCS    = -I./include
OBJS    = readdlm.o writedlm.o
LIB     = lib/libdlm.so.1
LIB_    = lib/libdlm.a
EXE     = test/test.x

# All: aaimd
.PHONY : all
all: test

readdlm.o:
	$(CC) $(INCS) $(CFLAGS) -c src/readdlm.c
writedlm.o:
	$(CC) $(INCS) $(CFLAGS) -c src/writedlm.c

lib: $(OBJS)
	$(CC) -o $(LIB) $(OBJS) $(LDFLAGS)
	$(AR) $(ARFLAGS) $(LIB_) $(OBJS)

test: lib
	$(CC) -o $(EXE) $(INCS) test/main.c -L./lib -ldlm
	cd ./test && ./test.x txt

# Remove all object files.
.PHONY : clean
clean:
	rm -f $(OBJS)

# Remove all object files and executables.
.PHONY : veryclean
veryclean:
	rm -f $(OBJS) ./lib/* ./test/test.x ./test/out

