#include <stdio.h>
#include <stdlib.h>
#include <simple2d.h>
#include <pthread.h>

#include "anim.h"



typedef struct anim{
    int tiles; 
    int pertiod;
    S2D_Sprite *sprite;
    rectangle rect[30];
    bool state;
    int tile;
    pthread_t thread;
    bool stop;
}anim_t;

/*EXAMPLE *n = 3, x = 4, min = 0, max = 4:*/
/* 3 + 3 = 6 --> >4 --> 6 - 4 - 1  = 1*/
void up(int *n, int x, int min, int max){
    if(*n + x <= max)
    {
        *n += x;
        return;
    }
    else
    {
        *n = (*n+x) - max;
        return;
    }
    
}

/*EXAMPLE *n = 3, x = 4, min = 0, max = 10:*/
/* 3 - 4 = -1 --> <0 --> 10 + 1  + (-1) = 10*/
void down(int *n, int x, int min, int max){
    if(*n - x >= min)
    {
        *n -= x;
        return;
    }
    else
    {
        *n = (*n-x) + max;
    }
    
}

void *_update_anim(void *animation){
    struct anim *anm = (struct anim *)animation;
    while(1){
        if(anm->state){
            //NO/*rect it dunamic array, and I |werry| smart*/
            up(&anm->tile, 1, 0, anm->tiles);
            
            

            rectangle r = anm->rect[anm->tile-1];
            S2D_ClipSprite(anm->sprite, r.x, r.y, r.w, r.h);

            printf("%i, %i, \n", anm->tile, anm->tiles);
            usleep(anm->pertiod*1000);//microseconds to milliseconds

        }
        if(anm->stop)
            return NULL;
    }

    return NULL;
}

/*allocales memory for the animation structure*/
struct anim *MK_create_anim(S2D_Sprite *sp){
    struct anim *anim_ = malloc(sizeof(anim_t));
    anim_->sprite = S2D_CreateSprite(sp->path);
    anim_->pertiod = 0;
    anim_->tiles = 0;
    anim_->tile = 0;
    anim_->state = 0;
    anim_->stop = 0;
}

/*Free all used memory*/
void MK_free_anim(struct anim *anm){
    MK_stop_anim(anm);
    free(anm);
    
}

void MK_add_anim_clip(anim_t *anm, rectangle rect){
    
    anm->rect[anm->tiles] = rect;
    anm->tiles++;
}

void MK_start_anim(struct anim *anm, int period){
    anm->state = 1;
    anm->pertiod  = period;
    pthread_create(&anm->thread, NULL, _update_anim, (void *)anm);

}

S2D_Sprite *MK_get_anim_sprite(anim_t *anm){
    return anm->sprite;
}

void MK_stop_anim(struct anim *anm){
    void *ret;
    anm->state = 0;
    anm->stop = 1;
    pthread_join(anm->thread, &ret);
}

void MK_pause_anim(struct anim *anm){
    anm->state = 0;
}

void MK_resume_anim(struct anim *anm){
    anm->state = 1;
}

void MK_change_anim_period(struct anim *anm, int period){
    anm->pertiod = period;
}


