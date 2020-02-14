typedef struct rectangle{
    int x;
    int y;
    int w;
    int h;
}rectangle;

typedef struct anim anim_t;


struct anim *MK_create_anim(S2D_Sprite *sp);
void MK_free_anim(struct anim *anm);

void MK_add_anim_clip(anim_t *anm, rectangle rect);
void MK_start_anim(struct anim *anm, int period);
void MK_stop_anim(struct anim *anm);
void MK_pause_anim(struct anim *anm);
void MK_resume_anim(struct anim *anm);
void MK_change_anim_period(struct anim *anm, int period);

S2D_Sprite *MK_get_anim_sprite(anim_t *anm);