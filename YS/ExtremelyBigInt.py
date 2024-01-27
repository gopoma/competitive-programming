import sys
input = sys.stdin.readline

import math

def inp():
    return(int(input()))

def inlt():
    return(list(map(int,input().split())))

def lcm (a, b):
    s = int(a)
    s1 = int(b)

    mul = s * s1

    gcd = math.gcd(s, s1)

    lcm = mul // gcd

    return lcm

# Driver Code
if __name__ == '__main__':
    t = inp()

    for _ in range(0, t):
        xd = inlt()
        A = xd[0]
        B = xd[1]
        C = xd[2]
        N = xd[3]
        A += 1
        B += 1
        C += 1

        sum1 = (N // A) + (N // B) + (N // C)
        sum2 = (N // lcm(A, B)) + (N // lcm(A, C)) + (N // lcm(B, C))
        sum3 = (N // lcm(A, lcm(B, C)))

        ans = sum1 - sum2 + sum3
        print(ans)

# This code is contributed by himanshu77
