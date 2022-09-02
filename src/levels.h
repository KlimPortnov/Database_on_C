#ifndef SRC_LEVELS_H_
#define SRC_LEVELS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Levels {
    int memory;
    int amount;
    int f_safe;
} Levels;

Levels l_read_record_from_file(FILE *pfile, int index);
void l_write_record_in_file(FILE *pfile, const Levels *module, int index);
int l_get_file_size_in_bytes(FILE *pfile);
int l_get_records_count_in_file(FILE *pfile);
void l_print_levels(Levels level);
char *l_file_name();
void l_print_data(int n);
void l_insert_data(int f);
void l_update_data();
void l_form_new_file();
void l_change_files();
void l_delete_data();
void l_safe_mode();
void l_form_new_file_t();
void l_change_files_t();
void l_safe_mode();

#endif  // SRC_LEVELS_H_

