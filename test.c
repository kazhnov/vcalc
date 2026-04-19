#define _VCALC_STRIP_PREFIX_
#include "vcalc.h"
#include <assert.h>

void derivation() {
    printf("Derivation... ");
    fflush(stdout);
    Poly* poly = PolyFromVa64(5, 1., 2., 3., 4., 5., 6.);
    PolyDifferentiate(poly);
    Poly* check = PolyFromVa64(4, 5., 8., 9., 8., 5.);
    assert(!PolyEq(check, poly));
    free(poly);
    free(check);
    printf("OK\n");
}

void integration() {
    printf("Integration... ");
    fflush(stdout);
    {
	Poly* poly = PolyFromVa64(5, 1., 0., 3., 4., 5., 6.);
	Poly* antider = PolyAntiderivative(poly);
	Poly* check = PolyFromVa64(6, 1./6., 0., 3./4., 4./3., 5./2., 6., 2);
	
	assert(!PolyEq(antider, check));

	free(poly);
	free(antider);
	free(check);
    }
    {
	Poly* poly = PolyFromVa64(2, -4.3, 2.6, 3.);
	assert(PolyIntegrate(poly, 2, 6) == -3668./15.);
	free(poly);
    }
    
    printf("OK\n");
}

void evaluation() {
    printf("Evaluation... ");
    fflush(stdout);
    Poly* poly = PolyParse("x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6");
    assert(PolyEvaluate(poly, 2) == 120);
    free(poly);
    printf("OK\n");
}

void parsing() {
    printf("Parsing... ");
    fflush(stdout);
    Poly* poly =       PolyParse("-7.6x^6 + 8.4x^3 + 5.1x^2 - 2x^2 + 55.1x - 5. - 11.");
    Poly* check = PolyFromVa64(6, -7.6, 0., 0., 8.4, 3.1, 55.1, -16.);
//    PolyPrint(poly);
//    PolyPrint(check);
    assert(!PolyEq(check, poly));    
    free(poly);
    free(check);
    printf("OK\n");
}

int main() {
    parsing();
    evaluation();
    derivation();
    integration();
    return 0;
}
