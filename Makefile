all:
	g++ -std=c++17 -g -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -o ./bin/${F}.out ${F}
run:
	make all && ./bin/${F}.out
