#include "include/vmath/vmath.h"
#include <stdarg.h>

struct VCALC_Poly;
typedef struct VCALC_Poly VCALC_Poly;

VCALC_Poly* VCALC_PolyFromVa64(u32 degree, ...);
VCALC_Poly* VCALC_PolyFromVector64(u32 degree, f64 vector[degree]);
VCALC_Poly* VCALC_PolyDup(VCALC_Poly* poly);
VCALC_Poly* VCALC_PolyDerivative(VCALC_Poly* poly);
VCALC_Poly* VCALC_PolyAntiderivative(VCALC_Poly* poly);
void VCALC_PolyDifferentiate(VCALC_Poly* poly);
void VCALC_PolyPrint(VCALC_Poly* poly);
u32 VCALC_PolyCopy(VCALC_Poly *to, VCALC_Poly* from);
b8 VCALC_PolyEq(VCALC_Poly* first, VCALC_Poly* second);
f64 VCALC_PolyEvaluate(VCALC_Poly* poly, f64 x);
f64 VCALC_PolyIntegrate(VCALC_Poly* poly, f64 from, f64 to);
VCALC_Poly* VCALC_PolyParse(char* str);

#ifdef _VCALC_STRIP_PREFIX_

#define Poly VCALC_Poly
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

#endif
