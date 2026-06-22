import sys
input = sys.stdin.readline

import math

def inp():
    return(int(input()))

def inlt():
    return(list(map(int,input().split())))

def lcm(a, b):
    return abs(a*b) // math.gcd(a, b)

def cdiv(a, b):
    return -(a // -b)

def calc(L, R, c):
    left = cdiv(L, c)
    right = R // c

    if(left > right):
        return 0
    else:
        return right - left + 1

# Driver Code
if __name__ == '__main__':
    t = inp()

    for _ in range(t):
        arr = inlt()

        a = arr[0]
        b = arr[1]
        m = arr[2]

        L = lcm(a, b)
        R = L + m

        val1 = calc(L, R, a)
        val2 = calc(L, R, b)

        ans = val1 + val2
        print(ans)



# This code is contributed by himanshu77
