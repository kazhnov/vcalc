#define _VCALC_STRIP_PREFIX_
#include "vcalc.h"
#include <assert.h>

f64 f(f64 x) {
    return x*x;
}

f64 F(f64 x) {
    return (x*x*x)/3.;
}

void parsing() {
    printf("Parsing... ");
    fflush(stdout);
    Matrix* poly =       PolyParse("-7.6x^6 + 8.4x^3 + 5.1x^2 - 2x^2 + 55.1x - 5. - 11.");
    Matrix* check = PolyFromVa64(6, -16., 55.1, 3.1, 8.4, 0.0, 0.0, -7.6);
    assert(!PolyEq(check, poly));    
    free(poly);
    free(check);
    printf("OK\n");
}

void derivation() {
    printf("Derivation... ");
    fflush(stdout);
    Matrix* poly = PolyFromVa64(5, 6., 5., 4., 3., 2., 1.);
    Matrix* der = PolyDerivative(poly);
    Matrix* check = PolyFromVa64(4, 5., 8., 9., 8., 5.);
    assert(!PolyEq(check, der));
    free(poly);
    free(der);
    free(check);
    printf("OK\n");
}


void integration() {
    printf("Integration... ");
    fflush(stdout);
    {
	Matrix* poly = PolyFromVa64(5, 6., 5., 4., 3., 0., 1.);
	Matrix* antider = PolyAntiderivative(poly);
	Matrix* check = PolyFromVa64(6, 0., 6., 5./2., 4./3., 3./4., 0.0, 1./6.);
	
	assert(!PolyEq(antider, check));

	free(poly);
	free(antider);
	free(check);
    }
    {
	Matrix* poly = PolyParse("-4.3x^2 + 2.6x + 3");
	assert(PolyIntegrate(poly, 2, 6) == -3668./15.);
	free(poly);
    }
    {
	f64 exact = F(3) - F(0);
	f64 approximate = FunctionIntegrateTrapezoid(f, 0, 3, 0.01);
	assert(fabs(exact - approximate) < 0.001);

    }
    
    printf("OK\n");
}

void evaluation() {
    printf("Evaluation... ");
    fflush(stdout);

    {
	Matrix* poly = PolyParse("x^5 + 2x^4 + 3x^3 + 4x^2 + 5x + 6");
	assert(PolyEvaluate(poly, 2) == 120);
	free(poly);
    }

    {
	Matrix* results = FunctionEvaluateRange(f, 0, 4, 0.5);
	Matrix* results_check = MatrixFromVa64(2, 9,
					       0.0,   0.0,
					       0.5,  0.25,
					       1.0,   1.0,
					       1.5,  2.25,
					       2.0,   4.0,
					       2.5,  6.25,
					       3.0,   9.0,
					       3.5, 12.25,
					       4.0,  16.0
	    );
	assert(!MatrixEq(results_check, results));
	free(results);
	free(results_check);
    }
    
    printf("OK\n");
}

void poly_multiplication() {
    printf("Polynomial Multiplication ...");
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

void concatenation() {
    printf("Matrix Concatenation... ");
    fflush(stdout);
    Matrix* a = MatrixFromVa64(3, 3,
			       5.5, 1.1, 2.3,
			       5.6, 8.7, 0.3,
			       6.1, 7.6, 1.0);
    Matrix* b = MatrixFromVa64(2, 2,
			       2.2, 2.3,
			       5.6, 7.4);
    Matrix* abr = MatrixRowsCat(a, b);
    Matrix* abr_check = MatrixFromVa64(3, 5,
	5.5000,	1.1000,	2.3000,	
	5.6000,	8.7000,	0.3000,	
	6.1000,	7.6000,	1.0000,	
	2.2000,	2.3000,	0.0000,	
	5.6000,	7.4000,	0.0000
	);
    assert(!MatrixEq(abr, abr_check));

    Matrix* abc = MatrixColumnsCat(a, b);
    Matrix* abc_check = MatrixFromVa64(5, 3,
				       5.5000,	1.1000,	2.3000,	2.2000,	2.3000,	
				       5.6000,	8.7000,	0.3000,	5.6000,	7.4000,	
				       6.1000,	7.6000,	1.0000,	0.0000,	0.0000);
    assert(!MatrixEq(abc, abc_check));
    
    free(a);
    free(b);
    free(abr);
    free(abc);
    free(abr_check);
    free(abc_check);
    printf("OK\n");
}

int main() {
    parsing();
    evaluation();
    derivation();
    integration();
    poly_multiplication();
    matrix_multiplication();
    concatenation();
    return 0;
}
