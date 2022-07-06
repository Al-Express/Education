// "Copyright 2022 leonarda"

#include "state_sort.h"

char filename[249];


int main() {
    int menu, flag = 0;
    FILE * filepointer;
    printf("Введите имя файла:\n");
    printf("> ");
    scanf("%s", filename);
    filepointer = fopen(filename, "rb");
    if (filepointer == NULL) {
        flag = 1;
    } else {
        if (is_empty(filepointer) == 2) {  // empty
            flag = 2;
        } else {
            printf("Введите номер меню: \n");
            printf("0. Вывести файл на экран.\n");
            printf("1. Отсортировать файл и вывести на экран.\n");
            printf("2. Добавить запись, отсортировать и вывести на экран.\n");
            printf("> ");
            menu = get_menu();
            if (menu >= 0) {
                switch (menu) {
                    case 0:
                        flag = output();
                        break;
                    case 1:
                        flag = sort();
                        flag = output();
                        break;
                    case 2:
                        flag = append();
                        // flag = sort();
                        flag = output();
                        break;

                    default:
                        break;
                }
            }
        }
    }
    if ((flag != 0) || (menu == -1))
        printf("n/a\n");
    return 0;
}

int output() {
    int flag = 0;  // 0 - Ok, 1 - not exist, 2 - empty
    FILE * filepointer;
    filepointer = fopen(filename, "rb");
    while (flag == 0) {
        if (fread(&d, sizeof(struct log_file), 1, filepointer) != 1) {
            if (feof(filepointer)) {
                flag = 0;  // end of file
            } else {
                flag = 4;  // reading error
            }
            break;
        } else {
            printf("%4d %2d %2d %2d %2d %2d %1d %3d\n", d[0].ye, d[0].mo, d[0].da, \
            d[0].ho, d[0].mi, d[0].se, d[0].st, d[0].co);
        }
    }
    rewind(filepointer);
    fclose(filepointer);
    return flag;
}

int sort() {
int flag = 0;   // 0 - Ok, 1 - not exist, 2 - empty

    FILE * filepointer;
    filepointer = fopen(filename, "rb");
    if (fread(d, sizeof(struct log_file), 1, filepointer) != 1) {
        if (feof(filepointer)) {
            flag = 3;  // end of file
        } else {
            flag = 4;  // reading error
        }
        rewind(filepointer);
        fclose(filepointer);
    } else {
        // Years
        fseek(filepointer, 0, SEEK_END);
        int counter = ftell(filepointer) / sizeof(struct log_file);
        fclose(filepointer);
        filepointer = fopen(filename, "rb+");
        for (int i = 0; i < counter - 1; i++) {
            fseek(filepointer, 0, SEEK_SET);
            for (int n = counter; n - counter < counter - i; n++) {
                if (fread(d, sizeof(struct log_file), 2, filepointer) == 2) {
                    tmp[0] = d[0];
                    if (d[0].ye > d[1].ye) {
                        d[0] = d[1];
                        d[1] = tmp[0];
                    }
                    fseek(filepointer, -2 * sizeof(struct log_file), SEEK_CUR);
                    fwrite(d, sizeof(struct log_file), 2, filepointer);
                    fflush(filepointer);
                    fseek(filepointer, -1 * sizeof(struct log_file), SEEK_CUR);
                }
            }
        }
        // Months
        fseek(filepointer, 0, SEEK_END);
        counter = ftell(filepointer) / sizeof(struct log_file);
        fclose(filepointer);
        filepointer = fopen(filename, "rb+");
            for (int i = 0; i < counter - 1; i++) {
            fseek(filepointer, 0, SEEK_SET);
            for (int n = counter; n - counter < counter - i; n++) {
                if (fread(d, sizeof(struct log_file), 2, filepointer) == 2) {
                    tmp[0] = d[0];
                    if (d[0].ye == d[1].ye && d[0].mo > d[1].mo) {
                        d[0] = d[1];
                        d[1] = tmp[0];
                    }
                    fseek(filepointer, -2 * sizeof(struct log_file), SEEK_CUR);
                    fwrite(d, sizeof(struct log_file), 2, filepointer);
                    fflush(filepointer);
                    fseek(filepointer, -1 * sizeof(struct log_file), SEEK_CUR);
                }
            }
        }
        // Days
        fseek(filepointer, 0, SEEK_END);
        counter = ftell(filepointer) / sizeof(struct log_file);
        fclose(filepointer);
        filepointer = fopen(filename, "rb+");
        for (int i = 0; i < counter - 1; i++) {
            fseek(filepointer, 0, SEEK_SET);
            for (int n = counter; n - counter < counter - i; n++) {
                if (fread(d, sizeof(struct log_file), 2, filepointer) == 2) {
                    tmp[0] = d[0];
                    if (d[0].ye == d[1].ye && d[0].mo == d[1].mo && d[0].da > d[1].da) {
                        d[0] = d[1];
                        d[1] = tmp[0];
                    }
                    fseek(filepointer, -2 * sizeof(struct log_file), SEEK_CUR);
                    fwrite(d, sizeof(struct log_file), 2, filepointer);
                    fflush(filepointer);
                    fseek(filepointer, -1 * sizeof(struct log_file), SEEK_CUR);
                }
            }
        }
        // Hours
        fseek(filepointer, 0, SEEK_END);
        counter = ftell(filepointer) / sizeof(struct log_file);
        fclose(filepointer);
        filepointer = fopen(filename, "rb+");
        for (int i = 0; i < counter - 1; i++) {
            fseek(filepointer, 0, SEEK_SET);
            for (int n = counter; n - counter < counter - i; n++) {
                if (fread(d, sizeof(struct log_file), 2, filepointer) == 2) {
                    tmp[0] = d[0];
                    if (d[0].ye == d[1].ye && d[0].mo == d[1].mo && d[0].da == d[1].da && d[0].ho > d[1].ho) {
                        d[0] = d[1];
                        d[1] = tmp[0];
                    }
                    fseek(filepointer, -2 * sizeof(struct log_file), SEEK_CUR);
                    fwrite(d, sizeof(struct log_file), 2, filepointer);
                    fflush(filepointer);
                    fseek(filepointer, -1 * sizeof(struct log_file), SEEK_CUR);
                }
            }
        }
        // Minutes
        fseek(filepointer, 0, SEEK_END);
        counter = ftell(filepointer) / sizeof(struct log_file);
        fclose(filepointer);
        filepointer = fopen(filename, "rb+");
        for (int i = 0; i < counter - 1; i++) {
            fseek(filepointer, 0, SEEK_SET);
            for (int n = counter; n - counter < counter - i; n++) {
                if (fread(d, sizeof(struct log_file), 2, filepointer) == 2) {
                    tmp[0] = d[0];
                    if (d[0].ye == d[1].ye && d[0].mo == d[1].mo && d[0].da == d[1].da &&\
                     d[0].ho == d[1].ho && d[0].mi > d[1].mi) {
                        d[0] = d[1];
                        d[1] = tmp[0];
                    }
                    fseek(filepointer, -2 * sizeof(struct log_file), SEEK_CUR);
                    fwrite(d, sizeof(struct log_file), 2, filepointer);
                    fflush(filepointer);
                    fseek(filepointer, -1 * sizeof(struct log_file), SEEK_CUR);
                }
            }
        }
        // Seconds
        fseek(filepointer, 0, SEEK_END);
        counter = ftell(filepointer) / sizeof(struct log_file);
        fclose(filepointer);
        filepointer = fopen(filename, "rb+");
        for (int i = 0; i < counter - 1; i++) {
            fseek(filepointer, 0, SEEK_SET);
            for (int n = counter; n - counter < counter - i; n++) {
                if (fread(d, sizeof(struct log_file), 2, filepointer) == 2) {
                    tmp[0] = d[0];
                    if (d[0].ye == d[1].ye && d[0].mo == d[1].mo && d[0].da == d[1].da &&\
                     d[0].ho == d[1].ho && d[0].mi > d[1].mi && d[0].se > d[1].se) {
                        d[0] = d[1];
                        d[1] = tmp[0];
                    }
                    fseek(filepointer, -2 * sizeof(struct log_file), SEEK_CUR);
                    fwrite(d, sizeof(struct log_file), 2, filepointer);
                    fflush(filepointer);
                    fseek(filepointer, -1 * sizeof(struct log_file), SEEK_CUR);
                }
            }
        }
        rewind(filepointer);
        fclose(filepointer);
        }
    return flag;
}

int append() {
int flag = 0;  // 0 - ok, 1 - not exist


    FILE * filepointer;

    filepointer = fopen(filename, "rb");
    if (fread(&d, sizeof(struct log_file), 1, filepointer) != 1) {
        if (feof(filepointer)) {
            flag = 3;  // end of file
        } else {
            flag = 4;  // reading error
        }
        rewind(filepointer);
        fclose(filepointer);
    } else {
        if (is_empty(filepointer) == 2) {  // empty
            filepointer = fopen(filename, "wb");  // write to begin of file
        } else {
            filepointer = fopen(filename, "ab");  // write to end of file
        }
        fseek(filepointer, sizeof(struct log_file), ftell(filepointer));
        scanf("%d %d %d %d %d %d %d %d", &d[0].ye, &d[0].mo, &d[0].da, &d[0].ho, \
        &d[0].mi, &d[0].se, &d[0].st, &d[0].co);
        fwrite(d, sizeof(struct log_file), 1, filepointer);
    }
    fclose(filepointer);
    return flag;
}


int is_empty(FILE * filepointer) {
    int c, flag = 0;
    filepointer = fopen(filename, "rb");
    if ((c = fgetc(filepointer)) == EOF)
        flag = 2;
    fclose(filepointer);
    return flag;
}

int get_menu() {
    // char end;
    int men;
    scanf("%d", &men);
    getchar();
    // if (end != ' ' || end != '\n')
    //     men = 0;
    if (men >= 0 && men <= 2) {
        {}  // ничего не меняем
    } else {
        men = -1;
    }
    return men;
}
