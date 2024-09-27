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

//void update_state(int *game_state, vec2 size)
//{
        
//}

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
                        //update_state(game_state, size);
                        write_state(grid, game_state, size);
                        return;
                        case 2:
                        deallocate(game_state);
                }
        }
}
