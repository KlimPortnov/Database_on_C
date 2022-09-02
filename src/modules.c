#include "modules.h"
#include "status.h"
#include "levels.h"


void n_read_name(char *data) {
    int i = 0;
    char c;
    scanf("%c", &c);
    while (scanf("%c", &data[i]) && data[i] != '\n') {
        i++;
    }
    data[i] = '\0';
}

Modules read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct Modules);
    fseek(pfile, offset, SEEK_SET);
    Modules record;
    fread(&record, sizeof(Modules), 1, pfile);
    rewind(pfile);
    return record;
}

void write_record_in_file(FILE *pfile, const Modules *module, int index) {
    int offset = index * sizeof(Modules);
    fseek(pfile, offset, SEEK_SET);
    fwrite(module, sizeof(Modules), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(Modules);
}

void print_modules(Modules module) {
    char *s = malloc(30*sizeof(char));
    strcpy(s, "");
    for (long unsigned int i = 0; i < 15 - strlen(module.name); i++) {
        strcat(s, " ");
    }
    printf("%03d %s%s %02d %02d %02d\n", module.id, module.name, s, module.memory,
           module.level, module.f_del);
    free(s);
}

char *file_name() {
    return "../materials/master_modules.db";
}

void m_print_data(int n) {
    FILE *pfile = fopen(file_name(), "rb");
    printf("\n");
    int nmax = get_records_count_in_file(pfile);
    if (nmax == 0) {
        printf("There is NO data in this database!\n");
    }
    if ((n == -1) || (n > nmax)) {
        n = nmax;
    }
    for (int i = 0; i < n; i++) {
        Modules module = read_record_from_file(pfile, i);
        print_modules(module);
    }
    fclose(pfile);
}

void m_insert_data(int f) {
    Modules module;
    printf("Enter id int\n");
    scanf("%d", &module.id);
    printf("Enter name s\n");
    n_read_name(module.name);
    printf("Enter memory level int\n");
    scanf("%d", &module.memory);
    printf("Enter module level int\n");
    scanf("%d", &module.level);
    printf("Enter flag int\n");
    scanf("%d", &module.f_del);
    FILE *pfile = fopen(file_name(), "r+b");
    if (f == -1) {
        f = get_records_count_in_file(pfile);
    }
    write_record_in_file(pfile, &module, f);
    printf("Data success update!\n");
    fclose(pfile);
}

void m_update_data() {
    int f = 0;
    FILE *pfile = fopen(file_name(), "r+b");
    int n = get_records_count_in_file(pfile);
    if (n) {
        int id;
        printf("\nEnter id to update: ");
        scanf("%d", &id);
        for (int i = 0; i < n; i++) {
            Modules module = read_record_from_file(pfile, i);
            if (id == module.id) {
                printf("Updating row\n");
                print_modules(module);
                m_insert_data(i);
                f = 1;
            }
        }
    } else {
        printf("Nothing to update!\n");
    }
    if ((!f) && (n)) {
        printf("There is no data with that id!\n");
    }
    fclose(pfile);
}

void form_new_file() {
    FILE *pfile = fopen(file_name(), "r+b");
    FILE *f_new = fopen("dop", "w+b");
    int i = 0;
    int n = get_records_count_in_file(pfile);
    for (int k = 0; k < n; k++) {
        Modules module = read_record_from_file(pfile, k);
        if (!module.f_del) {
            write_record_in_file(f_new, &module, i);
            i++;
        }
    }
    fclose(pfile);
    fclose(f_new);
}

void change_files() {
    FILE *f_new = fopen("dop", "r+b");
    FILE *pfile = fopen(file_name(), "w+b");
    int n = get_records_count_in_file(f_new);
    for (int i = 0; i < n; i++) {
        Modules module = read_record_from_file(f_new, i);
        write_record_in_file(pfile, &module, i);
    }
    fclose(pfile);
    fclose(f_new);
}

void m_delete_data() {
    printf("Are you sure, that you want to delete ALL data with delete mode != 0 ?\n");
    printf("\n1. Yes\n2. NO\n\n");
    int n;
    scanf("%d", &n);
    if (n == 1) {
        form_new_file();
        change_files();
        printf("\nData was success deleted!\n");
    }
}

void form_new_file_t() {
    FILE *pfile = fopen(file_name(), "r+b");
    FILE *f_new = fopen("dop", "w+b");
    int i = 0;
    int n = get_records_count_in_file(pfile);
    for (int k = 0; k < n; k++) {
        Modules module = read_record_from_file(pfile, k);
        if (module.id) {
            module.f_del = 1;
        }
        write_record_in_file(f_new, &module, i);
        i++;
    }
    fclose(pfile);
    fclose(f_new);
}

void change_files_t() {
    FILE *f_new = fopen("dop", "r+b");
    FILE *pfile = fopen(file_name(), "w+b");
    int n = get_records_count_in_file(f_new);
    for (int i = 0; i < n; i++) {
        Modules module = read_record_from_file(f_new, i);
        write_record_in_file(pfile, &module, i);
    }
    fclose(pfile);
    fclose(f_new);
}

void m_turn_off() {
    FILE *pfile = fopen(file_name(), "r+b");
    int n = get_records_count_in_file(pfile);
    for (int i = 0; i < n; i++) {
        Modules module = read_record_from_file(pfile, i);
        if (module.id) {
            s_turn_off(module.id, 0);
        }
    }
    fclose(pfile);
}

void m_turn_off2() {
    form_new_file_t();
    change_files_t();
}

void form_new_file_main() {
    FILE *pfile = fopen(file_name(), "r+b");
    FILE *f_new = fopen("dop", "w+b");
    int i = 0;
    int n = get_records_count_in_file(pfile);
    for (int k = 0; k < n; k++) {
        Modules module = read_record_from_file(pfile, k);
        if (!module.id) {
            module.level = 1;
            module.memory = 1;
        }
        write_record_in_file(f_new, &module, i);
        i++;
    }
    fclose(pfile);
    fclose(f_new);
}

void change_files_main() {
    FILE *f_new = fopen("dop", "r+b");
    FILE *pfile = fopen(file_name(), "w+b");
    int n = get_records_count_in_file(f_new);
    for (int i = 0; i < n; i++) {
        Modules module = read_record_from_file(f_new, i);
        write_record_in_file(pfile, &module, i);
    }
    fclose(pfile);
    fclose(f_new);
}

void m_safe_mode() {
    FILE *pfile = fopen(file_name(), "r+b");
    int n = get_records_count_in_file(pfile);
    for (int i = 0; i < n; i++) {
        Modules module = read_record_from_file(pfile, i);
        if (!module.id) {
            s_turn_off(module.id, 0);
            s_turn_off(module.id, 1);
            s_turn_off(module.id, 20);
        }
    }
    form_new_file_main();
    change_files_main();
    l_safe_mode();
    fclose(pfile);
}

void print_first_data() {
    FILE *pfile = fopen(file_name(), "rb");
    printf("\n");
    int nmax = get_records_count_in_file(pfile);
    if (nmax == 0) {
        printf("There is NO data in this database!\n");
    }
    for (int i = 0; i < nmax; i++) {
        Modules module = read_record_from_file(pfile, i);
        if ((module.memory == 1) && (module.level == 1) && (module.f_del == 0))
            print_modules(module);
    }
    fclose(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
    Modules record1 = read_record_from_file(pfile, record_index1);
    Modules record2 = read_record_from_file(pfile, record_index2);
    write_record_in_file(pfile, &record1, record_index2);
    write_record_in_file(pfile, &record2, record_index1);
}

void sort() {
    FILE *pfile = fopen(file_name(), "rb");
    int n = get_records_count_in_file(pfile);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            Modules a = read_record_from_file(pfile, j);
            Modules b = read_record_from_file(pfile, j + 1);
            if (a.id > b.id) {
                swap_records_in_file(pfile, j, j + 1);
            }
        }
    }
    fclose(pfile);
}

int bi(FILE *pfile, int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        Modules module = read_record_from_file(pfile, mid);
        if (module.id == x)
            return mid;
        if (module.id > x)
            return bi(pfile, l, mid - 1, x);
        return bi(pfile, mid + 1, r, x);
    }
    return -1;
}

void m_bi_search(int i) {
    FILE *pfile = fopen(file_name(), "rb");
    Modules module = read_record_from_file(pfile, i);
    int id = module.id;
    int n = get_records_count_in_file(pfile);
    int k = bi(pfile, 0, n, id);
    if ((i < 0) || (i > n - 1)) {
        printf("\nЭлемента с таким номером нет");
    } else {
        module = read_record_from_file(pfile, k);
        print_modules(module);
    }
    fclose(pfile);
}
