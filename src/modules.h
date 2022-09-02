#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Modules {
    int id;
    char name[30];
    int memory;
    int level;
    int f_del;
} Modules;

void n_read_name(char *data);
Modules read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const Modules *module, int index);
int get_file_size_in_bytes(FILE *pfile);
int get_records_count_in_file(FILE *pfile);
void print_modules(Modules module);
char *file_name();
void m_print_data(int n);
void m_update_data();
void m_insert_data(int f);
void m_delete_data();
void form_new_file();
void change_files();
void m_turn_off();
void form_new_file_t();
void change_files_t();
void m_turn_off2();
void m_safe_mode();
void form_new_file_main();
void change_files_main();
void print_first_data();
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
void sort();
void m_bi_search(int i);
int bi(FILE *pfile, int l, int r, int x);

#endif  // SRC_MODULES_H_
