compile:
	g++ -std=c++17 -g -Wl,--stack=268435456 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
run:
	make compile && ./bin/${F}.out
