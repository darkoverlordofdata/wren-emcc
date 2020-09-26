/* nuklear - 1.40.8 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include <corefw/corefw.h>
#include <wren.h>
#include <tglm/tglm.h>
#include "wc/wc.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GLES2_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gles2.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define UNUSED(a) (void)a
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a) / sizeof(a)[0])

CFWRefPool* pool;
WCScript* script;
WCMethod* hello_world;
WCMethod* vectorx;

/* Platform */
SDL_Window* win;
int running = nk_true;

/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the include
 * and the corresponding function. */
/*#include "../style.c"*/
/*#include "../calculator.c"*/
/*#include "../overview.c"*/
/*#include "../node_editor.c"*/
/* nuklear - v1.00 - public domain */
static void
calculator(struct nk_context* this)
{
    if (nk_begin(this, "Calculator", nk_rect(10, 10, 180, 250),
            NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_MOVABLE)) {
        static int set = 0, prev = 0, op = 0;
        static const char numbers[] = "789456123";
        static const char ops[] = "+-*/";
        static double a = 0, b = 0;
        static double* current = &a;

        size_t i = 0;
        int solve = 0;
        {
            int len;
            char buffer[256];
            nk_layout_row_dynamic(this, 35, 1);
            len = snprintf(buffer, 256, "%.2f", *current);
            nk_edit_string(this, NK_EDIT_SIMPLE, buffer, &len, 255, nk_filter_float);
            buffer[len] = 0;
            *current = atof(buffer);
        }

        nk_layout_row_dynamic(this, 35, 4);
        for (i = 0; i < 16; ++i) {
            if (i >= 12 && i < 15) {
                if (i > 12)
                    continue;
                if (nk_button_label(this, "C")) {
                    a = b = op = 0;
                    current = &a;
                    set = 0;
                }
                if (nk_button_label(this, "0")) {
                    *current = *current * 10.0f;
                    set = 0;
                }
                if (nk_button_label(this, "=")) {
                    solve = 1;
                    prev = op;
                    op = 0;
                }
            } else if (((i + 1) % 4)) {
                if (nk_button_text(this, &numbers[(i / 4) * 3 + i % 4], 1)) {
                    *current = *current * 10.0f + numbers[(i / 4) * 3 + i % 4] - '0';
                    set = 0;
                }
            } else if (nk_button_text(this, &ops[i / 4], 1)) {
                if (!set) {
                    if (current != &b) {
                        current = &b;
                    } else {
                        prev = op;
                        solve = 1;
                    }
                }
                op = ops[i / 4];
                set = 1;
            }
        }
        if (solve) {
            if (prev == '+')
                a = a + b;
            if (prev == '-')
                a = a - b;
            if (prev == '*')
                a = a * b;
            if (prev == '/')
                a = a / b;
            current = &a;
            if (set)
                current = &b;
            b = 0;
            set = 0;
        }
    }
    nk_end(this);
}
static void
draw_window(struct nk_context* this)
{
    float bgd_r = 0.392156f;
    float bgd_g = 0.584313f;
    float bgd_b = 0.929411f;
    float bg[4];
    int win_width, win_height;
    // nk_color_fv(bg, nk_rgb(28, 48, 62));
    nk_color_fv(bg, nk_rgb(bgd_r*256, bgd_g*256, bgd_b*256));
    SDL_GetWindowSize(win, &win_width, &win_height);
    glViewport(0, 0, win_width, win_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(bg[0], bg[1], bg[2], bg[3]);
    /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
    * with blending, scissor, face culling, depth test and viewport and
    * defaults everything back into a default state.
    * Make sure to either a.) save and restore or b.) reset your own state after
    * rendering the UI. */
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
    SDL_GL_SwapWindow(win);
}
static void
main_window(struct nk_context* this)
{
    /* GUI */
    if (nk_begin(this, "Demo", nk_rect(250, 10, 300, 300),
            NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        enum { EASY,
            HARD };
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(this, 30, 80, 1);
        if (nk_button_label(this, "click me")) {
            fprintf(stdout, "%s\n", wc_method_str(hello_world));
        }
        nk_layout_row_dynamic(this, 30, 2);
        if (nk_option_label(this, "easy", op == EASY))
            op = EASY;
        if (nk_option_label(this, "hard", op == HARD))
            op = HARD;
        nk_layout_row_dynamic(this, 25, 1);
        nk_property_int(this, "Compression:", 0, &property, 100, 10, 1);
    }
    nk_end(this);

}
/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
static void
event_handler(struct nk_context* this)
{
    /* Input */
    SDL_Event evt;
    nk_input_begin(this);
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT)
            running = nk_false;
        nk_sdl_handle_event(&evt);
    }
    nk_input_end(this);


}
static void
MainLoop(void* loopArg)
{
    struct nk_context* this = (struct nk_context*)loopArg;

    event_handler(this);
    main_window(this);
    /* -------------- EXAMPLES ---------------- */
    calculator(this);
    /*overview(this);*/
    /*node_editor(this);*/
    /* ----------------------------------------- */
    draw_window(this);
}

int main(int argc, char* argv[])
{
    pool = cfw_new(cfw_refpool);
    script = cfw_create(wc_script, &builtIns);
    wc_execute_module(script, "test");
    hello_world = cfw_create(wc_method, script, "test", "Main", "helloWorld()");
    vectorx = cfw_create(wc_method, script, "test", "test", "vectorx()");

    /* GUI */
    struct nk_context* this;
    SDL_GLContext glContext;
    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    /*SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS); // - do NOT init SDL on GL ES 2 */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    win = SDL_CreateWindow("Demo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    glContext = SDL_GL_CreateContext(win);

    /* OpenGL setup */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    this = nk_sdl_init(win);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {
        struct nk_font_atlas* atlas;
        nk_sdl_font_stash_begin(&atlas);
        struct nk_font* droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);
        // struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);
        // struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);
        /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
        /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
        /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
        nk_sdl_font_stash_end();
        /*nk_style_load_all_cursors(this, atlas->cursors);*/
        /*nk_style_set_font(this, &roboto->handle)*/;
    }

    /* style.c */
    /*set_style(this, THEME_WHITE);*/
    /*set_style(this, THEME_RED);*/
    /*set_style(this, THEME_BLUE);*/
    /*set_style(this, THEME_DARK);*/

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
    emscripten_set_main_loop_arg(MainLoop, (void*)this, 0, nk_true);
#else
    while (running)
        MainLoop((void*)this);
#endif

    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    cfw_unref(pool);
    return 0;
}
