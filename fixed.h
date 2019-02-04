/*
 *  Created by Steven on 06-Aug-18.
 */

#ifndef CFIXED_FIXED_H
#define CFIXED_FIXED_H

/* Todo: Design better names for macros */

#include <stdio.h>

/* Version Specific features */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#   include <stdint.h>
#elif defined(__STDC__)
#   define inline

/* These may need to be changed for different implementations */
typedef short           int16_t;
typedef unsigned short  uint16_t;
typedef int             int32_t;
typedef unsigned int    uint32_t;
typedef long            int64_t;
typedef unsigned long   uint64_t;

#else
#   error "Unsupported Compiler!"
#endif

/* Select a width for the fixedpt type (16 or 32 supported) */
#if !defined(FIXED_BASE_WIDTH)
#   error "FIXED_BASE_WIDTH not defined!"

#elif FIXED_BASE_WIDTH == 32
typedef int32_t fixedpt;
typedef uint32_t ufixedpt;
typedef int64_t lfixedpt;
typedef uint64_t ulfixedpt;

#elif FIXED_BASE_WIDTH == 16
typedef int16_t fixedpt;
typedef uint16_t ufixedpt;
typedef int32_t lfixedpt;
typedef uint32_t ulfixedpt;

#endif
#undef FIXED_BASE_WIDTH

/* Default width constants */
/* Byte->Bit, div by 2 */
#define FIXED_ONE                       ((fixedpt)1)
#define FIXED_FWIDTH                    (4*sizeof(fixedpt))
#define FIXED_IWIDTH                    (8*sizeof(fixedpt)-FIXED_FWIDTH)
#define FIXED_FMASK                     ((FIXED_ONE << FIXED_FWIDTH) - 1)
#define FIXED_1DMASK                    ((FIXED_ONE << (FIXED_FWIDTH-1)))
#define FIXED_IMASK                     (~FIXED_FMASK)
#define FIXED_I1DMASK                   (FIXED_IMASK | FIXED_1DMASK)

/* Variable width constants */
#define FIXED_FMASKW(w)                 ((FIXED_ONE << (w)) - 1)
#define FIXED_1DMASKW(w)                ((FIXED_ONE << ((w)-1)))
#define FIXED_IMASKW(w)                 (~FIXED_FMASKW(w))
#define FIXED_I1DMASKW(w)               (FIXED_IMASKW(w) | FIXED_1DMASKW(w))

/* Default width initalizers */
#define fixed_fromint(i)                ((fixedpt)(i) << FIXED_FWIDTH)
#define fixed_fromwhole(i, f)           (((fixedpt)(i) << FIXED_FWIDTH) | ((fixedpt)(f)))
#define fixed_fromoffs(i, f, o)         (((fixedpt)(i) << FIXED_FWIDTH) | ((fixedpt)(f) << (FIXED_FWIDTH-(o))))
#define fixed_fromuint(i)               ((ufixedpt)(i) << FIXED_FWIDTH)
#define fixed_fromuwhole(i, f)          (((ufixedpt)(i) << FIXED_FWIDTH) | ((ufixedpt)(f)))
#define fixed_fromuoffs(i, f, o)        (((ufixedpt)(i) << FIXED_FWIDTH) | ((ufixedpt)(f) << (FIXED_FWIDTH-(o))))

#define fixed_fromd(d)                  ((fixedpt)((d) * (1 << FIXED_FWIDTH)))
#define fixed_fromud(d)                 ((ufixedpt)((d) * (1 << FIXED_FWIDTH)))

/* Variable width initalizers */
#define fixed_fromintw(i, w)            ((fixedpt)(i) << (w))
#define fixed_fromwholew(i, f, w)       (((fixedpt)(i) << (w)) | ((fixedpt)(f)))
#define fixed_fromoffsw(i, f, o, w)     (((fixedpt)(i) << (w)) | ((fixedpt)(f) << ((w)-(o))))
#define fixed_fromuintw(i, w)           ((ufixedpt)(i) << (w))
#define fixed_fromuwholew(i, f, w)      (((ufixedpt)(i) << (w)) | ((ufixedpt)(f)))
#define fixed_fromuoffsw(i, f, o, w)    (((ufixedpt)(i) << (w)) | ((ufixedpt)(f) << ((w)-(o))))

#define fixed_fromdw(d, w)              ((fixedpt)((d) * (1 << (w))))
#define fixed_fromudw(d, w)             ((ufixedpt)((d) * (1 << (w))))

/* Special initializers */
#define fixed_fromlintw(l, w)           ((lfixedpt)(l) << (w))
#define fixed_fromulintw(l, w)          ((ulfixedpt)(l) << (w))

/* Default width accessors */
#define fixed_ipart(f)                  ((f) >> FIXED_FWIDTH)
#define fixed_fpart(f)                  ((ufixedpt)((f) & FIXED_FMASK))

/* Variable width accessors */
#define fixed_ipartw(f, w)              ((f) >> (w))
#define fixed_fpartw(f, w)              ((ufixedpt)((f) & ((1 << (w))-1)))

/* Default width limits */
#define FIXED_MAXVAL                    ((fixedpt)(~(1 << (FIXED_FWIDTH+FIXED_IWIDTH-1))))
#define FIXED_MINVAL                    ((fixedpt)(1 << (FIXED_FWIDTH+FIXED_IWIDTH-1)))
#define FIXED_MAXINT                    (fixed_ipart(FIXED_MAXVAL))
#define FIXED_MININT                    (fixed_ipart(FIXED_MINVAL))
#define FIXED_MAXFRAC                   (fixed_fpart(FIXED_MAXVAL))
#define FIXED_MINFRAC                   (fixed_fpart(FIXED_MINVAL))

#define FIXED_MAXUVAL                   (~(ufixedpt)0)
#define FIXED_MINUVAL                   ((ufixedpt)0)
#define FIXED_MAXUINT                   (fixed_ipart(FIXED_MAXUVAL))
#define FIXED_MINUINT                   (fixed_ipart(FIXED_MINUVAL))
#define FIXED_MAXUFRAC                  (fixed_fpart(FIXED_MAXUVAL))
#define FIXED_MINUFRAC                  (fixed_fpart(FIXED_MINUVAL))

/* Variable width limits */
#define FIXED_MAXVALW(w)                FIXED_MAXVAL
#define FIXED_MINVALW(w)                FIXED_MINVAL
#define FIXED_MAXINTW(w)                (fixed_ipartw(FIXED_MAXVAL, w))
#define FIXED_MININTW(w)                (fixed_ipartw(FIXED_MINVAL, w))
#define FIXED_MAXFRACW(w)               (fixed_fpartw(FIXED_MAXVAL, w))
#define FIXED_MINFRACW(w)               (fixed_fpartw(FIXED_MINVAL, w))

#define FIXED_MAXUVALW(w)                FIXED_MAXUVAL
#define FIXED_MINUVALW(w)                FIXED_MINUVAL
#define FIXED_MAXUINTW(w)                (fixed_ipartw(FIXED_MAXUVAL, w))
#define FIXED_MINUINTW(w)                (fixed_ipartw(FIXED_MINUVAL, w))
#define FIXED_MAXUFRACW(w)               (fixed_fpartw(FIXED_MAXUVAL, w))
#define FIXED_MINUFRACW(w)               (fixed_fpartw(FIXED_MINUVAL, w))

/* Universal operations */
#define fixed_neg(f)                    (-(f))
#define fixed_add(f1, f2)               ((f1)+(f2))
#define fixed_sub(f1, f2)               ((f1)-(f2))
#define fixed_abs(f)                    ((f) > 0 ? (f) : (-f))
#define fixed_max(f1, f2)               ((f1) > (f2) ? (f1) : (f2))
#define fixed_min(f1, f2)               ((f1) < (f2) ? (f1) : (f2))

/* Default width operations */
#define fixed_floor(f)                  ((f) & FIXED_IMASK)
#define fixed_ceil(f)                   ((((f) - 1) & FIXED_IMASK) + fixed_fromuint(1))
#define fixed_round(f)                  (((f) & FIXED_I1DMASK) + ((f) & FIXED_1DMASK))

/* Variable width operations */
#define fixed_floorw(f, w)              ((f) & FIXED_IMASKW(w))
#define fixed_ceilw(f, w)               ((((f) - 1) & FIXED_IMASKW(w)) + fixed_fromuintw(1, w))
#define fixed_roundw(f, w)              (((f) & FIXED_I1DMASKW(w)) + ((f) & FIXED_1DMASKW(w)))

#define fixed_convw(f, wold, wnew)      ((wnew) > (wold) ? ((f) << ((wnew)-(wold))) : ((f) >> ((wold)-(wnew))))

/* lfixedpt default width operators */
#define fixed_lmul(f1, f2)              (((lfixedpt)f1 * (lfixedpt)f2) >> FIXED_FWIDTH)
#define fixed_ldiv(f1, f2)              (((lfixedpt)(f1) << FIXED_FWIDTH) / (lfixedpt)f2)
#define fixed_lumul(f1, f2)             (((ulfixedpt)f1 * (ulfixedpt)f2) >> FIXED_FWIDTH)
#define fixed_ludiv(f1, f2)             (((ulfixedpt)(f1) << FIXED_FWIDTH) / (ulfixedpt)f2)

/* lfixedpt variable width operators */
#define fixed_lmulw(f1, f2, w)          (((lfixedpt)f1 * (lfixedpt)f2) >> (w))
#define fixed_ldivw(f1, f2, w)          (((lfixedpt)(f1) << (w)) / (lfixedpt)f2)
#define fixed_lumulw(f1, f2, w)         (((ulfixedpt)f1 * (ulfixedpt)f2) >> (w))
#define fixed_ludivw(f1, f2, w)         (((ulfixedpt)(f1) << (w)) / (ulfixedpt)f2)

/* Default width function operators */
static inline fixedpt fixed_mul(fixedpt f1, fixedpt f2) {
    return ((lfixedpt)(f1) * (lfixedpt)(f2)) >> FIXED_FWIDTH;
}

static inline fixedpt fixed_div(fixedpt f1, fixedpt f2) {
    return ((lfixedpt)(f1) << FIXED_FWIDTH) / (lfixedpt)(f2);
}

static inline ufixedpt fixed_umul(ufixedpt f1, ufixedpt f2) {
    return ((ulfixedpt)(f1) * (ulfixedpt)(f2)) >> FIXED_FWIDTH;
}

static inline ufixedpt fixed_udiv(ufixedpt f1, ufixedpt f2) {
    return ((ulfixedpt)(f1) << FIXED_FWIDTH) / (ulfixedpt)(f2);
}

/* Variable width function operators */
static inline fixedpt fixed_mulw(fixedpt f1, fixedpt f2, unsigned w) {
    return ((lfixedpt)(f1) * (lfixedpt)(f2)) >> w;
}

static inline fixedpt fixed_divw(fixedpt f1, fixedpt f2, unsigned w) {
    return ((lfixedpt)(f1) << w) / (lfixedpt)(f2);
}

static inline ufixedpt fixed_umulw(fixedpt f1, fixedpt f2, unsigned w) {
    return ((ulfixedpt)(f1) * (ulfixedpt)(f2)) >> w;
}

static inline ufixedpt fixed_udivw(ufixedpt f1, ufixedpt f2, unsigned w) {
    return ((ulfixedpt)(f1) << w) / (ulfixedpt)(f2);
}

static fixedpt fixed_ipow(fixedpt f, int b) {
    lfixedpt lfa = f;
    int recipflag = 0;

    if(b == 0) return fixed_fromint(1);
    if(b < 0) {
        recipflag = 1;
        b = -b;
    }

    while(b-1) {
        lfa = fixed_lmul(lfa, lfa);
        --b;
    }

    if(recipflag) lfa = fixed_ldiv(fixed_fromint(1), lfa);
    return lfa;
}

/* Trigonometry operators */
static fixedpt fixed_sin(fixedpt f) {
    lfixedpt accum = 0;

    accum += f;
    accum -= fixed_ldiv(fixed_ipow(f, 3), fixed_fromint(6));
    accum += fixed_ldiv(fixed_ipow(f, 5), fixed_fromint(120));
    accum -= fixed_ldiv(fixed_ipow(f, 7), fixed_fromint(5040));

    return accum;
}

/* String operators */
/* Longest string: -32767 + 1 / 65535, 23 chars. */
static void fixed_str(fixedpt f, char *str) {
    fixedpt ipart = fixed_ipart(f);
    f = fixed_fpart(f);
    if(ipart < 0 && f) {
        *str++ = '-';
        ipart = -(ipart + 1);
    }

    str += sprintf(str, "%d", ipart);  /* Take str to end of string */
    if(!f) return;

    *str++ = '.';
    do {
        f = fixed_mul(f, fixed_fromint(10));
        ipart = fixed_ipart(f);

        *str = (char)(ipart + '0');
        ++str;
        f = fixed_fpart(f);
    } while(f);

    *str = '\0';
}

static void fixed_fstr(fixedpt f, char *str) {
    fixedpt ipart = fixed_ipart(f);
    ufixedpt fpart = fixed_fpart(f);
    if(ipart < 0 && f) {
        *str++ = '-';
        ipart = -(ipart + 1);
    }

    sprintf(str, "%d + %u / %lu", ipart, fpart, (1UL << (unsigned long)(FIXED_FWIDTH)));
}

/* Longest string: 65535 + 1 / 65535, 22 chars. */
static void fixed_ustr(ufixedpt f, char *str) {
    ufixedpt ipart = fixed_ipart(f);
    f = fixed_fpart(f);

    str += sprintf(str, "%u", ipart);  /* Take str to end of string */
    if(!f) return;

    *str++ = '.';
    do {
        f = fixed_umul(f, fixed_fromuint(10));
        ipart = fixed_ipart(f);

        *str = (char)(ipart + '0');
        ++str;
        f = fixed_fpart(f);
    } while(f);

    *str = '\0';
}

static void fixed_ufstr(ufixedpt f, char *str) {
    ufixedpt ipart = fixed_ipart(f);
    ufixedpt fpart = fixed_fpart(f);

    sprintf(str, "%u + %u / %lu", ipart, fpart, (1UL << (unsigned long)(FIXED_FWIDTH)));
}

/* Known bugs: At w<=31 ulfixedpt overflows */
static void fixed_strw(fixedpt fi, unsigned w, char *str) {
    fixedpt ipart = fixed_ipartw(fi, w);
    ulfixedpt f = fixed_fpartw(fi, w);          // ulfixedpt so widths above 28 print correctly
    if(ipart < 0 && f) {
        *str++ = '-';
        ipart = -(ipart + 1);
    }

    str += sprintf(str, "%d", ipart);  /* Take str to end of string */
    if(!f) return;

    *str++ = '.';
    do {
        f = fixed_lumulw(f, fixed_fromulintw(10, w), w);
        ipart = fixed_ipartw(f, w);

        *str = (char)(ipart + '0');
        ++str;
        f = fixed_fpartw(f, w);
    } while(f);

    *str = '\0';
}

/* Known bugs: At w<=31 ulfixedpt overflows */
static void fixed_ustrw(ufixedpt fi, unsigned w, char *str) {
    ufixedpt ipart = fixed_ipartw(fi, w);
    ulfixedpt f = fixed_fpartw(fi, w);

    str += sprintf(str, "%u", ipart);  /* Take str to end of string */
    if(!f) return;

    *str++ = '.';
    do {
        f = fixed_lumulw(f, fixed_fromulintw(10, w), w);
        ipart = fixed_ipartw(f, w);

        *str = (char)(ipart + '0');
        ++str;
        f = fixed_fpartw(f, w);
    } while(f);

    *str = '\0';
}

static void fixed_xstr(ufixedpt f, char *str) {
    sprintf(str, "0x%08x", f);
}

#ifdef FIXED_DEBUG_STRINGS
static char FIXED_DEBUG_STRING_BUF[32];
static const char *fixed_debugstr(fixedpt f) {
    fixed_str(f, FIXED_DEBUG_STRING_BUF);
    return str;
}

static const char *fixed_debugstrw(fixedpt f, unsigned w) {
    fixed_strw(f, w, FIXED_DEBUG_STRING_BUF);
    return str;
}
#endif


#endif /* CFIXED_FIXED_H */
