CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = matrix
OBJS = main.o matrix.o matrix_int.o matrix_float.o complex.o matrix_complex.o func.o tests.o 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

main.o: src/main.c include/func.h
	$(CC) $(CFLAGS) -c src/main.c

func.o: src/func.c include/func.h include/matrix/matrix_complex.h include/matrix/matrix_int.h include/matrix/matrix_float.h include/complex.h
	$(CC) $(CFLAGS) -c src/func.c

matrix.o: src/matrix.c include/matrix/matrix.h
	$(CC) $(CFLAGS) -c src/matrix.c

matrix_int.o: matrix_type/matrix_int.c include/matrix/matrix_int.h
	$(CC) $(CFLAGS) -c matrix_type/matrix_int.c

matrix_float.o: matrix_type/matrix_float.c include/matrix/matrix_float.h
	$(CC) $(CFLAGS) -c matrix_type/matrix_float.c

complex.o: matrix_type/complex.c include/complex.h
	$(CC) $(CFLAGS) -c matrix_type/complex.c

matrix_complex.o: matrix_type/matrix_complex.c include/complex.h include/matrix/matrix_complex.h
	$(CC) $(CFLAGS) -c matrix_type/matrix_complex.c

tests.o: src/tests.c include/tests.h
	$(CC) $(CFLAGS) -c src/tests.c

start: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean start