CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = matrix
OBJS = main.o matrix.o matrix_int.o func.o tests.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: main.c include/func.h
	$(CC) $(CFLAGS) -c main.c

func.o: func.c include/func.h include/matrix/matrix_complex.h include/matrix/matrix_int.h include/matrix/matrix_float.h include/complex.h
	$(CC) $(CFLAGS) -c func.c

matrix.o: matrix.c include/matrix/matrix.h
	$(CC) $(CFLAGS) -c matrix.c

matrix_int.o: matrix_type/matrix_int.c include/matrix/matrix_int.h
	$(CC) $(CFLAGS) -c matrix_int.c

tests.o: tests.c include/tests.h
	$(CC) $(CFLAGS) -c tests.c

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean test