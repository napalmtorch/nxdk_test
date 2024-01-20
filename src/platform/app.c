#include "platform/app.h"
#include "minecraft.h"

static uint32_t *alloc_vertices;
static uint32_t  num_vertices;
static Matrix    m_viewport, m_view, m_proj, m_wvp;
static Vector3   v_pos, v_lookdir, v_up;

typedef struct {
    float pos[3];
    float color[3];
} __attribute__((packed)) ColoredVertex;

static const ColoredVertex verts[] = {
    {{-1.0, -1.0,  1.0}, { 1.0,  0.0,  0.0 }}, /* Foreground triangle */
    {{ 0.0,  1.0,  1.0}, { 0.0,  1.0,  0.0 }},
    {{ 1.0, -1.0,  1.0}, { 0.0,  0.0,  1.0 }},
};

static int _fps = 0;

void ApplicationInit()
{
    InputInit();
    GfxInit();
    
    alloc_vertices = MmAllocateContiguousMemoryEx(sizeof(verts), 0, 0x3ffb000, 0, 0x404);
    memcpy(alloc_vertices, verts, sizeof(verts));
    num_vertices = sizeof(verts)/sizeof(verts[0]);

    v_pos     = (Vector3){ -5.0f, 0.0f, -10.0f };
    v_lookdir = (Vector3){ 0.0f, 0.0f, 0.0f };
    v_up      = (Vector3){ 0.0f, 1.0f, 0.0f };
}

void ApplicationDispose()
{
    pb_show_debug_screen();
    pb_kill();
}

void ApplicationRun()
{
    SDL_Event event;
    int frames, last, now, start;
    start = now = last = GetTickCount();

    while (true)
    {
        GfxClear((Color){ 0x00, 0x2F, 0x2F, 0xFF });

        Matrix m_world;
        MatrixIdentity(&m_world);
        MatrixPerspectiveFovLH(&m_proj, 90.0f * M_PI / 180.0f, SCREEN_WIDTH / SCREEN_HEIGHT, 0.01f, 1000.0f);
        MatrixLookAtLH(&m_view, &v_pos, &v_lookdir, &v_up);
        
        MatrixIdentity(&m_wvp);
        MatrixMultiply(&m_wvp, &m_view, &m_proj);
        MatrixMultiply(&m_wvp, &m_wvp, &m_world);
        GfxSetConstant(0, 4, m_wvp.m);

        //MatrixOrthoLH(&m_viewport, 0, 0, GetScreenSize().x, GetScreenSize().y, -1.0f, 1.0f);
        //GfxSetConstant(0, 4, m_viewport.m);

        uint32_t* p = pb_begin();
        pb_push(p++, NV097_SET_VERTEX_DATA_ARRAY_FORMAT,16);
        for(int i = 0; i < 16; i++) { *(p++) = NV097_SET_VERTEX_DATA_ARRAY_FORMAT_TYPE_F; }
        pb_end(p);

        GfxSetAttributePointer(0, NV097_SET_VERTEX_DATA_ARRAY_FORMAT_TYPE_F, 3, sizeof(ColoredVertex), &alloc_vertices[0]);
        GfxSetAttributePointer(3, NV097_SET_VERTEX_DATA_ARRAY_FORMAT_TYPE_F, 3, sizeof(ColoredVertex), &alloc_vertices[3]);
        GfxDrawArrays(NV097_SET_BEGIN_END_OP_TRIANGLES, 0, num_vertices);
        
        pb_print("%d FPS", _fps);
        pb_draw_text_screen();

        GfxDisplay();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_CONTROLLERDEVICEADDED)
            {
                SDL_GameController* dev = SDL_GameControllerOpen(event.cdevice.which);
                DbgWriteLine("CONTROLLER CONNECTED");
            }
            else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
            {
                SDL_GameControllerClose(SDL_GameControllerFromInstanceID(event.cdevice.which));
            }
            else if (event.type == SDL_CONTROLLERAXISMOTION)
            {
                DbgWriteLine("AXIS");
            }
            else if (event.type == SDL_CONTROLLERBUTTONDOWN)
            {
                DbgWriteLine("BUTTON DOWN");
            }
            else if (event.type == SDL_CONTROLLERBUTTONUP)
            {

            }
        }
        SDL_GameControllerUpdate();
        
        frames++;
        now = GetTickCount();
        if ((now - last) > 1000) 
        {
            _fps   = frames;
            frames = 0;
            last   = now;
        }
    }
}

int GetFramesPerSecond() { return _fps; }