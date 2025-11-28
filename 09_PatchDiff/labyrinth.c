#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROOMS_NUM 6
#define LABYRINTH_LENGTH (ROOMS_NUM * 2 + 1)

#define WALL '#'
#define PATH '.'

void init_labyrinth(char labyrinth[LABYRINTH_LENGTH][LABYRINTH_LENGTH]) {
    for (int i = 0; i < LABYRINTH_LENGTH; i++)
        for (int j = 0; j < LABYRINTH_LENGTH; j++)
                labyrinth[i][j] = (i % 2 == 0 || j % 2 == 0) ? WALL : PATH;
}

void shuffle_dirs(int dirs[4]) {
    for (int i = 0; i < 4; i++) {
        int swap_tmp = dirs[i];
        int j = rand() % 4;
        dirs[i] = dirs[j];
        dirs[j] = swap_tmp;
    }
}

bool valid_coords(int x, int y, int size) {
    return (x >= 0 && x < size && y >= 0 && y < size);
}

void gen_labyrinth(int x, int y, bool visited_rooms[ROOMS_NUM][ROOMS_NUM], char labyrinth[LABYRINTH_LENGTH][LABYRINTH_LENGTH]) {
    int dirs[4] = {0, 1, 2, 3};
    shuffle_dirs(dirs);

    int x_dirs[4] = {0, 1, 0, -1};
    int y_dirs[4] = {1, 0, -1, 0};

    visited_rooms[y][x] = true;

    for (int i = 0; i < 4; i++) {
        int dir = dirs[i];
        int new_x = x + x_dirs[dir];
        int new_y = y + y_dirs[dir];

        if (valid_coords(new_x, new_y, ROOMS_NUM) && !visited_rooms[new_y][new_x]) {
            int x_wall = x * 2 + 1 + x_dirs[dir];
            int y_wall = y * 2 + 1 + y_dirs[dir];

            labyrinth[y_wall][x_wall] = PATH;
            gen_labyrinth(new_x, new_y, visited_rooms, labyrinth);
        }
    }
}

int count_walls(char labyrinth[LABYRINTH_LENGTH][LABYRINTH_LENGTH]) {
    int walls_counter = 0;

    for (int i = 0; i < LABYRINTH_LENGTH; i++)
        for (int j = 0; j < LABYRINTH_LENGTH; j++)
            if (labyrinth[i][j] == WALL)
                walls_counter++;

    return walls_counter;
}

void add_walls(char labyrinth[LABYRINTH_LENGTH][LABYRINTH_LENGTH]) {
    int labyrinth_area = LABYRINTH_LENGTH * LABYRINTH_LENGTH;
    int walls_counter = count_walls(labyrinth);

    while (walls_counter < labyrinth_area * 15 / 100) {
        int i = rand() % (LABYRINTH_LENGTH - 2) + 1;
        int j = rand() % (LABYRINTH_LENGTH - 2) + 1;

        if (i % 2 != 0 && j % 2 != 0 || labyrinth[i][j] == WALL)
            continue;

        labyrinth[i][j] = WALL;

        int walls_around_counter = 0;
        int i_dirs[4] = {0, 1, 0, -1};
        int j_dirs[4] = {1, 0, -1, 0};

        for (int k = 0; k < 4; k++) {
            int new_i = i + i_dirs[k];
            int new_j = j + j_dirs[k];

            if (valid_coords(new_i, new_j, LABYRINTH_LENGTH))
                if (labyrinth[new_i][new_j] == WALL)
                    walls_around_counter++;
        }

        if (walls_around_counter < 3) {
            walls_counter++;
        } else {
            labyrinth[i][j] = PATH;
        }
    }
}

void print_labyrinth(char labyrinth[LABYRINTH_LENGTH][LABYRINTH_LENGTH]) {
    for (int i = 0; i < LABYRINTH_LENGTH; i++) {
        for (int j = 0; j < LABYRINTH_LENGTH; j++)
            printf("%c", labyrinth[i][j]);
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    char labyrinth[LABYRINTH_LENGTH][LABYRINTH_LENGTH];
    init_labyrinth(labyrinth);

    bool visited_rooms[ROOMS_NUM][ROOMS_NUM] = {false};
    gen_labyrinth(0, 0, visited_rooms, labyrinth);

    add_walls(labyrinth);

    print_labyrinth(labyrinth);

    return 0;
}
