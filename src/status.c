#include "status.h"

void s_read_date(char *data) {
    int i = 0;
    char c;
    scanf("%c", &c);
    while (scanf("%c", &data[i]) && data[i] != '\n') {
        i++;
    }
    data[i] = '\0';
}

void s_read_time(char *data) {
    int i = 0;
    char c;
    scanf("%c", &c);
    while (scanf("%c", &data[i]) && data[i] != '\n') {
        i++;
    }
    data[i] = '\0';
}

Status s_read_record_from_file(FILE *pfile, int index) {
    int offset = index * sizeof(struct Status);
    fseek(pfile, offset, SEEK_SET);
    Status record;
    fread(&record, sizeof(Status), 1, pfile);
    rewind(pfile);
    return record;
}

void s_write_record_in_file(FILE *pfile, const Status *status, int index) {
    int offset = index * sizeof(Status);
    fseek(pfile, offset, SEEK_SET);
    fwrite(status, sizeof(Status), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int s_get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int s_get_records_count_in_file(FILE *pfile) {
    return s_get_file_size_in_bytes(pfile) / sizeof(Status);
}

void s_print_status(Status status) {
    printf("%03d %02d %02d %11s %9s\n", status.id, status.module, status.stat, status.sdate, status.stime);
}

char *s_file_name() {
    return "../materials/master_status_events.db";
}

void s_print_data(int n) {
    FILE *pfile = fopen(s_file_name(), "rb");
    printf("\n");
    int nmax = s_get_records_count_in_file(pfile);
    if (nmax == 0) {
        printf("There is NO data in this database!\n");
    }
    if ((n == -1) || (n > nmax)) {
        n = nmax;
    }
    for (int i = 0; i < n; i++) {
        Status status = s_read_record_from_file(pfile, i);
        s_print_status(status);
    }
    fclose(pfile);
}

void s_insert_data(int f) {
    Status status;
    printf("Enter id int\n");
    scanf("%d", &status.id);
    printf("Enter module id int\n");
    scanf("%d", &status.module);
    printf("Enter module status int\n");
    scanf("%d", &status.stat);
    printf("Enter date dd.mm.yyyy\n");
    s_read_date(status.sdate);
    printf("Enter date hh:mm:ss\n");
    s_read_time(status.stime);
    FILE *pfile = fopen(s_file_name(), "r+b");
    if (f == -1) {
        f = s_get_records_count_in_file(pfile);
    }
    s_write_record_in_file(pfile, &status, f);
    printf("Data success update!\n");
    fclose(pfile);
}

void s_update_data() {
    int f = 0;
    FILE *pfile = fopen(s_file_name(), "r+b");
    int n = s_get_records_count_in_file(pfile);
    if (n) {
        int id;
        printf("\nEnter id to update: ");
        scanf("%d", &id);
        for (int i = 0; i < n; i++) {
            Status status = s_read_record_from_file(pfile, i);
            if (id == status.id) {
                printf("Updating row\n");
                s_print_status(status);
                s_insert_data(i);
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

void s_form_new_file() {
    FILE *pfile = fopen(s_file_name(), "r+b");
    FILE *f_new = fopen("dop", "w+b");
    int i = 0;
    int n = s_get_records_count_in_file(pfile);
    for (int k = 0; k < n; k++) {
        Status status = s_read_record_from_file(pfile, k);
        if (status.stat) {
            s_write_record_in_file(f_new, &status, i);
            i++;
        }
    }
    fclose(pfile);
    fclose(f_new);
}

void s_change_files() {
    FILE *f_new = fopen("dop", "r+b");
    FILE *pfile = fopen(s_file_name(), "w+b");
    int n = s_get_records_count_in_file(f_new);
    for (int i = 0; i < n; i++) {
        Status status = s_read_record_from_file(f_new, i);
        s_write_record_in_file(pfile, &status, i);
    }
    fclose(pfile);
    fclose(f_new);
}

void s_delete_data() {
    printf("Are you sure, that you want to delete ALL data with delete mode != 0 ?\n");
    printf("\n1. Yes\n2. NO\n\n");
    int n;
    scanf("%d", &n);
    if (n == 1) {
        s_form_new_file();
        s_change_files();
        printf("\nData was success deleted!\n");
    }
}

void s_turn_off(int i, int f) {
    FILE *pfile = fopen(s_file_name(), "r+b");
    int n  = s_get_records_count_in_file(pfile);
    Status status;
    status.id = n;
    status.module = i;
    status.stat = f;
    int hours, minutes, seconds, day, month, year;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    day = local->tm_mday;
    month = local->tm_mon + 1;
    year = local->tm_year + 1900;
    char *s = malloc(12*sizeof(char));
    sprintf(s, "%02d.%02d.%04d%c", day, month, year, '\0');
    strcpy(status.sdate, s);
    hours = local->tm_hour;
    minutes = local->tm_min;
    seconds = local->tm_sec;
    char *s2 = malloc(10*sizeof(char));
    sprintf(s2, "%02d:%02d:%02d%c", hours, minutes, seconds, '\0');
    strcpy(status.stime, s2);
    s_write_record_in_file(pfile, &status, n);
    free(s);
    free(s2);
    fclose(pfile);
}
