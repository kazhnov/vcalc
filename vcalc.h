#include "include/vmath/vmath.h"
#include <stdarg.h>

struct VCALC_Matrix;
typedef struct VCALC_Matrix VCALC_Matrix;

VCALC_Matrix* VCALC_MatrixFromVa64(u32 x, u32 y, ...);
VCALC_Matrix* VCALC_MatrixZeros(u32 x, u32 y);
VCALC_Matrix* VCALC_MatrixOnes(u32 x, u32 y);
void VCALC_MatrixSet(VCALC_Matrix* matrix, u32 x, u32 y, f64 value);
f64 VCALC_MatrixGet(VCALC_Matrix* matrix, u32 x, u32 y);
void VCALC_MatrixPrint(VCALC_Matrix* matrix);
VCALC_Matrix* VCALC_MatrixTransposed(VCALC_Matrix* matrix);
void VCALC_MatrixTranspose(VCALC_Matrix* matrix);
void VCALC_MatrixCopy(VCALC_Matrix* to, VCALC_Matrix* from);
void VCALC_MatrixMove(VCALC_Matrix* to, VCALC_Matrix* from);
VCALC_Matrix* VCALC_MatrixMultiply(VCALC_Matrix* a, VCALC_Matrix* b);
b8 VCALC_MatrixEq(VCALC_Matrix* a, VCALC_Matrix* b);

VCALC_Matrix* VCALC_VectorFromVa64(u32 size, ...);

VCALC_Matrix* VCALC_PolyFromVa64(u32 degree, ...);
VCALC_Matrix* VCALC_PolyFromVector64(u32 degree, f64 vector[degree]);
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

#ifdef _VCALC_STRIP_PREFIX_

#define Matrix VCALC_Matrix
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

#define VectorFromVa64 VCALC_VectorFromVa64

#define PolyEvaluate VCALC_PolyEvaluate
#define PolyFromVa64 VCALC_PolyFromVa64
#define PolyFromVector64 VCALC_PolyFromVector64
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

#endif
