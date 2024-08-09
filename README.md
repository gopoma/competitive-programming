# competitive-programming

**g++ installation:** `https://code.visualstudio.com/docs/cpp/config-mingw`

**make:** `https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows`

**Precompiling <bits/stdc++.h>:**
```bash
g++ -std=c++17 -g -O2 -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL -fmax-errors=2 -Wno-sign-conversion -Wfloat-equal -Wduplicated-cond -Wlogical-op stdc++.h
```
