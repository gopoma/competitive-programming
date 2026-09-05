co:
	g++ -std=c++17 -g -Wl,--stack=26843545600 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
run:
	make co && ./bin/${F}.out
coxd:
	g++ -std=c++17 -g -Wl,--stack=26843545600 -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Winvalid-pch -o ./bin/${F}.out ${F}
xd:
	make coxd && ./bin/${F}.out
gdb:
	make co && gdb -q -batch -ex "set breakpoint pending on" -ex "break __gnu_debug::_Error_formatter::_M_error() const" -ex run -ex bt --args ./bin/${F}.out
gdbxd:
	make coxd && gdb -q -batch -ex "set breakpoint pending on" -ex "break __gnu_debug::_Error_formatter::_M_error() const" -ex run -ex bt --args ./bin/${F}.out
