#include "djui.h"

  ////////////
 // events //
////////////

void djui_rect_render(struct DjuiBase* base) {
    struct DjuiBaseRect* clip = &base->clip;

    // translate position
    f32 translatedX = clip->x;
    f32 translatedY = clip->y;
    djui_gfx_position_translate(&translatedX, &translatedY);
    create_dl_translation_matrix(DJUI_MTX_PUSH, translatedX, translatedY, 0);

    // translate size
    f32 translatedWidth  = clip->width;
    f32 translatedHeight = clip->height;
    djui_gfx_scale_translate(&translatedWidth, &translatedHeight);
    create_dl_scale_matrix(DJUI_MTX_NOPUSH, translatedWidth, translatedHeight, 1.0f);

    // render
    gDPSetEnvColor(gDisplayListHead++, base->color.r, base->color.g, base->color.b, base->color.a);
    gSPDisplayList(gDisplayListHead++, dl_djui_simple_rect);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

static void djui_rect_destroy(struct DjuiBase* base) {
    struct DjuiRect* rect = (struct DjuiRect*)base;
    free(rect);
}

struct DjuiRect* djui_rect_create(struct DjuiBase* parent) {
    struct DjuiRect* rect = malloc(sizeof(struct DjuiRect));
    struct DjuiBase* base = &rect->base;

    djui_base_init(parent, base, djui_rect_render, djui_rect_destroy);

    return rect;
}
