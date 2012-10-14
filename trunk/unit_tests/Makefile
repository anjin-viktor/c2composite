all: util_test.o unit_tests.o ../src/util.o
	gcc -o unit_tests util_test.o  unit_tests.o ../src/util.o -lcunit	

unit_tests.o: unit_tests.c
	gcc -c unit_tests.c

util_test.o: util_test.c
	gcc -c util_test.c


../src/util.o: ../src/util.c ../src/util.h
	make -C ../src/ util.o


clean:
	rm -f unit_tests *.o

test:
	./unit_tests

