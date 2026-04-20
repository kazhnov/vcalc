#include "include/vmath/vmath.h"
#include <stdarg.h>

#ifndef _VCALC_LOG_FILE_
#define _VCALC_LOG_FILE_ stderr
#endif

#define iVCALC_LogMessage(x, ...) fprintf(_VCALC_LOG_FILE_, __FILE__":%d: "x, __LINE__, __VA_ARGS__)
#define iVCALC_LogSimple(x)       fprintf(_VCALC_LOG_FILE_, __FILE__":%d: "x, __LINE__);

struct VCALC_Matrix;
typedef struct VCALC_Matrix VCALC_Matrix;

VCALC_Matrix* VCALC_MatrixFromVa64(u32 x, u32 y, ...);
VCALC_Matrix* VCALC_MatrixFromArray(u32 x, u32 y, f64 array[x*y]);
VCALC_Matrix* VCALC_MatrixZeros(u32 x, u32 y);
VCALC_Matrix* VCALC_MatrixOnes(u32 x, u32 y);
void VCALC_MatrixSet(VCALC_Matrix* matrix, u32 x, u32 y, f64 value);
f64 VCALC_MatrixGet(VCALC_Matrix* matrix, u32 x, u32 y);
void VCALC_MatrixPrint(VCALC_Matrix* matrix);
VCALC_Matrix* VCALC_MatrixTransposed(VCALC_Matrix* matrix);
void VCALC_MatrixTranspose(VCALC_Matrix* matrix);
b8 VCALC_MatrixCopy(VCALC_Matrix* to, VCALC_Matrix* from);
void VCALC_MatrixMove(VCALC_Matrix* to, VCALC_Matrix* from);
VCALC_Matrix* VCALC_MatrixDup(VCALC_Matrix* from);
VCALC_Matrix* VCALC_MatrixMultiply(VCALC_Matrix* a, VCALC_Matrix* b);
b8 VCALC_MatrixEq(VCALC_Matrix* a, VCALC_Matrix* b);


VCALC_Matrix* VCALC_VectorZeros(u32 size);
VCALC_Matrix* VCALC_VectorFromVa64(u32 size, ...);
VCALC_Matrix* VCALC_VectorFromArray(u32 size, f64 array[size]);
f64 VCALC_VectorGet(VCALC_Matrix* vector, u32 x);
void VCALC_VectorSet(VCALC_Matrix* vector, u32 x, f64 value);


VCALC_Matrix* VCALC_ScalarNew(f64 value);
f64 VCALC_ScalarGet(VCALC_Matrix* scalar);
void VCALC_ScalarSet(VCALC_Matrix* scalar, f64 value);


VCALC_Matrix* VCALC_PolyFromVa64(u32 degree, ...);
VCALC_Matrix* VCALC_PolyFromArray(u32 degree, f64 array[degree + 1]);
VCALC_Matrix* VCALC_PolyDup(VCALC_Matrix* poly);
VCALC_Matrix* VCALC_PolyDerivative(VCALC_Matrix* poly);
VCALC_Matrix* VCALC_PolyAntiderivative(VCALC_Matrix* poly);
void VCALC_PolyDifferentiate(VCALC_Matrix* poly);
void VCALC_PolyPrint(VCALC_Matrix* poly);
u32 VCALC_PolyCopy(VCALC_Matrix* to, VCALC_Matrix* from);
b8 VCALC_PolyEq(VCALC_Matrix* first, VCALC_Matrix* second);
f64 VCALC_PolyEvaluate(VCALC_Matrix* poly, f64 x);
f64 VCALC_PolyIntegrate(VCALC_Matrix* poly, f64 from, f64 to);
VCALC_Matrix* VCALC_PolyParse(char* str);
VCALC_Matrix* VCALC_PolyMultiply(VCALC_Matrix* a, VCALC_Matrix* b);

VCALC_Matrix* VCALC_VectorZeros(u32 size);
f64 VCALC_VectorElementsSum(VCALC_Matrix* vector);
f64 VCALC_VectorMean(VCALC_Matrix* vector);
void VCALC_VectorScale(VCALC_Matrix* vector, f64 scale);
VCALC_Matrix* VCALC_MatrixColumnsSum(VCALC_Matrix* matrix);
VCALC_Matrix* VCALC_MatrixColumnMean(VCALC_Matrix* matrix);
f64 VCALC_MatrixElementsMean(VCALC_Matrix* matrix);

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
#define MatrixMove VCALC_MatrixMove
#define MatrixTransposed VCALC_MatrixTransposed
#define MatrixTranspose VCALC_MatrixTranspose
#define MatrixMultiply VCALC_MatrixMultiply
#define MatrixEq VCALC_MatrixEq

#define VectorZeros VCALC_VectorZeros
#define VectorFromVa64 VCALC_VectorFromVa64
#define VectorFromArray VCALC_VectorFromArray

#define PolyEvaluate VCALC_PolyEvaluate
#define PolyFromVa64 VCALC_PolyFromVa64
#define PolyFromArray VCALC_PolyFromArray
#define PolyDup VCALC_PolyDup
#define PolyDerivative VCALC_PolyDerivative
#define PolyAntiderivative VCALC_PolyAntiderivative
#define PolyDifferentiate VCALC_PolyDifferentiate
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


#endif
