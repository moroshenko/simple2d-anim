# simple2d-anim
it is simple 2d anim lib for simple2d: https://github.com/simple2d/simple2d
sample:

```c
#include <stdio.h>
#include <stdlib.h>
#include <simple2d.h>

#include "main.h"
#include "anim.h"


S2D_Window *WIN;
S2D_Sprite *sprite;
anim_t *ANIM;
anim_t *ANIM2;

int main(int argc, char *argv[]){



    sprite = S2D_CreateSprite("some_spritesheet.png");

    rectangle r1 = {0, 0, 150, 200};
    rectangle r2 = {150, 200, 150, 200};

    ANIM = MK_create_anim(sprite);
    MK_add_anim_clip(ANIM, r1);
    MK_add_anim_clip(ANIM, r2);

    ANIM2 = MK_create_anim(sprite);
    MK_add_anim_clip(ANIM2, r1);
    MK_add_anim_clip(ANIM2, r2);

    MK_start_anim(ANIM, 500);
    MK_start_anim(ANIM2, 1000);

    WIN = S2D_CreateWindow("EXAMPLE",800, 600, update, render, S2D_BORDERLESS);
    WIN->background.r = 1;
    WIN->background.g = 1;
    WIN->background.b = 1;
    WIN->background.a = 1;
    WIN->on_key = on_key;

    S2D_Show(WIN);

    S2D_FreeWindow(WIN);
    return 0;
}

void update(){
}

void render(){
    S2D_Sprite *sp = MK_get_anim_sprite(ANIM);
    S2D_Sprite *sp2 = MK_get_anim_sprite(ANIM2);

    sp->x = 200;
    sp->y = 400;
    sp2->x = 400;
    sp2->y = 400;

    S2D_DrawSprite(sp);
    S2D_DrawSprite(sp2);     
}

void on_key(S2D_Event e) {
    if(e.type == S2D_KEY_UP){
        if(!strcmp(e.key, "Escape")) //For exit. Because we use window without borders(ma engl wery bed)
            exit(0);
        switch (*e.key)
        {
        case 'Q':
            MK_pause_anim(ANIM);
            break;
        case 'E':
            MK_resume_anim(ANIM);
            break;
        case 'A':
            MK_pause_anim(ANIM2);
            break;
        case 'D':
            MK_resume_anim(ANIM2);
            break;
        default:
            break;
        }
    }
}
```
