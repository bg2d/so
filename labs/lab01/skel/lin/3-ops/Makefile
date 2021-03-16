CC = gcc
CFLAGS = -Wall
LDLIBS =

all: ops

# Create object file for ops and link all the modules together
ops: ops.c add mul
	# Define HAVE_MATH symbol on preprocessing and
	# create object file
	$(CC) $(CFLAGS) -c -D HAVE_MATH ops.c
	# Link
	$(CC) $(CFLAGS) -o ops ops.o add.o mul.o -lm


# Create object file for add
add: add.c
	$(CC) $(CFLAGS) -c add.c

# Create object file for mul
mul: mul.c
	$(CC) $(CFLAGS) -c mul.c

clean:
	rm -rf *.o ops

