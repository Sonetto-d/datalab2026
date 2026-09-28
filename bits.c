/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
  * bitAnd - x & y using only ~ and |
  * Example: bitAnd(4, 5) = 4
  * Legal ops: ~ |
  * Max ops: 7
  * Difficulty: 1
  */
int bitAnd(int x, int y) {
    /* De Morgan: x & y == ~(~x | ~y) */
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    /* x ^ y == (x | y) & ~(x & y), and x | y == ~(~x & ~y) */
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    /* x >> 31 is 0 for x >= 0 and -1 for x < 0, so the sign bits are
     * exactly the two lowest bits of sx and sy. */
    int sx = x >> 31;
    int sy = y >> 31;

    if (sx ^ sy) {
        return 0; /* one non-negative, the other negative */
    }
    if (sx) {
        return 1; /* both negative */
    }
    if (x) {
        if (y) {
            return 1; /* both positive */
        }
        return 0; /* x > 0, y == 0 */
    }
    if (y) {
        return 0; /* x == 0, y != 0 */
    }
    return 1; /* both zero */
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int r = 0;
    int s;

    /* Standard binary search for floor(log2(v)).  Every step produces its
     * own shift amount s by comparing the remaining value with a bound, so
     * no control flow is needed. */
    s = (v > 0xFFFF) << 4;
    v = v >> s;
    r = r | s;
    s = (v > 0xFF) << 3;
    v = v >> s;
    r = r | s;
    s = (v > 0xF) << 2;
    v = v >> s;
    r = r | s;
    s = (v > 0x3) << 1;
    v = v >> s;
    r = r | s;
    r = r | (v > 1);
    return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift = n << 3;
    int mshift = m << 3;
    int nbyte, mbyte, diff, mask;

    /* Extract both bytes, then XOR the two positions with the difference of
     * the bytes: the bits of the two bytes are exactly the bits that have to
     * be flipped. */
    nbyte = (x >> nshift) & 0xFF;
    mbyte = (x >> mshift) & 0xFF;
    diff = nbyte ^ mbyte;
    mask = (diff << nshift) | (diff << mshift);
    return x ^ mask;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    int i = 32;

    /* Peel one bit off the right of v and push it onto the left of r. */
    while (i) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int low, fixup;

    /* low = mask of the low (32 - n) bits, built with positive shifts only:
     * (n + 31) & 31 equals n - 1 for n >= 1 and 31 for n == 0. */
    low = 0x7FFFFFFF >> ((n + 31) & 31);
    /* For n == 0 all 32 bits must be kept, but low is then 0.  In that case
     * low - 1 is -1 and (low - 1) >> 31 is an all-ones mask; for every
     * n >= 1, low >= 1 so (low - 1) >> 31 is 0. */
    fixup = (low + ~0) >> 31;
    return (x >> n) & (low | fixup);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int cnt = 0;
    int w;

    /* Binary search: cnt is the number of leading ones already proven.
     * The next chunk of c bits sits at offset 32 - cnt - c, i.e. at
     * ~cnt + (33 - c).  Shifting right arithmetically keeps the low bits of
     * the chunk intact, so it can be tested with a mask. */

    /* chunk of 16 bits (offset is the constant 16 while cnt == 0) */
    w = x >> 16;
    cnt = cnt + ((!((w + 1) & 0xFFFF)) << 4);

    /* chunk of 8 bits, offset = 24 - cnt */
    w = x >> (~cnt + 25);
    cnt = cnt + ((!((w + 1) & 0xFF)) << 3);

    /* chunk of 4 bits, offset = 28 - cnt */
    w = x >> (~cnt + 29);
    cnt = cnt + ((!((w + 1) & 0xF)) << 2);

    /* chunk of 2 bits, offset = 30 - cnt */
    w = x >> (~cnt + 31);
    cnt = cnt + ((!((w + 1) & 0x3)) << 1);

    /* Final 2 bits (bits 1 and 0 when the first 30 bits were all ones).
     * (w >> 1) + (w & (w >> 1)) is the number of leading ones of the 2-bit
     * window w, and it is 0 whenever the window contains the first zero. */
    w = (x >> (~cnt + 31)) & 0x3;
    cnt = cnt + ((w >> 1) + (w & (w >> 1)));

    return cnt;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x;
    unsigned sign, mag, frac, rem, half, shift;
    unsigned t;
    int e = 0;

    if (x == 0) {
        return 0;
    }
    sign = ux & 0x80000000;
    if (x < 0) {
        mag = -ux; /* unsigned negation, well defined for 0x80000000 */
    } else {
        mag = ux;
    }

    /* e = floor(log2(mag)): shift mag down until only the leading 1 is left.
     * e starts at 0, so logtwo(1) == 0 is handled without a special case. */
    t = mag;
    while (t >>= 1) {
        e = e + 1;
    }

    if (e > 23) {
        /* Some bits are shifted out, so round to nearest, ties to even. */
        shift = e - 23;
        frac = mag >> shift;
        rem = mag & ((1 << shift) - 1); /* the bits that are dropped */
        half = 1 << (shift - 1);        /* 0.5 ulp */
        if (rem > half) {
            frac = frac + 1;
        } else if (rem == half) {
            if (frac & 1) {
                frac = frac + 1; /* tie: round up only to an even mantissa */
            }
        }
        if (frac >> 24) {
            /* mantissa overflowed, e.g. 0xFFFFFF rounded up to 0x1000000 */
            frac = frac >> 1;
            e = e + 1;
        }
    } else {
        frac = mag << (23 - e); /* exact, no rounding needed */
    }
    frac = frac & 0x7FFFFF; /* drop the implicit leading 1 */
    return sign | ((e + 127) << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned sign = uf & 0x80000000;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) {
        return uf; /* inf and NaN are unchanged (2*inf == inf) */
    }
    if (exp == 0) {
        /* zero or denormal: doubling is a left shift of the fraction */
        if (frac >> 22) {
            /* the fraction becomes normal: exponent field 1, leading 1 dropped */
            return sign | 0x00800000 | ((frac << 1) & 0x7FFFFF);
        }
        return sign | (frac << 1);
    }
    exp = exp + 1;
    if (exp == 0xFF) {
        return sign | 0x7F800000; /* overflow to +-inf */
    }
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned val, shift;

    /* |value| < 1 (including all denormals): truncation gives 0 */
    if (exp < 1023) {
        return 0;
    }
    /* |value| >= 2^31 (including inf and NaN): overflow */
    if (exp > 1054) {
        return 0x80000000;
    }
    /* val holds the (mantissa + implicit 1) bits, aligned so that
     * val >> (1054 - exp) is the truncated magnitude. */
    val = 0x80000000 | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);
    shift = 1054 - exp;
    val = val >> shift;

    if (sign) {
        if (val > 0x80000000) {
            return 0x80000000; /* -(val) does not fit in an int */
        }
        return -val; /* covers -2^31 as well */
    }
    if (val > 0x7FFFFFFF) {
        return 0x80000000;
    }
    return val;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    /* Normal numbers need a biased exponent in [1, 254], i.e. x in [-126, 127] */
    if (x > 127) {
        return 0x7F800000; /* +INF */
    }
    if (x < -126) {
        if (x < -149) {
            return 0; /* smaller than the smallest denormal 2^-149 */
        }
        /* denormal: 2^x == 1 << (x + 149), with x + 149 in [0, 22] */
        return 1 << (x + 149);
    }
    return (x + 127) << 23;
}
