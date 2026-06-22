alias clr="clear"
co() { g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -DLOCAL -o ./bin/$1 $1.cpp; }
run() { co $1 && ./bin/$1; }
