## fixedpt
Fixed Point Implementation for C. Fixedpts can be created at 16, or 32 bits wide, and radix point can be set at different widths.

## Method Descriptions
Note references to fixedpt apply to ufixedpt, and likewise for lfixedpt (unless otherwise stated).
Square brackets signify an optional name that changes macro effects.

# Default width constants 

FIXED\_ONE: The literal 1 casted to fixedpt for macro definitions.

FIXED\_FWIDTH: Amount of bits for the FPart of a (u)fixedpt.

FIXED\_IWIDTH: Amount of bits for the IPart of a (u)fixedpt.

FIXED\_FMASK: Mask for the FPart of a (u)fixedpt.

FIXED\_IMASK: Mask for the IPart of a (u)fixedpt.

FIXED\_1DMASK: Mask for the first fraction of a (u)fixedpt.

FIXED\_I1DMASK: Mask for the IPart and first fraction of a (u)fixedpt.

# Default width initializers

Specifying "u" returns ufixedpt rather than fixedpt.

fixed\_from\[u\]int(i): Casts an integer to a (u)fixedpt with default width.
    E.g. i = 1 -> 1.0

fixed\_from\[u\]whole(i, f): Casts an integer and scaled fractional part to a (u)fixedpt with default width.
    E.g. i = 1, f = UINT16_MAX -> 1.5

fixed\_from\[u\]offs(i, f, o): Casts an integer and fractional part shifted by o to a (u)fixedpt with default width.
    E.g. i = 1, f = 1, o = sizeof(fixedpt) - 1 -> 1.5
    
fixed\_from\[u\]d(d): Casts a floating point to a (u)fixedpt.
    E.g. d = 3.14159 -> 3.1415863... (205887 raw 32-bit fixedpt)
    
# Default width accessors

fixed\_ipart(f): Returns the IPart of (u)fixedpt f.

fixed\_fpart(f): Returns the FPart of (u)fixedpt f.
    
# Default width limits

FIXED\_MAX\[U\]VAL: Maximum value of a (u)fixedpt.

FIXED\_MIN\[U\]VAL: Minimum value of a (u)fixedpt.

FIXED\_MAX\[U\]INT: Maximum value of the IPart of a (u)fixedpt.

FIXED\_MIN\[U\]INT: Minimum value of the IPart of a (u)fixedpt.

FIXED\_MAX\[U\]FRAC: Maximum value of the FPart of a (u)fixedpt.

FIXED\_MIN\[U\]FRAC: Minimum value of the FPart of a (u)fixedpt.

# Operations

fixed\_neg(f): Calculates -f1. (Macro for formality, can simply use "-" operator)

fixed\_add(f1, f2): Calculates f1 + f2. (Macro for formality, can simply use "+" operator)

fixed\_sub(f1, f2): Calculates f1 - f2. (Macro for formality, can simply use "-" operator)

fixed\_abs(f): Calculates the absolute value of f.

fixed\_max(f1, f2): Returns the maximum value from f1, f2. (Parameters used twice, do not have side effects)

fixed\_min(f1, f2): Returns the minimum value from f1, f2. (Parameters used twice, do not have side effects)

fixed\_floor(f): Calculates the floor of f at the default width.

fixed\_ceil(f): Calculates the ceil of f at the default width.

fixed\_round(f): Calculates the rounded value of f at the default width. (FPart < 0.5 -> floor, FPart >= 0.5 -> Ceil) (Parameters used twice, do not have side effects)

fixed\_\[l\]\[u\]mul(f1, f2): Calculates f1 * f2. Macro inlined version called fixed\_lmul. (If multiplying by integer, can simply use "*" operator)

fixed\_\[l\]\[u\]div(f1, f2): Calculates f1 / f2. Macro inlined version called fixed\_ldiv. (If divisor is integer, can simply use "/" operator)

fixed\_ipow(f, b): Calculates f^b. b can be of any sign. Only operates on fixedpt.

fixed\_sin(f): Calculates sin(f) from the first 4 terms of the Taylor series. Only operates on fixedpt.

# String Conversions

fixed\_\[u\]str(f, str): Converts (u)fixedpt f to a string stored in buffer str. Has format "+IIIII.FFFFF". Maximum length 23 bytes (22 for ufixedpt).

fixed\_ufstr(f, str): Converts ufixedpt f to a string stored in buffer str. Has format "+IIIII + FFFFF / WWWWW". Maximum length 22 bytes.

fixed\_xstr(f, str): Converts ufixedpt f to a hex string stored in buffer str. Has format "0xXXXXXXXX". Maximum length 11 bytes.

fixed\_debugstr(f): Converts fixedpt using fixed\_str using a static buffer. Macro "FIXED_DEBUG_STRINGS" must be enabled.

## Variable width fixedpts

The default width of fixedpts can be changed by specifying a new radix point. These use the fixed\_???w functions. These fixedpts can also use the "+", "-" operators as well as abs, max, min. All functions assume a width of w.

# Variable width constants

FIXED\_FMASKW(w): Mask for the FPart of a (u)fixedpt.

FIXED\_IMASKW(w): Mask for the IPart of a (u)fixedpt.

FIXED\_1DMASKW(w): Mask for the first fraction of a (u)fixedpt.

FIXED\_I1DMASKW(w): Mask for the IPart and first fraction of a (u)fixedpt.

# Variable width initializers

Same as the default width initializers except macro postpended with a "w" and width supplied as last argument. (E.g. fixed\_fromintw(1, 8)).

# Variable width accessors

Same as the default width accessors except macro postpended as above.

# Variable width limits

Same as the default width limits except macro postpended as above.

# Variable width operations

fixed\_floorw(f, w): Calculates the floor of a f at the radix point specified by w **or** calculates the floor of any fixedpt at an offset.
    E.g. Default width fixedpt = 1.75, width = FIXED_FWIDTH - 1 -> 1.5
    
fixed\_ceilw(f, w): Calculates the ceil of a f at the radix point specified by w **or** calculates the ceil of any fixedpt at an offset.
    E.g. Default width fixedpt = 1.75, width = FIXED_FWIDTH - 1 -> 2.0
    
fixed\_roundw(f, w): Calculates the rounded value of f at the radix point specified by w **or** calculates the rounded value of any fixed pt at and offset. (Parameters used twice, do not have side effects)
    E.g. Default width fixedpt = 1.75, width = FIXED_FWIDTH - 1 -> 2.0

fixed\_convw(f, wold, wnew): Converts a fixedpt number of width wold to wnew. (Parameters used twice, do not have side effects)

fixed\_\[l\]\[u\]mulw(f1, f2, w): Defined as above.
fixed\_\[l\]\[u\]divw(f1, f2, w): Defined as above.