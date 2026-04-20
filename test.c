#define _VCALC_STRIP_PREFIX_
#include "vcalc.h"
#include <assert.h>

void parsing() {
    printf("Parsing... ");
    fflush(stdout);
    Matrix* poly =       PolyParse("-7.6x^6 + 8.4x^3 + 5.1x^2 - 2x^2 + 55.1x - 5. - 11.");
    Matrix* check = PolyFromVa64(6, -7.6, 0., 0., 8.4, 3.1, 55.1, -16.);
//    printf("\n");
//    PolyPrint(poly);
//    PolyPrint(check);
    assert(!PolyEq(check, poly));    
    free(poly);
    free(check);
    printf("OK\n");
}

void derivation() {
    printf("Derivation... ");
    fflush(stdout);
    Matrix* poly = PolyFromVa64(5, 1., 2., 3., 4., 5., 6.);
    PolyDifferentiate(poly);
    Matrix* check = PolyFromVa64(4, 5., 8., 9., 8., 5.);
    assert(!PolyEq(check, poly));
    free(poly);
    free(check);
    printf("OK\n");
}

void integration() {
    printf("Integration... ");
    fflush(stdout);
    {
	Matrix* poly = PolyFromVa64(5, 1., 0., 3., 4., 5., 6.);
	Matrix* antider = PolyAntiderivative(poly);
	Matrix* check = PolyFromVa64(6, 1./6., 0., 3./4., 4./3., 5./2., 6., 2);
	
	assert(!PolyEq(antider, check));

	free(poly);
	free(antider);
	free(check);
    }
    {
	Matrix* poly = PolyFromVa64(2, -4.3, 2.6, 3.);
	assert(PolyIntegrate(poly, 2, 6) == -3668./15.);
	free(poly);
    }
    
    printf("OK\n");
}

void evaluation() {
    printf("Evaluation... ");
    fflush(stdout);
    Matrix* poly = PolyParse("x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6");
    assert(PolyEvaluate(poly, 2) == 120);
    free(poly);
    printf("OK\n");
}


void multiplication() {
    printf("Multiplication ...");
    fflush(stdout);

    Matrix* a = PolyFromVa64(5, 3.3, 1.5, 6., 3.4, -1.2, 0.2);
    Matrix* b = PolyFromVa64(5, 1.3, 4.5, 2.9, 1., 9.4, 0.9);
    Matrix* ab = PolyMultiply(a, b);

    free(a);
    free(b);
    free(ab);


    printf("OK\n");
}
void matrix_multiplication() {
    printf("Matrix Multiplication... ");
    fflush(stdout);
    Matrix* a = VectorFromVa64(5, 1., 3., 4., 1., 2.);
    Matrix* b = VectorFromVa64(5, 2., 2., 6., 3., 8.);
    Matrix* aT = MatrixTransposed(a);
    Matrix* ab = MatrixMultiply(b, aT);
    Matrix* check = MatrixFromVa64(5, 5,
				   2., 2., 6., 3., 8.,
				   6., 6., 18., 9., 24.,
				   8., 8., 24., 12., 32.,
				   2., 2., 6., 3., 8.,
				   4., 4., 12., 6., 16.);
    assert(!MatrixEq(ab, check));
    
    
    free(a);
    free(b);
    free(ab);
    free(aT);
    free(check);
    printf("OK\n");
}

int main() {
    parsing();
    evaluation();
    derivation();
    integration();
    multiplication();
    matrix_multiplication();
    return 0;
}
