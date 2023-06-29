#pragma once

#define MUL2(X) ((X) << 1)
#define DIV2(X) ((X) >> 1)
#define EXP2(N) (1 << (N))

#define MUL_EXP2(X, N) ((X) << (N))
#define DIV_EXP2(X, N) ((X) >> (N))
#define MOD_EXP2(X, N) ((X) & (EXP2(N) - 1))

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define AVG(X, Y) (((X) & (Y)) + (((X) ^ (Y)) >> 1))

#define PAD(X, N) (((X) + (N) - 1) / (N))
