#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <unistd.h>
#include <stdlib.h>

#define REC_SQRT2 0.7071067811865475 

enum input_state
{
    NOTHING_PRESSED = 0,
    UP_PRESSED = 1,
    DOWN_PRESSED = 1<<1,
    LEFT_PRESSED = 1<<2,
    RIGHT_PRESSED = 1<<3
};

struct context
{
    SDL_Renderer *renderer;

    SDL_Rect destination;
    SDL_Texture *texture;

    enum input_state active_state;

    int vx;
    int vy;
};

/**
 * Loads the image located at 'fileName' and copies it to the
 * renderer 'renderer'
 */
int get_texture(struct context *ctx, const char *fileName)
{
    SDL_Surface *image = IMG_Load(fileName);
    if (!image)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        return 0;
    }

    ctx->texture = SDL_CreateTextureFromSurface(ctx->renderer, image);
    ctx->destination.w = image->w;
    ctx->destination.h = image->h;

    SDL_FreeSurface(image);

    return 1;
}

void process_input(struct context *ctx)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->active_state |= UP_PRESSED;
                else if (event.key.type == SDL_KEYUP)
                    ctx->active_state ^= UP_PRESSED;
                break;
            case SDLK_DOWN:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->active_state |= DOWN_PRESSED;
                else if (event.key.type == SDL_KEYUP)
                    ctx->active_state ^= DOWN_PRESSED;
                break;
            case SDLK_LEFT:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->active_state |= LEFT_PRESSED;
                else if (event.key.type == SDL_KEYUP)
                    ctx->active_state ^= LEFT_PRESSED;
                break;
            case SDLK_RIGHT:
                if (event.key.type == SDL_KEYDOWN)
                    ctx->active_state |= RIGHT_PRESSED;
                else if (event.key.type == SDL_KEYUP)
                    ctx->active_state ^= RIGHT_PRESSED;
                break;
            default:
                break;
        }
    }

    ctx->vy = 0;
    ctx->vx = 0;
    if (ctx->active_state & UP_PRESSED)
        ctx->vy = -5;
    if (ctx->active_state & DOWN_PRESSED)
        ctx->vy = 5;
    if (ctx->active_state & LEFT_PRESSED)
        ctx->vx = -5;
    if (ctx->active_state & RIGHT_PRESSED)
        ctx->vx = 5;

    if (ctx->vx != 0 && ctx->vy != 0)
    {
        ctx->vx *= REC_SQRT2;
        ctx->vy *= REC_SQRT2;
    }
}

void loop_handler(void *arg)
{
    struct context *ctx = arg;

    int vx = 0;
    int vy = 0;
    process_input(ctx);

    ctx->destination.x += ctx->vx;
    ctx->destination.y += ctx->vy;

    SDL_RenderClear(ctx->renderer);
    SDL_RenderCopy(ctx->renderer, ctx->texture, NULL, &ctx->destination);
    SDL_RenderPresent(ctx->renderer);
}

int main()
{
    SDL_Window *window;
    struct context ctx;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(600, 400, 0, &window, &ctx.renderer);

    int result = 0;

    SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 255, 255);

    get_texture(&ctx, "03_assets/images/Character.png");

    emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);

    return 0;
}
