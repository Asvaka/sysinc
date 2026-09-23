/* 4096_t.h */

#ifndef _4096_T_H
#define _4096_T_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>

#define BYTES 4096 / 8
#define S BYTES / sizeof(uint64_t)

/* Given a
 * minuend	uint64_t min[S]
 * subtrahend	uint64_t sub[S]
 * difference	uint64_t dif[S]
 * 1. Populate dif with the difference between min and sub
 * 2. Return the "carry bit" capturing whether an overflow occured.
 */
uint64_t bigsub(uint64_t *min, uint64_t *sub, uint64_t *dif);

/* Given a
 * addend_0	uint64_t in0[S]
 * addend_1	uint64_t in1[S]
 * sum		uint64_t sum[S]
 * 1. Populate sum with the sum over in0 and in1
 * 2. Return the "carry bit" capturing whether an overflow occured.
 */
uint64_t bigadd(uint64_t *in0, uint64_t *in1, uint64_t *sum);

#endif /* _4096_T_H */
