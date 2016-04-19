#
# tests for C99 equivalent Arithmetic (if compiled into mawk)
#
# These tests will FAIL if -DSTDC_MATHERR is defined
#
BEGIN {
  Arr["PI"] = 3.1415926535897932384626433832795
  Arr["NZero"] = -0.0
  Arr["Zero"] = 0.0
  Arr["IntVal"] = 42
  Arr["DblVal"] = 42.42
  Arr["NaN"] = log(-3)
  Arr["Inf"] = tgamma(12345678)
  Arr["NInf"] = log2(0)

  for (x in Arr) {
    print "\n###############",Arr[x],"#####################"
    print x, "abs            = ", abs(Arr[x])
    print x, "sin            = ", sin(Arr[x])
    print x, "cos            = ", cos(Arr[x])
    print x, "tan            = ", tan(Arr[x])
    print x, "asin           = ", asin(Arr[x])
    print x, "acos           = ", acos(Arr[x])
    print x, "atan           = ", atan(Arr[x])
    print x, "sinh           = ", sinh(Arr[x])
    print x, "cosh           = ", cosh(Arr[x])
    print x, "tanh           = ", tanh(Arr[x])
    print x, "asinh          = ", asinh(Arr[x])
    print x, "acosh          = ", acosh(Arr[x])
    print x, "atanh          = ", atanh(Arr[x])
    print x, "hypot(x,0.1)   = ", hypot(Arr[x],0.1)
    print x, "log            = ", log(Arr[x])
    print x, "log10          = ", log10(Arr[x])
    print x, "log2           = ", log2(Arr[x])
    print x, "log1p          = ", log1p(Arr[x])
    print x, "logb           = ", logb(Arr[x])
    print x, "ilogb          = ", ilogb(Arr[x])
    print x, "exp            = ", exp(Arr[x])
    print x, "exp2           = ", exp2(Arr[x])
    print x, "expm1          = ", expm1(Arr[x])
    print x, "ldexp(x,2)     = ", ldexp(Arr[x],2)
    print x, "pow(x,10)      = ", pow(Arr[x],10)
    print x, "cbrt           = ", cbrt(Arr[x])

    print x, "mod(x,2)       = ", mod(Arr[x],2)
    print x, "int            = ", int(Arr[x])
    print x, "ceil           = ", ceil(Arr[x])
    print x, "floor          = ", floor(Arr[x])
    print x, "trunc          = ", trunc(Arr[x])
    print x, "round          = ", round(Arr[x])
    print x, "min(x,2)       = ", min(Arr[x],2)
    print x, "max(x,2)       = ", max(Arr[x],2)
    print x, "erf            = ", erf(Arr[x])
    print x, "erfc           = ", erfc(Arr[x])
    print x, "lgamma         = ", lgamma(Arr[x])
    print x, "tgamma         = ", tgamma(Arr[x])
    print x, "bessel_j0      = ", bessel_j0(Arr[x])
    print x, "bessel_j1      = ", bessel_j1(Arr[x])
    print x, "bessel_jn(3,x) = ", bessel_jn(3,Arr[x])
    print x, "bessel_y0      = ", bessel_y0(Arr[x])
    print x, "bessel_y1      = ", bessel_y1(Arr[x])
    print x, "bessel_yn(3,x) = ", bessel_yn(3,Arr[x])

    print x, "compl          = ", compl(Arr[x])
    print x, "lshift(x,2)    = ", lshift(Arr[x],2)
    print x, "rshift(x,2)    = ", rshift(Arr[x],2)
    print x, "xor(x,0xff)    = ", xor(Arr[x],0xff)
    print x, "or(x,0xff)     = ", or(Arr[x],0xff)
    print x, "and(x,0xff)    = ", and(Arr[x],0xff)
  }
  print "##########################################"
}
