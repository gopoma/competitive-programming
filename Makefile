co:
	g++ -std=c++17 -g -Wl,--stack=26843545600 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
run:
	make co && ./bin/${F}.out
coxd:
	g++ -std=c++17 -g -Wl,--stack=26843545600 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
xd:
	make coxd && ./bin/${F}.out
