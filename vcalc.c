#define _VCALC_STRIP_PREFIX_
#include "include/vmath/vmath.h"
#include "vcalc.h"
#include <stdarg.h>
#include <stddef.h>

struct VCALC_Matrix {
    u32 size[2];
    f64 values[];
};

#define EPSILON 1e-12

b8 iVCALC_DoubleEq(f64 first, f64 second) {
    return fabs(first - second) < EPSILON;
}

Matrix* iVCALC_MatrixNew(u32 x, u32 y) {
    Matrix* matrix = calloc(offsetof(Matrix, values) + sizeof(f64)*x*y, 1);
    matrix->size[0] = x;
    matrix->size[1] = y;
    return matrix;
}

VCALC_Matrix* VCALC_MatrixFromArray(u32 x, u32 y, f64 array[x*y]) {
    Matrix* matrix = MatrixZeros(x, y);
    for (u32 i = 0; i < x*y; i++) {
	matrix->values[i] = array[i];
    }
    return matrix;
}

VCALC_Matrix* VCALC_MatrixZeros(u32 x, u32 y) {
    return iVCALC_MatrixNew(x, y);
}

VCALC_Matrix* VCALC_MatrixOnes(u32 x, u32 y) {
    Matrix* matrix = MatrixZeros(x, y);

    for (u32 j = 0; j < matrix->size[1]; j++) {
	for (u32 i = 0; i < matrix->size[0]; i++) {
	    MatrixSet(matrix, i, j, 1);
	}
    }
    return matrix;
}


void VCALC_MatrixMove(Matrix* to, Matrix* from) {
    if (MatrixCopyCheck(to, from)) return;
    free(from);
}

void VCALC_MatrixSet(Matrix* m, u32 x, u32 y, f64 value) {
    if (m->size[0] <= x || m->size[1] <= y) return;
    m->values[y*m->size[0] + x] = value;
}

f64 VCALC_MatrixGet(Matrix* m, u32 x, u32 y) {
    if (m->size[0] <= x || m->size[1] <= y) return 0;
    return m->values[y*m->size[0]+x];
}

Matrix* iVCALC_MatrixFromVaList(u32 x, u32 y, va_list values) {
    Matrix* matrix = MatrixZeros(x, y);
    for (u32 j = 0; j < y; j++) {
	for (u32 i = 0; i < x; i++) {
	    MatrixSet(matrix, i, j, va_arg(values, f64));
	}
    }
    return matrix;
}

Matrix* VCALC_MatrixFromVa64(u32 x, u32 y, ...) {
    va_list values;
    va_start(values, y);
    Matrix* matrix = iVCALC_MatrixFromVaList(x, y, values);
    va_end(values);
    return matrix;
}


VCALC_Matrix* VCALC_VectorZeros(u32 size) {
    return MatrixZeros(size, 1);
}

Matrix* VCALC_VectorFromVa64(u32 size, ...) {
    va_list values;
    va_start(values, size);
    Matrix* vector =  iVCALC_MatrixFromVaList(size, 1, values);
    va_end(values);
    return vector;
}

VCALC_Matrix* VCALC_VectorFromArray(u32 size, f64 array[size]) {
    Matrix* vector = MatrixZeros(size, 1);
    for (u32 i = 0; i < size; i++) {
	vector->values[i] = array[i];
    }
    return vector;
}

f64 VCALC_VectorGet(VCALC_Matrix* vector, u32 x) {
    if (vector->size[0] <= x) return 0;
    return vector->values[x];
}

void VCALC_VectorSet(VCALC_Matrix* vector, u32 x, f64 value) {
    if (vector->size[0] <= x) return;
    vector->values[x] = value;
}


VCALC_Matrix* VCALC_ScalarNew(f64 value) {
    Matrix* scalar = MatrixZeros(1, 1);
    scalar->values[0] = value;
    return scalar;
}

f64 VCALC_ScalarGet(Matrix* scalar) {
    return scalar->values[0];
}

void VCALC_ScalarSet(Matrix* scalar, f64 value) {
    scalar->values[0] = value;
}

Matrix* VCALC_PolyFromVa64(u32 degree, ...) {
    va_list values;
    va_start(values, degree);
    Matrix* poly = iVCALC_MatrixFromVaList(degree + 1, 1, values);
    va_end(values);
    return poly;
}

f64 VCALC_PolyGet(Matrix* poly, u32 power) {
    if (poly->size[0] <= power) return 0;
    return poly->values[power];
}

void VCALC_PolySet(Matrix* poly, u32 power, f64 value) {
    if (poly->size[0] <= power) return;
    poly->values[power] = value;
}

void VCALC_MatrixPrint(Matrix* matrix) {
    for (u32 j = 0; j < matrix->size[1]; j++) {
	for (u32 i = 0; i < matrix->size[0]; i++) {
	    printf("%.4f\t", MatrixGet(matrix, i, j));
	}
	printf("\n");
    }
}

b8 VCALC_MatrixEq(VCALC_Matrix* a, VCALC_Matrix* b) {
    if (a->size[0] != b->size[0] || a->size[1] != b->size[1]) {
	return 1;      
    }
    for (u32 j = 0; j < a->size[1]; j++) {
	for (u32 i = 0; i < a->size[0]; i++) {
	    if (!iVCALC_DoubleEq(MatrixGet(a, i, j), MatrixGet(b, i, j))) {
		return 1;
	    }
	}
    }
    return 0;
}

// MatrixCopy      copies where possible, doesn't change matrix size
// MatrixDup       copies values and dimensions
// MatrixCopyCheck copies if fits, if not, exits with 1
// MatrixCopyat    copies from [x, y] towards right down corner

void VCALC_MatrixCopy(Matrix* to, Matrix* from) {
    for (u32 j = 0; j < from->size[1]; j++) {
	for (u32 i = 0; i < from->size[0]; i++) {
	    MatrixSet(to, i, j, MatrixGet(from, i, j));
	}
    }
}

VCALC_Matrix* VCALC_MatrixDup(VCALC_Matrix* from) {
    Matrix* dup = MatrixZeros(from->size[0], from->size[1]);
    assert(!MatrixCopyCheck(dup, from));
    return dup;
}


void VCALC_MatrixCopyAt(Matrix* to, Matrix* from, u32 x, u32 y) {
    for (u32 j = 0; j < from->size[1]; j++) {
	for (u32 i = 0; i < from->size[0]; i++) {
	    MatrixSet(to, x+i, y+j, MatrixGet(from, i, j));
	}
    }
}

b8 VCALC_MatrixCopyCheck(Matrix* to, Matrix* from) {
    if (to->size[0] < from->size[0] || to->size[1] < from->size[1]) return 1;
    for (u32 j = 0; j < from->size[1]; j++) {
	for (u32 i = 0; i < from->size[0]; i++) {
	    MatrixSet(to, i, j, MatrixGet(from, i, j));
	}
    }
    return 0;
}

Matrix* VCALC_MatrixTransposed(Matrix* matrix) {
    Matrix* new = MatrixZeros(matrix->size[1], matrix->size[0]);
    for (u32 j = 0; j < matrix->size[0]; j++) {
	for (u32 i = 0; i < matrix->size[1]; i++) {
	    MatrixSet(new, i, j, MatrixGet(matrix, j, i));
	}
    }
    return new;
}

Matrix* VCALC_MatrixMultiply(Matrix* a, Matrix* b) {
    Matrix* out = MatrixZeros(a->size[0], b->size[1]);
    if (a->size[1] != b->size[0]) return out;
    
    for (u32 i = 0; i < a->size[0]; i++) {
	for (u32 j = 0; j < b->size[1]; j++) {
	    for (u32 k = 0; k < b->size[0]; k++) {
		f64 curvalue = MatrixGet(out, i, j);
		curvalue += MatrixGet(a, i, k) * MatrixGet(b, k, j);
		MatrixSet(out, i, j, curvalue);
	    }
	}
    }
    
    return out;
}


Matrix* iVCALC_PolyNew(u32 degree) {
    return MatrixZeros(degree+1, 1);
}

Matrix* VCALC_PolyFromArray(u32 degree, f64 array[degree + 1]) {
    Matrix* poly = iVCALC_PolyNew(degree);
    for (u32 i = 0; i <= degree; i++) {
	PolySet(poly, i, array[i]);
    }
    return poly;
}

Matrix* VCALC_PolyDup(Matrix* poly) {
    return PolyFromArray(poly->size[0] - 1, poly->values);
}

Matrix* VCALC_PolyDerivative(Matrix* poly) {
    Matrix *der;
    if (poly->size[0] - 1 > 0) {
	der = iVCALC_PolyNew(poly->size[0] - 2);
    } else {
	der = iVCALC_PolyNew(0);
    }

    for (u32 i = 0; i < der->size[0]; i++) {
	u32 prev_power = i + 1;
	f64 higher_prev_value = PolyGet(poly, i+1);
	f64 this_value = higher_prev_value*prev_power;
	PolySet(der, i, this_value);
    }

    return der;
}

void VCALC_PolyPrint(Matrix* poly) {
    for (u32 i = poly->size[0] - 1; i >= 1; i--) {
	f64 value = PolyGet(poly, i);
	if (value == 0) continue;
	f64 absval = fabs(value);
	b8 minus = value < 0;
	if (i != poly->size[0] - 1) {
	    printf(" %c ", minus ? '-' : '+');
	}

	if (i == 1) {
	    printf("%.2lf*x", absval);
	} else {
	    printf("%.2lf*x^%d", absval, i);
	}
    }

    if (poly->size[0] - 1 == 0) {
	printf("%.2lf", PolyGet(poly, 0));
    } else if (poly->size[0] - 1 > 0 && PolyGet(poly, 1) != 0) {
	f64 value = PolyGet(poly, 1);
	f64 absval = fabs(value);
	b8 minus = value < 0;
	printf(" %c ", minus ? '-' : '+');
	printf("%.2lf", absval);
    }
    printf("\n");
}

b8 VCALC_PolyEq(Matrix* first, Matrix* second) {
    if (first->size[0] != second->size[0]) {
	iVCALC_LogMessage("Not the same degrees: %u and %u\n", first->size[0] - 1, second->size[0] - 1);
	return 1;
    }
    for (u32 i = 0; i < first->size[0]; i++) {
	if (!iVCALC_DoubleEq(PolyGet(first, i), PolyGet(second, i))) {
	    iVCALC_LogMessage("Not the same at power %u.\n%.30lf\n%.30lf\n", i, PolyGet(first, i), PolyGet(second, i));
	    return 1;
	}
    }
    return 0;
}

f64 VCALC_PolyEvaluate(Matrix* poly, f64 x) {
    f64 sum = 0;
    for (u32 i = 0; i < poly->size[0]; i++) {
	sum += PolyGet(poly, i)*pow(x, i);
    }
    return sum;
}

Matrix* VCALC_PolyAntiderivative(Matrix* poly) {
    Matrix* antider = iVCALC_PolyNew(poly->size[0]);

    for (u32 i = 0; i < poly->size[0]; i++) {
	u32 power = i + 1;
	f64 prev_value = PolyGet(poly, i);
	PolySet(antider, i + 1, prev_value/power);
    }

    return antider;
}

f64 VCALC_PolyIntegrate(Matrix* poly, f64 from, f64 to) {
    Matrix* antider = PolyAntiderivative(poly);
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

Matrix* VCALC_PolyParse(char* str) {
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
	if (new_degree > degree) degree = new_degree;
	cursor += read;
    }
    Matrix* poly = iVCALC_PolyNew(degree);
    cursor = 0;
    for(;; cursor++) {
	if (str[cursor] == 0) break;
	u32 read;
	f64 value = 0;
	b8 is_negative = 0;
	b8 has_value = 0;
	u32 power = 0;
	if (str[cursor] == '+') {
	    cursor++;
	}
	else if (str[cursor] == '-') {
	    is_negative = 1;
	    cursor++;
	}
	
	if (sscanf(str + cursor, "%lf%n", &value, &read) == 1) {
	    cursor += read;
	    has_value = 1;
	    if (is_negative) value *= -1;
	}

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
	PolySet(poly, power, PolyGet(poly, power) + value);
	if (str[cursor] == 0) break;
    }
    return poly;
}

Matrix* VCALC_PolyMultiply(Matrix* a, Matrix* b) {
    Matrix* result = iVCALC_PolyNew(a->size[0] + b->size[0] - 2);
    for (u32 i = 0; i < a->size[0]; i++) {
	for (u32 j = 0; j < b->size[0]; j++) {
	    u32 k = i + j;
	    result->values[k] += a->values[i]*b->values[j];
	}
    }
    return result;
}

// Matrix Concatenation

Matrix* VCALC_MatrixSizeSet(Matrix* m, u32 x, u32 y) {
    b8 is_cut = 0;
    Matrix* new = MatrixZeros(x, y);
    MatrixCopy(new, m);
    return new;
}

Matrix* VCALC_MatrixRowsCat(Matrix* first, Matrix* second) {
    u32 size[2];
    size[0] = first->size[0] > second->size[0] ? first->size[0] : second->size[0];
    size[1] = first->size[1] + second->size[1];
    Matrix* result = MatrixZeros(size[0], size[1]);
    MatrixCopy(result, first);
    MatrixCopyAt(result, second, 0, first->size[1]);
    return result;
}

Matrix* VCALC_MatrixColumnsCat(Matrix* first, Matrix* second) {
    u32 size[2];
    size[1] = first->size[1] > second->size[1] ? first->size[1] : second->size[1];
    size[0] = first->size[0] + second->size[0];
    Matrix* result = MatrixZeros(size[0], size[1]);
    MatrixCopy(result, first);
    MatrixCopyAt(result, second, first->size[0], 0);
    return result;
}

// Statistics

f64 VCALC_VectorElementsSum(Matrix* vector) {
    f64 sum = 0;
    for (u32 i = 0; i < vector->size[0]; i++) {
	sum += vector->values[i];
    }
    return sum;
}

f64 VCALC_VectorMean(Matrix* vector) {
    return VectorElementsSum(vector)/vector->size[0];
}

void VCALC_VectorScale(Matrix* vector, f64 scale) {
    for (u32 i = 0; i < vector->size[0]; i++) {
	vector->values[i] *= scale;
    }
}

Matrix* VCALC_MatrixColumnsSum(Matrix* matrix) {
    Matrix* result = VectorZeros(matrix->size[0]);
    for (u32 j = 0; j < matrix->size[1]; j++) {
	f64 sum = 0;
	for (u32 i = 0; i < matrix->size[0]; i++) {
	    sum += MatrixGet(matrix, i, j);
	}
	result->values[j] = sum;
    }
    return result;
}

Matrix* VCALC_MatrixColumnsMean(Matrix* matrix) {
    Matrix* vector = MatrixColumnsSum(matrix);
    VectorScale(vector, matrix->size[1]);
    return vector;
}

f64 VCALC_MatrixElementMean(Matrix* matrix) {
    Matrix* vector = MatrixColumnsMean(matrix);
    f64 result = VectorMean(vector);
    free(vector);
    return result;
}

Matrix* VCALC_VectorFromRange(f64 from, f64 to, f64 step) {
    f64 size_f64 = (to - from)/step + 1;
    u32 size = size_f64 <= 0 ? 0 : size_f64;
    Matrix* vector = VectorZeros(size);
    for (u32 i = 0; i < size; i++) {
	VectorSet(vector, i, from + step*i);
    }
    return vector;
}

Matrix* VCALC_FunctionEvaluateArray(f64 f(f64), Matrix* array) {
    Matrix* results = VectorZeros(array->size[0]);
    for (u32 i = 0; i < array->size[0]; i++) {
	VectorSet(results, i, f(VectorGet(array, i)));
    }
    return results;
}

Matrix* VCALC_FunctionEvaluateRange(f64 f(f64), f64 from, f64 to, f64 step) {
    Matrix* xs = VectorFromRange(from, to, step);
    Matrix* results = FunctionEvaluateArray(f, xs);
    Matrix* outputT = MatrixRowsCat(xs, results);
    Matrix* output = MatrixTransposed(outputT);
    free(xs);
    free(results);
    free(outputT);
    return output;
}

f64 VCALC_FunctionIntegrateTrapezoid(f64 f(f64), f64 from, f64 to, f64 dx) {
    Matrix* range = FunctionEvaluateRange(f, from, to, dx);
    Matrix* end = MatrixFromVa64(2, 1, to, f(to));
    Matrix* full = MatrixRowsCat(range, end);
    free(range); free(end);

    f64 sum = 0;
    for (u32 i = 0; i < full->size[1] - 1; i++) {
	f64 dx = MatrixGet(full, 0, i + 1) - MatrixGet(full, 0, i);
	f64 height = MatrixGet(full, 1, i);
	f64 dy = MatrixGet(full, 1, i+1) - height;
	f64 area = dx*height + dx*dy/2.;
	sum += area;
    }
    free(full);
    return sum;
}
