mmul:
	g++ -Wall -Werror -std=c++17 MatrixMul/mmul.cpp -o mmul.o

line:
	echo ---------------------------------------------

run:
	./mmul.o

clean:
	rm mmul.o
