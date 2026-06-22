import sys
input = sys.stdin.readline

from decimal import Decimal, getcontext

getcontext().prec = 100

def moneyfmt(value, places=2, curr='', sep=',', dp='.',
             pos='', neg='-', trailneg=''):
    """Convert Decimal to a money formatted string.

    places:  required number of places after the decimal point
    curr:    optional currency symbol before the sign (may be blank)
    sep:     optional grouping separator (comma, period, space, or blank)
    dp:      decimal point indicator (comma or period)
             only specify as blank when places is zero
    pos:     optional sign for positive numbers: '+', space or blank
    neg:     optional sign for negative numbers: '-', '(', space or blank
    trailneg:optional trailing minus indicator:  '-', ')', space or blank

    >>> d = Decimal('-1234567.8901')
    >>> moneyfmt(d, curr='$')
    '-$1,234,567.89'
    >>> moneyfmt(d, places=0, sep='.', dp='', neg='', trailneg='-')
    '1.234.568-'
    >>> moneyfmt(d, curr='$', neg='(', trailneg=')')
    '($1,234,567.89)'
    >>> moneyfmt(Decimal(123456789), sep=' ')
    '123 456 789.00'
    >>> moneyfmt(Decimal('-0.02'), neg='<', trailneg='>')
    '<0.02>'

    """
    q = Decimal(10) ** -places      # 2 places --> '0.01'
    sign, digits, exp = value.quantize(q).as_tuple()
    result = []
    digits = list(map(str, digits))
    build, next = result.append, digits.pop
    if sign:
        build(trailneg)
    for i in range(places):
        build(next() if digits else '0')
    if places:
        build(dp)
    if not digits:
        build('0')
    i = 0
    while digits:
        build(next())
        i += 1
        if i == 3 and digits:
            i = 0
            build(sep)
    build(curr)
    build(neg if sign else pos)
    return ''.join(reversed(result))

def pi():
    """Compute Pi to the current precision.

    >>> print(pi())
    3.141592653589793238462643383

    """
    getcontext().prec += 2  # extra digits for intermediate steps
    three = Decimal(3)      # substitute "three=3.0" for regular floats
    lasts, t, s, n, na, d, da = 0, three, 3, 1, 0, 0, 24
    while s != lasts:
        lasts = s
        n, na = n+na, na+8
        d, da = d+da, da+32
        t = (t * n) / d
        s += t
    getcontext().prec -= 2
    return +s               # unary plus applies the new precision

def exp(x):
    """Return e raised to the power of x.  Result type matches input type.

    >>> print(exp(Decimal(1)))
    2.718281828459045235360287471
    >>> print(exp(Decimal(2)))
    7.389056098930650227230427461
    >>> print(exp(2.0))
    7.38905609893
    >>> print(exp(2+0j))
    (7.38905609893+0j)

    """
    getcontext().prec += 2
    i, lasts, s, fact, num = 0, 0, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 1
        fact *= i
        num *= x
        s += num / fact
    getcontext().prec -= 2
    return +s

def cos(x):
    """Return the cosine of x as measured in radians.

    The Taylor series approximation works best for a small value of x.
    For larger values, first compute x = x % (2 * pi).

    >>> print(cos(Decimal('0.5')))
    0.8775825618903727161162815826
    >>> print(cos(0.5))
    0.87758256189
    >>> print(cos(0.5+0j))
    (0.87758256189+0j)

    """
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

def sin(x):
    """Return the sine of x as measured in radians.

    The Taylor series approximation works best for a small value of x.
    For larger values, first compute x = x % (2 * pi).

    >>> print(sin(Decimal('0.5')))
    0.4794255386042030002732879352
    >>> print(sin(0.5))
    0.479425538604
    >>> print(sin(0.5+0j))
    (0.479425538604+0j)

    """
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

def acos(x):
    mn, mx = Decimal(0), Decimal(pi())
    for i in range(100):
        md = (mn + mx) / 2
        if cos(md) <= x:
            mx = md
        else:
            mn = md
    return mx

def inp():
    return(Decimal(input()))

def inlt():
    return(list(map(Decimal,input().split())))

# Function to return area of intersection
def intersectionArea(X1, Y1, R1, X2, Y2, R2) :
    Pi = pi()

    # Calculate the euclidean distance
    # between the two points
    d = Decimal(((X2 - X1) * (X2 - X1)) + ((Y2 - Y1) * (Y2 - Y1))).sqrt()

    if (d > R1 + R2) :
        ans = 0

    elif (d <= (R1 - R2) and R1 >= R2) :
        ans = Pi * R2 * R2

    elif (d <= (R2 - R1) and R2 >= R1) :
        ans = Pi * R1 * R1

    else :
        alpha = acos(((R1 * R1) + (d * d) - (R2 * R2)) / (Decimal(2) * R1 * d)) * Decimal(2)
        beta = acos(((R2 * R2) + (d * d) - (R1 * R1)) / (Decimal(2) * R2 * d)) * Decimal(2)

        a1 = (Decimal(0.5) * beta * R2 * R2 ) - (Decimal(0.5) * R2 * R2 * sin(beta))
        a2 = (Decimal(0.5) * alpha * R1 * R1) - (Decimal(0.5) * R1 * R1 * sin(alpha))
        ans = a1 + a2

    return ans

# Driver Code
if __name__ == '__main__':
    k1 = inlt()
    x1 = k1[0]
    y1 = k1[1]
    r1 = k1[2]

    k2 = inlt()
    x2 = k2[0]
    y2 = k2[1]
    r2 = k2[2]

    ans = intersectionArea(x1, y1, r1, x2, y2, r2)
    print(ans)




# This code is contributed by himanshu77
