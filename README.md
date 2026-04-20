# vcalc
calc is short for calculator you guys.


octave clone with a better naming choice and made as a library


# The basics

Everything in this library is a 2D matrix. But you can construct these matrices in different ways as to mimic different data types:
Poly is [degree+1]x1 Matrix
Vector is a Nx1 Matrix

You can manipulate with any data form by using matrix functions (MatrixRowsCat, MatrixElementsMean)

You may want to put #define _VCALC_STRIP_PREFIX_ before including the headers, to save what's left of your fingers

# Memory management

Every matrix is created inside a function, but can be freed with a simple free() call

Matrix is an opaque type and cannot be changed directly, only with MatrixSet and other functions

