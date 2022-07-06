// "Copyright 2022 leonarda"

#ifndef SRC_STATE_SORT_H_
#define SRC_STATE_SORT_H_

#include <stdio.h>
#include <string.h>

struct log_file {
    int ye;
    int mo;
    int da;
    int ho;
    int mi;
    int se;
    int st;
    int co;
};
struct log_file d[2];
struct log_file tmp[1];

int output();
int sort();
int append();
int is_empty(FILE * filepointer);
int get_menu();

#endif  // SRC_STATE_SORT_H_
