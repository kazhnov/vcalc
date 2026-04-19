#define _VCALC_STRIP_PREFIX_
#include "include/vmath/vmath.h"
#include "vcalc.h"
#include <stdarg.h>
#include <stddef.h>

struct VCALC_Poly {
    u32 degree;
    f64 values[];
};

struct VCALC_Matrix {
    u32 size[2];
    f64 values[];
};

#define EPSILON 1e-12

b8 iVCALC_DoubleEq(f64 first, f64 second) {
    return fabs(first - second) < EPSILON;
}

Poly* iVCALC_PolyNew(u32 degree) {
    Poly* poly = calloc(offsetof(Poly, values) + sizeof(f64) * (degree + 1), 1);
    poly->degree = degree;
    return poly;
}

VCALC_Poly* VCALC_PolyFromVa64(u32 degree, ...) {
    VCALC_Poly* poly = iVCALC_PolyNew(degree);
    va_list values;
    va_start(values, degree);
    for (u32 i = 0; i <= degree; i++) {
	poly->values[i] = va_arg(values, f64);
    }
    va_end(values);
    return poly;    
}

VCALC_Poly* VCALC_PolyFromVector64(u32 degree, f64 vector[degree + 1]) {
    VCALC_Poly* poly = iVCALC_PolyNew(degree);
    for (u32 i = 0; i <= degree; i++) {
	poly->values[i] = vector[i];
    }
    return poly;
}

VCALC_Poly* VCALC_PolyDup(VCALC_Poly* poly) {
    return PolyFromVector64(poly->degree, poly->values);
}

VCALC_Poly* VCALC_PolyDerivative(VCALC_Poly* poly) {
    VCALC_Poly *der;
    if (poly->degree > 0) {
	der = iVCALC_PolyNew(poly->degree - 1);
    } else {
	der = iVCALC_PolyNew(0);
    }

    for (u32 i = 0; i <= poly->degree - 1; i++) {
	u32 power = poly->degree - i;
	der->values[i] = poly->values[i]*power;
    }

    return der;
}

u32 VCALC_PolyCopy(Poly *to, Poly* from) {
    if (to->degree < from->degree) return -1;
    for (u32 i = 0; i <= from->degree; i++) {
	to->values[i] = from->values[i];
    }
    to->degree = from->degree;
    return 0;
}

void VCALC_PolyDifferentiate(Poly *poly) {
    Poly* temp = PolyDerivative(poly);
    PolyCopy(poly, temp);
    free(temp);
}

void VCALC_PolyPrint(Poly* poly) {
    for (u32 i = 0; i < poly->degree; i++) {
	if (poly->values[i] == 0) continue;
	f64 absval = fabs(poly->values[i]);
	b8 minus = poly->values[i] < 0;
	if (i != 0) {
	    printf(" %c ", minus ? '-' : '+');
	}

	if (i == poly->degree - 1) {
	    printf("%.2lf*x", poly->values[i]);
	} else {
	    printf("%.2lf*x^%d", poly->values[i], poly->degree - i);
	}
    }

    if (poly->degree == 0) {
	printf("%.2lf", poly->values[0]);
    } else if (poly->degree > 0 && poly->values[poly->degree] != 0) {
	f64 absval = fabs(poly->values[poly->degree]);
	b8 minus = poly->values[poly->degree] < 0;
	printf(" %c ", minus ? '-' : '+');
	printf("%.2lf", fabs(poly->values[poly->degree]));
    }
    printf("\n");
}

b8 VCALC_PolyEq(Poly* first, Poly* second) {
    if (first->degree != second->degree) {
	printf("Not the same degrees\n");
	return 1;      
    }
    for (u32 i = 0; i <= first->degree; i++) {
	if (!iVCALC_DoubleEq(first->values[i], second->values[i])) {
	    printf("Not the same at power %u.\n%.30lf\n%.30lf\n", first->degree - i, first->values[i], second->values[i]);
	    return 1;
	}
    }
    return 0;
}

f64 VCALC_PolyEvaluate(Poly* poly, f64 x) {
    f64 sum = 0;
    for (u32 i = 0; i < poly->degree; i++) {
	u32 power = poly->degree - i;
	sum += poly->values[i]*pow(x, power);
    }
    sum += poly->values[poly->degree];
    return sum;
}

Poly* VCALC_PolyAntiderivative(Poly* poly) {
    VCALC_Poly *antider = iVCALC_PolyNew(poly->degree + 1);

    for (u32 i = 0; i <= poly->degree; i++) {
	u32 power = antider->degree - i;
	antider->values[i] = poly->values[i]/power;
    }

    return antider;
}

f64 VCALC_PolyIntegrate(Poly* poly, f64 from, f64 to) {
    Poly* antider = PolyAntiderivative(poly);
    f64 end = PolyEvaluate(antider, to);
    f64 start = PolyEvaluate(antider, from);
    free(antider);
    return end - start;
}

b8 iVCALC_WhitespaceSkip(char* str, u32* cursor) {
    printf("symbol: %c\n", str[*cursor]);
    while (str[*cursor] != 0 && str[*cursor] == ' ') cursor++;
    if (str[*cursor] == 0) return 1;
    return 0;
}

Poly* VCALC_PolyParse(char* str) {
    u32 cursor = 0;
    u32 degree = 0;
    for (;str[cursor] != 0; cursor++) {
	if (str[cursor] != 'x') continue;
	if (str[cursor+1] != '^') {
	    degree = degree > 1 ? degree : 1;
	    continue;
	}
	cursor++;
	u32 read = 0;
	u32 new_degree = 0;
	if (sscanf(str + cursor + 1, "%u%n", &new_degree, &read) != 1) continue;
	if (str[cursor + 1 + read] == 0) break;
	cursor++;
//	printf("\nnew degree = %d\n", degree);
	if (new_degree > degree) degree = new_degree;
	cursor += read;
    }
    Poly* poly = iVCALC_PolyNew(degree);
    cursor = 0;
    for(;; cursor++) {
	if (str[cursor] == 0) break;
//	printf("symbol: %c\n", str[cursor]);
	u32 read;
	f64 value = 0;
	b8 is_negative = 0;
	b8 has_value = 0;
	u32 power = 0;
//	if(iVCALC_WhitespaceSkip(str, &cursor)) break;
	if (str[cursor] == '+') {
	    cursor++;
	}
	else if (str[cursor] == '-') {
	    is_negative = 1;
	    cursor++;
	}
	
//	if (iVCALC_WhitespaceSkip(str, &cursor)) break;
	if (sscanf(str + cursor, "%lf%n", &value, &read) == 1) {
	    cursor += read;
	    has_value = 1;
	    if (is_negative) value *= -1;
//	    printf("value: %d %lf\n", is_negative, value);
	}

//	if (iVCALC_WhitespaceSkip(str, &cursor)) break;
	if (str[cursor] == 'x') {
	    if (!has_value) {
		has_value = 1;
		value = 1.;
	    }
	    power = 1;
	    cursor++;
	    if (str[cursor] == 0) break;
	    if (str[cursor] == '^') {
		if (str[cursor] == 0) break;
		sscanf(str + cursor + 1, "%u%n", &power, &read);
		cursor += read;

	    } else {
		if (!has_value) continue;
		cursor--;
	    }
	} else {
	    if (!has_value) continue;
	    cursor--;
	}
//	printf("%lfx^%u\n", value, power);	
	poly->values[poly->degree - power] += value;
	if (str[cursor] == 0) break;
    }
    return poly;
}
