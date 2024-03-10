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

def dist2(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1

    return dx * dx + dy * dy

def dist(x1, y1, x2, y2):
    return Decimal.sqrt(dist2(x1, y1, x2, y2))

def S(R):
    """
    auto S = [](db R) {
        db result = (db(180) * R) / PI;
        return result;
    };
    """
    result = (Decimal(180) * R) / pi()
    return result

def get_angle(A_x, A_y, B_x, B_y, C_x, C_y):
    """
        //? need angle ABC
        db a2 = dist2(A, B);
        db b2 = dist2(B, C);
        db c2 = dist2(A, C);

        //? c^2 = a^2 + b^2 - 2*a*b*cos(x)
        //? 2*a*b*cos(x) = a^2 + b^2 - c^2
        //? cos(x) = (a^2 + b^2 - c^2) / (2*a*b)

        db result = acos((a2 + b2 - c2) / (db(2)*db(sqrt(a2))*db(sqrt(b2))));
        return result;
    """
    a2 = dist2(A_x, A_y, B_x, B_y)
    b2 = dist2(B_x, B_y, C_x, C_y)
    c2 = dist2(A_x, A_y, C_x, C_y)

    result = acos((a2 + b2 - c2) / (Decimal(2) * Decimal.sqrt(a2) * Decimal.sqrt(b2)))
    return result

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

# Driver Code xd
if __name__ == '__main__':
    node1 = inlt()
    Ax = node1[0]
    Ay = node1[1]

    node2 = inlt()
    Bx = node2[0]
    By = node2[1]

    node3 = inlt()
    Cx = node3[0]
    Cy = node3[1]

    node4 = inlt()
    Dx = node4[0]
    Dy = node4[1]

    # print("================================")
    # print(Ax, Ay)
    # print(Bx, By)
    # print(Cx, Cy)
    # print(Dx, Dy)
    # print("================================")

    angles = []

    angles.append(get_angle(Dx, Dy, Ax, Ay, Bx, By))
    angles.append(get_angle(Ax, Ay, Bx, By, Cx, Cy))
    angles.append(get_angle(Bx, By, Cx, Cy, Dx, Dy))
    angles.append(get_angle(Cx, Cy, Dx, Dy, Ax, Ay))

    S_angles = set()
    S_angles.add(get_angle(Dx, Dy, Ax, Ay, Bx, By))
    S_angles.add(get_angle(Ax, Ay, Bx, By, Cx, Cy))
    S_angles.add(get_angle(Bx, By, Cx, Cy, Dx, Dy))
    S_angles.add(get_angle(Cx, Cy, Dx, Dy, Ax, Ay))

    S_distances = set()
    S_distances.add(dist2(Ax, Ay, Bx, By))
    S_distances.add(dist2(Bx, By, Cx, Cy))
    S_distances.add(dist2(Cx, Cy, Dx, Dy))
    S_distances.add(dist2(Dx, Dy, Ax, Ay))

    # for x in angles:
    #     print(S(x))
    # print("================================")
    # for x in S_angles:
        # print(S(x))
    # print("================================")
    # for x in S_distances:
    #     print(x)
    # print("================================")

    if(len(S_angles) == 1):
        if(len(S_distances) == 1):
            print("square")
        else:
            print("rectangle")
    elif(len(S_angles) == 2 and len(S_distances) == 1):
        print("rhombus")
    else:
        # print("dbg kite")
        ok_kite = False
        for i in range(0, 40):
            i_tmp = i % 4
            j = (i + 2) % 4
            other = []

            for k in range(0, 4):
                if(k != i_tmp and k != j):
                    other.append(angles[k])

            if(angles[i_tmp] == angles[j] and other[0] != other[1]):
                ok_kite = True

        if(ok_kite):
            print("kite")
        else:
            # print("dbg parallelogram")

            ok_parallelogram = False
            for i in range(0, 40):
                xd1 = angles[i % 4]
                xd2 = angles[(i + 1) % 4]
                xd3 = angles[(i + 2) % 4]
                xd4 = angles[(i + 3) % 4]

                if(xd1 == xd3 and xd2 == xd4):
                    assert xd1 != xd2
                    ok_parallelogram = True

            if(ok_parallelogram):
                print("parallelogram")
            else:
                # print("dbg trapezium")

                ok_trapezium = False
                for i in range(0, 40):
                    xd1 = angles[i % 4]
                    xd2 = angles[(i + 1) % 4]

                    if((xd1 + xd2) == pi()):
                        ok_trapezium = True

                if(ok_trapezium):
                    print("trapezium")
                else:
                    print("none")

# This code is contributed by himanshu77
