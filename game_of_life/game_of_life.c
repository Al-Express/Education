// "Copyright 2022 leonarda"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define Length 80
#define Height 25

int* world;

int get_menu(int quantity_main);

void world_create(int ***world);
void random_world(int **world);
int custom_world(int **world);
void empty_world(int **world);
void print_world(int **world);
void copy_world(int **world, int **next_world);

int neighbor_count(int **world, int height, int length);
void check_new_birth(int **world, int **next_world);
void check_isolation(int **world, int **next_world);
void check_overpopulation(int **world, int **next_world);
void check_still_alive(int **world, int **next_world);

int main() {
    int err = 0;
    int choice = 0, quantity = 2;
    int time = 10;
    int key = 49;
    int **main_world, **temp;

    world_create(&temp);
    world_create(&main_world);

    printf("Please choose: 1 - Load custom preset, 2 - Generate random preset > ");
    choice = get_menu(quantity);
    if (choice != 0) {
        switch (choice) {
                case 1:
                    err = custom_world(main_world);
                    break;
                case 2:
                    random_world(main_world);
                    break;
                default:
                    break;
        }
    } else {
        err = 1;
    }
    if (err == 0) {
        initscr();
        clear();
        noecho();
        curs_set(0);
        print_world(main_world);
        while (1 < 2) {
            refresh();
            halfdelay(time);
            key = getch();
            empty_world(temp);
            check_new_birth(main_world, temp);
            check_isolation(main_world, temp);
            check_overpopulation(main_world, temp);
            check_still_alive(main_world, temp);
            print_world(temp);
            refresh();
            if (key >= 49 && key <= 57) {
                time = 58 - key;
            }
            if (key == 32) {
                do {
                    key = getch();
                } while (key != 32);
            }
            if (key == 113 || key == 27) {
                break;
            }
            copy_world(main_world, temp);
        }
        curs_set(1);
        clear();
        refresh();
        endwin();
    } else {
        printf("n/a\n");
    }
    free(main_world);
    free(temp);
    return 0;
}

void empty_world(int **world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            world[i][j] = 0;
        }
    }
}

void world_create(int ***world) {
    *world = malloc(Height * Length * sizeof(int) + Height * sizeof(int*));
    int* pworld = (int*)(*world + Height);
    for (int i = 0; i < Height; i++) {
        (*world)[i] = pworld + Length * i;
    }
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            (*world)[i][j] = 0;
        }
    }
}

void random_world(int **world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            int r = rand()%11;
            if (r > 5) {
                world[i][j] = 1;
            }
        }
    }
}

int custom_world(int **world) {
    int err = 0;
    char tmp;
    char filename[250];
    printf("Enter name of text file > ");
    scanf("%s", filename);
    FILE *fpointer;
    fpointer = fopen(filename, "r");
    if (fpointer) {
        for (int i = 5; i < Height; i++) {
            for (int j = 25; j < Length; j++) {
                fread(&tmp, sizeof(char), 1, fpointer);
                if (feof(fpointer)) {
                    i = Height;
                    j = Length;
                    break;
                }
                if (tmp == '\0' || tmp == '\n') {
                    break;
                } else {
                    if (tmp == '1') {
                        world[i][j] = 1;
                    }
                }
            }
        }
        fclose(fpointer);
    } else {
        err = 1;
    }
    return err;
}

int neighbor_count(int **world, int i, int j) {
    int count = 0 - world[i][j];
    for (int n = i - 1; n <= i + 1; n++) {
        for (int m = j - 1; m <= j + 1; m++) {
            count += world[(n + Height) % Height][(m + Length) % Length];
        }
    }
    return count;
}

void check_new_birth(int **world, int **next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 0) {
                if (neighbor_count(world, i, j) == 3) {
                    next_world[i][j] = 1;
                }
            }
        }
    }
}

void check_isolation(int **world, int **next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 1) {
                if (neighbor_count(world, i, j) < 2) {
                    next_world[i][j] = 0;
                }
            }
        }
    }
}

void check_overpopulation(int **world, int **next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 1) {
                if (neighbor_count(world, i, j) > 4) {
                    next_world[i][j] = 0;
                }
            }
        }
    }
}


void check_still_alive(int **world, int **next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 1) {
                if (neighbor_count(world, i, j) == 2 || neighbor_count(world, i, j) == 3) {
                    next_world[i][j] = 1;
                }
            }
        }
    }
}


void print_world(int **world) {
    move(0, 0);
    printw("Press 1..9 for speed, Space for pause, q or Esc for exit");
    refresh();
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            move(i + 1, j);
            if (world[i][j] == 1) {
                printw("#");
                refresh();
            } else {
                printw(" ");
                refresh();
            }
        }
    }
}

void copy_world(int **world, int **next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            world[i][j] = next_world[i][j];
        }
    }
}

int get_menu(int quantity) {
    int men;
    scanf("%d", &men);
    if (men > 0 && men <= quantity) {
        {}  // ничего не меняем
    } else {
        men = 0;
    }
    return men;
}
