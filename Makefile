compile:
	g++ -std=c++17 -g -Wl,--stack=26843545600 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
run:
	make compile && ./bin/${F}.out
xd:
	g++ -std=c++17 -o ./bin/${F}.out ${F} && ./bin/${F}.out
xd-dbg:
	g++ -std=c++17 -DLOCAL -o ./bin/${F}.out ${F} && ./bin/${F}.out
icpc:
	g++ -std=c++11 -o ./bin/${F}.out ${F} && ./bin/${F}.out
icpc-dbg:
	g++ -std=c++11 -DLOCAL -o ./bin/${F}.out ${F} && ./bin/${F}.out
