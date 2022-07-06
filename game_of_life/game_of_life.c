// "Copyright 2022 leonarda"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define Length 80
#define Height 25



void random_world_generator(int ***world);
void dead_world_generator(int ***world);
void custom_world_generator(int **world);

int* world;

void print_world(int **world);
int neighbor_count(int **world, int height, int length);
void check_new_birth(int **world, int ***next_world);
void check_isolation(int **world, int ***next_world);
void check_overpopulation(int **world, int ***next_world);
void check_still_alive(int **world, int ***next_world);


void copy_world(int ***world, int **next_world);


int main() {
    initscr();
    clear();
    int time = 100000;
    int **main_world, **temp;
    dead_world_generator(&temp);
    dead_world_generator(&main_world);
    random_world_generator(&main_world);
    custom_world_generator(main_world);
    print_world(main_world);
    int speed = 9;
    int y = 0;
    int x = 0;

    while (1 < 2) {
        refresh();
        speed = getch();
        usleep(time);
        dead_world_generator(&temp);

        check_new_birth(main_world, &temp);
        check_isolation(main_world, &temp);
        check_overpopulation(main_world, &temp);
        check_still_alive(main_world, &temp);
        print_world(temp);
        getyx(stdscr, y, x);

        move(y + 1, x = 0);
        printw("%d", speed);
        if (speed == 43) {
            time -= 100000;
        }
        if (speed == 45) {
            time += 100000;
        }
        if (speed == 113) {
            break;
        }
        copy_world(&main_world, temp);
    }
    endwin();
    free(main_world);
    free(temp);
    return 0;
}

void random_world_generator(int ***world) {
    *world = malloc(Height * Length * sizeof(int) + Height * sizeof(int*));
    int* pworld = (int*)(*world + Height);
    for (int i = 0; i < Height; i++) {
        (*world)[i] = pworld + Length * i;
    }
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            int r = rand()%11;
            if (r > 5) {
                (*world)[i][j] = 1;
            }
        }
    }
}


void dead_world_generator(int ***world) {
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

void custom_world_generator(int **world) {
    int tmp;
//   char c;
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            scanw("%d", &tmp);
//            if (c == EOF || c == '.') {
//                i = Height;
//               j = Length;
//            } else {
                world[i][j] = tmp;
//                if (c == '\n') {
//                    i++;
 //                   j = -1;    
 //               }
 //           }
        }
    }
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

void check_new_birth(int **world, int ***next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 0) {
                if (neighbor_count(world, i, j) == 3) {
                    (*next_world)[i][j] = 1;
                }
            }
        }
    }
}

void check_isolation(int **world, int ***next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 1) {
                if (neighbor_count(world, i, j) < 2) {
                    (*next_world)[i][j] = 0;
                }
            }
        }
    }
}

void check_overpopulation(int **world, int ***next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 1) {
                if (neighbor_count(world, i, j) > 4) {
                    (*next_world)[i][j] = 0;
                }
            }
        }
    }
}


void check_still_alive(int **world, int ***next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (world[i][j] == 1) {
                if (neighbor_count(world, i, j) == 2 || neighbor_count(world, i, j) == 3) {
                    (*next_world)[i][j] = 1;
                }
            }
        }
    }
}


void print_world(int **world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            move(i, j);
            if (world[i][j] == 1) {
                printw("*");
                refresh();
            } else {
                printw(" ");
                refresh();
            }
        }
    }
}

void copy_world(int ***world, int **next_world) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            (*world)[i][j] = next_world[i][j];
        }
    }
}
