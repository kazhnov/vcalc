#include "include/vmath/vmath.h"
#include <stdarg.h>

#ifndef _VCALC_LOG_FILE_
#define _VCALC_LOG_FILE_ stderr
#endif

#define iVCALC_LogMessage(x, ...) fprintf(_VCALC_LOG_FILE_, __FILE__":%d: "x, __LINE__, __VA_ARGS__)
#define iVCALC_LogSimple(x)       fprintf(_VCALC_LOG_FILE_, __FILE__":%d: "x, __LINE__);

struct VCALC_Matrix;
typedef struct VCALC_Matrix VCALC_Matrix;

// Matrix Creation
VCALC_Matrix* VCALC_MatrixFromVa64(u32 x, u32 y, ...);
VCALC_Matrix* VCALC_MatrixFromArray(u32 x, u32 y, f64 array[x*y]);
VCALC_Matrix* VCALC_MatrixZeros(u32 x, u32 y);
VCALC_Matrix* VCALC_MatrixOnes(u32 x, u32 y);
void VCALC_MatrixSet(VCALC_Matrix* matrix, u32 x, u32 y, f64 value);
f64 VCALC_MatrixGet(VCALC_Matrix* matrix, u32 x, u32 y);

// MatrixCopy      copies where possible, doesn't change matrix size
// MatrixDup       copies values and dimensions
// MatrixCopyCheck copies if fits, if not, exits with 1
// MatrixCopyat    copies from [x, y] towards right down corner
void VCALC_MatrixCopy(VCALC_Matrix* to, VCALC_Matrix* from);
void VCALC_MatrixCopyAt(VCALC_Matrix* to, VCALC_Matrix* from, u32 x, u32 y);
b8 VCALC_MatrixCopyCheck(VCALC_Matrix* to, VCALC_Matrix* from);
VCALC_Matrix* VCALC_MatrixDup(VCALC_Matrix* from);


void VCALC_MatrixPrint(VCALC_Matrix* matrix);
VCALC_Matrix* VCALC_MatrixTransposed(VCALC_Matrix* matrix);
void VCALC_MatrixTranspose(VCALC_Matrix* matrix);
void VCALC_MatrixMove(VCALC_Matrix* to, VCALC_Matrix* from);
VCALC_Matrix* VCALC_MatrixMultiply(VCALC_Matrix* a, VCALC_Matrix* b);
b8 VCALC_MatrixEq(VCALC_Matrix* a, VCALC_Matrix* b);

// Matrix Concatenation
VCALC_Matrix* VCALC_MatrixSizeSet(VCALC_Matrix* m, u32 x, u32 y);
VCALC_Matrix* VCALC_MatrixRowsCat(VCALC_Matrix* first, VCALC_Matrix* second);
VCALC_Matrix* VCALC_MatrixColumnsCat(VCALC_Matrix* first, VCALC_Matrix* second);

// Vector Creation
VCALC_Matrix* VCALC_VectorZeros(u32 size);
VCALC_Matrix* VCALC_VectorFromVa64(u32 size, ...);
VCALC_Matrix* VCALC_VectorFromArray(u32 size, f64 array[size]);
f64 VCALC_VectorGet(VCALC_Matrix* vector, u32 x);
void VCALC_VectorSet(VCALC_Matrix* vector, u32 x, f64 value);
VCALC_Matrix* VCALC_VectorZeros(u32 size);
void VCALC_VectorScale(VCALC_Matrix* vector, f64 scale);

// Scalar Creation
VCALC_Matrix* VCALC_ScalarNew(f64 value);
f64 VCALC_ScalarGet(VCALC_Matrix* scalar);
void VCALC_ScalarSet(VCALC_Matrix* scalar, f64 value);

// Polynomial Creation
VCALC_Matrix* VCALC_PolyFromVa64(u32 degree, ...);
VCALC_Matrix* VCALC_PolyFromArray(u32 degree, f64 array[degree + 1]);
VCALC_Matrix* VCALC_PolyDerivative(VCALC_Matrix* poly);
VCALC_Matrix* VCALC_PolyAntiderivative(VCALC_Matrix* poly);
void VCALC_PolyPrint(VCALC_Matrix* poly);
u32 VCALC_PolyCopy(VCALC_Matrix* to, VCALC_Matrix* from);
b8 VCALC_PolyEq(VCALC_Matrix* first, VCALC_Matrix* second);
f64 VCALC_PolyEvaluate(VCALC_Matrix* poly, f64 x);
f64 VCALC_PolyIntegrate(VCALC_Matrix* poly, f64 from, f64 to);
VCALC_Matrix* VCALC_PolyParse(char* str);
VCALC_Matrix* VCALC_PolyMultiply(VCALC_Matrix* a, VCALC_Matrix* b);


// Statistics
f64 VCALC_VectorElementsSum(VCALC_Matrix* vector);
f64 VCALC_VectorMean(VCALC_Matrix* vector);
VCALC_Matrix* VCALC_MatrixColumnsSum(VCALC_Matrix* matrix);
VCALC_Matrix* VCALC_MatrixColumnMean(VCALC_Matrix* matrix);
f64 VCALC_MatrixElementsMean(VCALC_Matrix* matrix);

// Function Evaluation
VCALC_Matrix* VCALC_VectorFromRange(f64 from, f64 to, f64 step);
VCALC_Matrix* VCALC_FunctionEvaluateArray(f64 f(f64), VCALC_Matrix* array);
VCALC_Matrix* VCALC_FunctionEvaluateRange(f64 f(f64), f64 from, f64 to, f64 step);
f64 VCALC_FunctionIntegrateTrapezoid(f64 f(f64), f64 from, f64 to, f64 dx);

#ifdef _VCALC_STRIP_PREFIX_

#define Matrix VCALC_Matrix
#define MatrixFromArray VCALC_MatrixFromArray
#define MatrixZeros VCALC_MatrixZeros
#define MatrixOnes VCALC_MatrixOnes
#define MatrixFromVa64 VCALC_MatrixFromVa64
#define MatrixSet VCALC_MatrixSet
#define MatrixGet VCALC_MatrixGet
#define MatrixPrint VCALC_MatrixPrint
#define MatrixCopy VCALC_MatrixCopy
#define MatrixCopyAt VCALC_MatrixCopyAt
#define MatrixCopyCheck VCALC_MatrixCopyCheck
#define MatrixMove VCALC_MatrixMove
#define MatrixTransposed VCALC_MatrixTransposed
#define MatrixTranspose VCALC_MatrixTranspose
#define MatrixMultiply VCALC_MatrixMultiply
#define MatrixEq VCALC_MatrixEq

#define VectorZeros VCALC_VectorZeros
#define VectorFromVa64 VCALC_VectorFromVa64
#define VectorFromArray VCALC_VectorFromArray
#define VectorSet VCALC_VectorSet
#define VectorGet VCALC_VectorGet


#define PolyEvaluate VCALC_PolyEvaluate
#define PolyFromVa64 VCALC_PolyFromVa64
#define PolyFromArray VCALC_PolyFromArray
#define PolyDerivative VCALC_PolyDerivative
#define PolyAntiderivative VCALC_PolyAntiderivative
#define PolyPrint VCALC_PolyPrint
#define PolyCopy VCALC_PolyCopy
#define PolyEq VCALC_PolyEq
#define PolyIntegrate VCALC_PolyIntegrate
#define PolyParse VCALC_PolyParse
#define PolyMultiply VCALC_PolyMultiply

#define VectorElementsSum VCALC_VectorElementsSum
#define VectorMean VCALC_VectorMean
#define VectorScale VCALC_VectorScale
#define MatrixColumnsSum VCALC_MatrixColumnsSum
#define MatrixColumnsMean VCALC_MatrixColumnsMean
#define MatrixElementsMean VCALC_MatrixElementsMean

#define MatrixSizeSet VCALC_MatrixSizeSet
#define MatrixRowsCat VCALC_MatrixRowsCat
#define MatrixColumnsCat VCALC_MatrixColumnsCat

#define VectorFromRange VCALC_VectorFromRange
#define FunctionEvaluateArray VCALC_FunctionEvaluateArray
#define FunctionEvaluateRange VCALC_FunctionEvaluateRange
#define FunctionIntegrateTrapezoid VCALC_FunctionIntegrateTrapezoid
    
// Functio

#endif
