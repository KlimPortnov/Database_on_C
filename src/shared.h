#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#include <stdlib.h>
#include <stdio.h>
#include "modules.h"
#include "levels.h"
#include "status.h"

typedef enum BD {
    MODULES = 1,
    LEVELS,
    STATUS
} BD;

int choose_table();
int n_output();
int n_input();
void select_d();
void update_d();
void insert_d();
void delete_d();
void turn_off();
void turn_off2();
void safe_mode();
void select_first();
void bi_search();

#endif  // SRC_SHARED_H_
