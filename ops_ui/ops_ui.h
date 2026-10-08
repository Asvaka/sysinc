#ifndef _ops_ui_H
#define _ops_ui_H
#include "4096_t.h"


uint64_t add_ui(uint64_t *big, uint64_t lil, uint64_t *out);
uint64_t sub_ui(uint64_t *big, uint64_t lil, uint64_t *out);
uint64_t mul_ui(uint64_t *big, uint64_t lil, uint64_t *out);
uint64_t quo_ui(uint64_t *big, uint64_t lil, uint64_t *out);
uint64_t rem_ui(uint64_t *big, uint64_t lil, uint64_t *out);

#endif
