#
# tests of bit-wise Arithmetic
#
BEGIN {
  x=0x11
  y=0x03
  printf "0x%X, 0x%X, 0x%X\n", and(x,y), or(x,y), xor(x,y)
  printf "0x%X, 0x%X\n", compl(x), compl(y)
  printf "0x%X, 0x%X, 0x%X\n", lshift(x,4), rshift(x,1), rshift(lshift(x,5),1)
}
