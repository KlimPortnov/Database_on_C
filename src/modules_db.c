#include "shared.h"

void print_m() {
    printf("\n\nPlease choose one operation:\n");
    printf("1. SELECT\n2. INSERT\n3. UPDATE\n4. DELETE\n");
    printf("5. Turn off all additional modules\n");
    printf("6. DELETE entry for additional modules (flag = 1)\n");
    printf("7. Main module safe mode\n");
    printf("8. SELECT 1 CELL of 1 LEVEL\n");
    printf("9. Binary search by id\n");
    printf("0. EXIT\n\n");
}


int main() {
    int r = 0;
    print_m();
    while (scanf("%d", &r)) {
        if (r == 1) {
            select_d();
        }
        if (r == 2) {
            insert_d();
        }
        if (r == 3) {
            update_d();
        }
        if (r == 4) {
            delete_d();
        }
        if (r == 5) {
            turn_off();
        }
        if (r == 6) {
            turn_off2();
        }
        if (r == 7) {
            safe_mode();
        }
        if (r == 8) {
            select_first();
        }
        if (r == 9) {
            bi_search();
        }
        if (r == 0) {
            break;
        }
        print_m();
    }
    return 0;
}
