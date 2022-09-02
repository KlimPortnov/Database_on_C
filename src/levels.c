#include "levels.h"

Levels l_read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct Levels);
    fseek(pfile, offset, SEEK_SET);
    Levels record;
    fread(&record, sizeof(Levels), 1, pfile);
    rewind(pfile);
    return record;
}

void l_write_record_in_file(FILE *pfile, const Levels *module, int index) {
    int offset = index * sizeof(Levels);
    fseek(pfile, offset, SEEK_SET);
    fwrite(module, sizeof(Levels), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int l_get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int l_get_records_count_in_file(FILE *pfile) {
    return l_get_file_size_in_bytes(pfile) / sizeof(Levels);
}

void l_print_levels(Levels level) {
    printf("%02d %02d %02d\n", level.memory, level.amount, level.f_safe);
}

char *l_file_name() {
    return "../materials/master_levels.db";
}

void l_print_data(int n) {
    FILE *pfile = fopen(l_file_name(), "rb");
    printf("\n");
    int nmax = l_get_records_count_in_file(pfile);
    if (nmax == 0) {
        printf("There is NO data in this database!\n");
    }
    if ((n == -1) || (n > nmax)) {
        n = nmax;
    }
    for (int i = 0; i < n; i++) {
        Levels level = l_read_record_from_file(pfile, i);
        l_print_levels(level);
    }
    fclose(pfile);
}

void l_insert_data(int f) {
    Levels level;
    printf("Enter memory level int\n");
    scanf("%d", &level.memory);
    printf("Enter amount of positions int\n");
    scanf("%d", &level.amount);
    printf("Enter flag safe int\n");
    scanf("%d", &level.f_safe);
    FILE *pfile = fopen(l_file_name(), "r+b");
    if (f == -1) {
        f = l_get_records_count_in_file(pfile);
    }
    l_write_record_in_file(pfile, &level, f);
    printf("Data success update!\n");
    fclose(pfile);
}

void l_update_data() {
    int f = 0;
    FILE *pfile = fopen(l_file_name(), "r+b");
    int n = l_get_records_count_in_file(pfile);
    if (n) {
        int l;
        printf("\nEnter level to update: ");
        scanf("%d", &l);
        for (int i = 0; i < n; i++) {
            Levels level = l_read_record_from_file(pfile, i);
            if (l == level.memory) {
                printf("Updating row\n");
                l_print_levels(level);
                l_insert_data(i);
                f = 1;
            }
        }
    } else {
        printf("Nothing to update!\n");
    }
    if ((!f) && (n)) {
        printf("There is no data with that memory level!\n");
    }
    fclose(pfile);
}

void l_form_new_file() {
    FILE *pfile = fopen(l_file_name(), "r+b");
    FILE *f_new = fopen("dop", "w+b");
    int i = 0;
    int n = l_get_records_count_in_file(pfile);
    for (int k = 0; k < n; k++) {
        Levels level = l_read_record_from_file(pfile, k);
        if (level.f_safe) {
            l_write_record_in_file(f_new, &level, i);
            i++;
        }
    }
    fclose(pfile);
    fclose(f_new);
}

void l_change_files() {
    FILE *f_new = fopen("dop", "r+b");
    FILE *pfile = fopen(l_file_name(), "w+b");
    int n = l_get_records_count_in_file(f_new);
    for (int i = 0; i < n; i++) {
        Levels level = l_read_record_from_file(f_new, i);
        l_write_record_in_file(pfile, &level, i);
    }
    fclose(pfile);
    fclose(f_new);
}

void l_delete_data() {
    printf("Are you sure, that you want to delete ALL levels with safe mode = 0 ?\n");
    printf("\n1. Yes\n2. NO\n\n");
    int n;
    scanf("%d", &n);
    if (n == 1) {
        l_form_new_file();
        l_change_files();
        printf("\nData was success deleted!\n");
    }
}

void l_form_new_file_t() {
    FILE *pfile = fopen(l_file_name(), "r+b");
    FILE *f_new = fopen("dop", "w+b");
    int i = 0;
    int n = l_get_records_count_in_file(pfile);
    for (int k = 0; k < n; k++) {
        Levels level = l_read_record_from_file(pfile, k);
        if (level.memory == 1) {
            level.f_safe = 1;
        }
        l_write_record_in_file(f_new, &level, i);
        i++;
    }
    fclose(pfile);
    fclose(f_new);
}

void l_change_files_t() {
    FILE *f_new = fopen("dop", "r+b");
    FILE *pfile = fopen(l_file_name(), "w+b");
    int n = l_get_records_count_in_file(f_new);
    for (int i = 0; i < n; i++) {
        Levels level = l_read_record_from_file(f_new, i);
        l_write_record_in_file(pfile, &level, i);
    }
    fclose(pfile);
    fclose(f_new);
}
void l_safe_mode() {
    l_form_new_file_t();
    l_change_files_t();
}
