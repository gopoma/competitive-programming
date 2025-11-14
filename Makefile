compile:
	g++ -std=c++20 -g -Wl,--stack=26843545600 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
run:
	make compile && ./bin/${F}.out
xd:
	g++ -std=c++20 -Wl,--stack=26843545600 -o ./bin/${F}.out ${F} && ./bin/${F}.out
rpc:
	g++ -std=c++11 -DLOCAL -o ./bin/${F}.out ${F} && ./bin/${F}.out
