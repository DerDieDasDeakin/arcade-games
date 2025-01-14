//compile by running skm clang++ program.cpp -o SingleCombat

#include "splashkit.h"
#include <vector>
using namespace std;

/* CONTROLS INFO
According to https://github.com/thoth-tech/arcade-games
Player One
Up: W | Left: A | Down S | Right: D Weak(1): R | Weak(2): F Med(1) : T | Med(2) : G Hard(1): Y | Hard(2): H

Player Two
Up: UP_ARROW | Left: LEFT_ARROW | Down: DOWN_ARROW | Right: RIGHT_ARROW Weak(1): U | Weak(2): J Med(1) : I | Med(2) : K Hard(1): O | Hard(2): L

General
Start: ENTER 
Escape: ESC
*/


void load_resources()
{
    
    load_resource_bundle("game_bundle", "game_bundle.txt");
}


int main()
{
    //max window size 1600 x 900 for Arcade Machine. Minimum 640 x 480
    /*window size of 576 x 864 calibrated to allow for board of 288w x 864h dimensions + some extra space. Dimensions based on blocks that are 75%
    of the original size, so are 48w x 72h. This board can thus fit 12 vertically and 6 horizontally. */
    open_window("Single Combat", 576, 900);
    
    //variable to define edge of the playing board.
    int boardLeftEdge = 144;
    int boardRightEdge = 288;

    //this will vary based on where the bottom of any particular column is, as blocks are stacked;
    int boardBottomEdge = 882;

    //window_toggle_border("Single Combat"); uncomment this when ready for arcade
    load_resources();

    //create sprite
    sprite GreenBlockSprite = create_sprite("greenblock.png");

        //At 75% size (48w x 72h), can easily fit 12 blocks vertically, and plenty of space for 6 horizontally for 2 player screens. Could get away with a bit larger if needed down the track
        //Scaling down for the current art distorts slightly, this will be fine for testing purposes but worth fixing in future (need art with less pixels)
        sprite_set_scale(GreenBlockSprite, 0.75);
        //set start location of sprite, should spawn in 3rd column across
        //Note that the scale down means that the block start is not actually 0, 0. It's offset by 12.5%, so -8 and -12). Will be better to adjust art so that there's no need to scale
        sprite_set_x(GreenBlockSprite, 232);
        sprite_set_y(GreenBlockSprite, 6);
        sprite_set_dx(GreenBlockSprite, 1);
        sprite_set_dy(GreenBlockSprite, 1);
        sprite_set_heading(GreenBlockSprite, 90);
    
        
            
    while (!key_typed(ESCAPE_KEY) && !quit_requested())
    {
        process_events();
        clear_screen(COLOR_WHITE);
        update_sprite(GreenBlockSprite);
        fill_rectangle(COLOR_BLACK, 144, 18, 288, 864);
        draw_sprite(GreenBlockSprite);
        refresh_screen(60);

        //lets block move left if not at edge of board
        if (key_typed(A_KEY))
        {
            if (sprite_x(GreenBlockSprite) > boardLeftEdge)
            {
                sprite_set_x(GreenBlockSprite, (sprite_x(GreenBlockSprite) - 48));
            }

        }

        //lets block move right if not at edge of board
        if (key_typed(D_KEY))
        {

            if (sprite_x(GreenBlockSprite) < boardRightEdge + 48)
            {
                sprite_set_x(GreenBlockSprite, (sprite_x(GreenBlockSprite) + 48));
            }
            
        }

        //speeds descent of block, can't be undone
        if (key_typed(S_KEY))
        {
            sprite_set_speed(GreenBlockSprite, 10);
        }

        //sprite stops when it reaches the end of the board
        if (sprite_y(GreenBlockSprite) >= boardBottomEdge - 90)
            {
                sprite_set_speed(GreenBlockSprite, 0);
            } 
    

    }
    return 0;
}