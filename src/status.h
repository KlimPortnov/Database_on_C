#ifndef SRC_STATUS_H_
#define SRC_STATUS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Status {
    int id;
    int module;
    int stat;
    char sdate[11];
    char stime[9];
} Status;

void s_read_date(char *data);
void s_read_time(char *data);
Status s_read_record_from_file(FILE *pfile, int index);
void s_write_record_in_file(FILE *pfile, const Status *status, int index);
int s_get_file_size_in_bytes(FILE *pfile);
int s_get_records_count_in_file(FILE *pfile);
void s_print_status(Status status);
char *s_file_name();
void s_print_data(int n);
void s_insert_data(int f);
void s_update_data();
void s_form_new_file();
void s_change_files();
void s_delete_data();
void s_turn_off(int i, int f);

#endif  // SRC_STATUS_H_
