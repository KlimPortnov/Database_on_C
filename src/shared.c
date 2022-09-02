#include "shared.h"

int choose_table() {
    int r = 0;
    printf("\nPlease choose a table:\n");
    printf("1. Modules\n2. Levels\n3. Status events\n\n");
    scanf("%d", &r);
    if (r == 1) {
        return 1;
    }
    if (r == 2) {
        return 2;
    }
    if (r == 3) {
        return 3;
    }
    printf("%s", "Error input\n");
    return 0;
}

int n_output() {
    int n;
    printf("\nInsert the number of records or insert -1 to output all of them: ");
    scanf("%d", &n);
    return n;
}

void select_d() {
    BD bd = choose_table();
    if (bd) {
        int n = n_output();
        switch (bd) {
            case MODULES: m_print_data(n); break;
            case LEVELS: l_print_data(n); break;
            case STATUS: s_print_data(n); break;
        }
    }
}

void update_d() {
    BD bd = choose_table();
    if (bd) {
        switch (bd) {
            case MODULES: m_update_data(); break;
            case LEVELS: l_update_data(); break;
            case STATUS: s_update_data(); break;
        }
    }
}

void insert_d() {
    BD bd = choose_table();
    if (bd) {
        switch (bd) {
            case MODULES: m_insert_data(-1); break;
            case LEVELS: l_insert_data(-1); break;
            case STATUS: s_insert_data(-1); break;
        }
    }
}

void delete_d() {
    BD bd = choose_table();
    if (bd) {
        switch (bd) {
            case MODULES: m_delete_data(); break;
            case LEVELS: l_delete_data(); break;
            case STATUS: s_delete_data(); break;
        }
    }
}

void turn_off() {
    m_turn_off();
    printf("New modules status were created\n");
}

void turn_off2() {
    m_turn_off2();
    printf("Modules flags were changed\n");
}

void safe_mode() {
    m_safe_mode();
    printf("Main module in safe mode\n");
}

void select_first() {
    print_first_data();
}

void bi_search() {
    sort();
    int i;
    printf("\nInsert the number: ");
    scanf("%d", &i);
    m_bi_search(i);
}
