alias clr="clear"
co() { g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -Wconversion -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -o ./bin/$1 $1.cpp; }
run() { co $1 && ./bin/$1; }
