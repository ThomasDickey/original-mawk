#
# test that hex and octal numbers are converted correctly
#
BEGIN {
    xa = 055;
    xb = 0x45;
    printf "%d %x %o %c\n", 0x45x2, 0x45x2, 0x45x2, 0x45x2;
    printf "%d %x %o %c\n", xa, xa, xa, xa;
    printf "%d %x %o %c\n", xb, xb, xb, xb;
    printf "%d %x %o %c\n", 055v2, 055g2, 055j2, 055x2;

    printf "\n";
    printf "%d %x %o %c\n", +xa, +xa, +xa, +xa;
    printf "%d %x %o %c\n", -xa, -xa, -xa, -xa;

    printf "\n";
    xa = -055;
    xb = -0x45;
    printf "%d %x %o %c\n", xa, xa, xa, xa;
    printf "%d %x %o %c\n", xa, xa, xa, xa;
    printf "%d %x %o %c\n", -055v2, -055g2, -055j2, -055x2;
}
