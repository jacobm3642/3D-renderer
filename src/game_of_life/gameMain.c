#include "dataTypes.h"
#include "rendeing.h"
#include "object_handleing.h"
#include "engine_internal.h"

bool vec4_check(vec4 v1, vec4 v2)
{
        if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z) {
                return true;
        }
        return false;
}

int *init_game_state(Objnode **grid, vec2 size) 
{
        vec4 bl = {0, 0, 0, 1};
        int *game_state = allocate(sizeof(int) * size.x * size.y);
        for (int i = 0; i < size.x * size.y; i++) {
                if (vec4_check(grid[i]->obj->color, bl)) {
                        game_state[i] = 0;
                } else {
                        game_state[i] = 1;
                }
        }
        return game_state;
}

int check_cell(int *game_state, vec2 size, int i)
{
    int count = 0;
    int width = size.x;
    int height = size.y;

    int row = i / width;
    int col = i % width;

    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (r == row && c == col) continue;

            if (r >= 0 && r < height && c >= 0 && c < width) {
                count += game_state[r * width + c];
            }
        }
    }

    return count;
}

void update_state(int *game_state, vec2 size)
{
        int kill[1000] = {0};
        int k = 0;
        int alive[1000] = {0};
        int l = 0;
        for (int i = 0; i < size.x * size.y; i++) {
                int count = check_cell(game_state, size, i);
                if (game_state[i] == 1) {
                        if (count < 2) {
                                kill[k] = i;
                                k++;
                        }
                        if (count > 3) {
                                kill[k] = i;
                                k++;
                        }
                } else {
                        if (count == 3) {

                                alive[l] = game_state[i];
                                l++;
                        }
                }
        }
        for (int i = 0; i < k; i++) {
                game_state[kill[i]] = 0;
        }
        for (int i = 0;i < l; i++) {
                game_state[alive[i]] = 1;
        }
}

void write_state(Objnode **grid, int *game_state, vec2 size)
{
        vec4 wi = {1, 1, 1, 1};
        vec4 bl = {0, 0, 0, 1};
        for (int i = 0; i < size.x * size.y; i++) {
                if (game_state[i] == 0) {
                        grid[i]->obj->color = bl;
                } else if (game_state[i] == 1) {
                        grid[i]->obj->color = wi;
                }
        }
}

void game_of_life(Objnode **grid, vec2 size)
{
        static char state = 0;
        static int *game_state;
        switch (state) {
                for (;;) {
                        case 0:
                        game_state = init_game_state(grid, size);
                        state = 1;
                        case 1:
                        update_state(game_state, size);
                        write_state(grid, game_state, size);
                        return;
                        case 2:
                        deallocate(game_state);
                }
        }
}
