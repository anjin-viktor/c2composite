all: util_test
	

util_test: util_test.c ../src/util.o
	gcc -o util_test ../src/util.o ../unit_tests/util_test.c -lcunit

../src/util.o: ../src/util.c ../src/util.h
	make -C ../src/ util.o


clean:
	rm -f util_test

test:
	./util_test

