alias clr="clear"
co() { g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -Wconversion -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -o ./bin/$1 $1.cpp; }
run() { co $1 && ./bin/$1; }

coxd() { g++ -std=c++11 -O2 -Wall -Wextra -Wshadow -Wconversion -o ./bin/$1 $1.cpp; }
runxd() { coxd $1 && ./bin/$1; }
