#include "graphics/gfxdevice.h"
#include "minecraft.h"

typedef struct
{
    int w, h;
    bool vsync;
} GraphicsDevice;
static GraphicsDevice _gfxdev;

void GfxInit()
{
    XVideoSetMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, REFRESH_DEFAULT);
    DbgWriteLine("Set video mode to %dx%dx32bpp", SCREEN_WIDTH, SCREEN_HEIGHT);

    int res = pb_init();
    if (res != 0) { DbgError("Error initializing pbkit - %d", res); return; }
    pb_show_front_screen();

    memset(&_gfxdev, 0, sizeof(GraphicsDevice));
    _gfxdev.w = (int)pb_back_buffer_width();
    _gfxdev.h = (int)pb_back_buffer_height();
    _gfxdev.vsync = false;

    GfxInitShader();

    DbgWriteLine("Initialized graphics device");
    Sleep(500);
    pb_show_front_screen();
}

void GfxInitShader()
{
    uint32_t vs_program[] = 
    {
        #include "../assets/shaders/vertex.inl"
    };

    uint32_t shader_args = MASK(NV097_SET_TRANSFORM_EXECUTION_MODE_MODE, NV097_SET_TRANSFORM_EXECUTION_MODE_MODE_PROGRAM) | 
                           MASK(NV097_SET_TRANSFORM_EXECUTION_MODE_RANGE_MODE, NV097_SET_TRANSFORM_EXECUTION_MODE_RANGE_MODE_PRIV);

    uint32_t* p = pb_begin();
    p = pb_push1(p, NV097_SET_TRANSFORM_PROGRAM_START, 0);
    p = pb_push1(p, NV097_SET_TRANSFORM_EXECUTION_MODE, shader_args);
    p = pb_push1(p, NV097_SET_TRANSFORM_PROGRAM_CXT_WRITE_EN, 0);
    pb_end(p);

    p = pb_begin();
    p = pb_push1(p, NV097_SET_TRANSFORM_PROGRAM_LOAD, 0);
    pb_end(p);

    for (int i = 0; i < sizeof(vs_program) / 16; i++) 
    {
        p = pb_begin();
        pb_push(p++, NV097_SET_TRANSFORM_PROGRAM, 4);
        memcpy(p, &vs_program[i * 4], 4 * 4);
        p += 4;
        pb_end(p);
    }
    DbgWriteLine("Initialized vertex shader");

    p = pb_begin();
    #include "../assets/shaders/pixel.inl"
    pb_end(p);
    DbgWriteLine("Initialized pixel shader");    
}

void GfxClear(Color color)
{
    if (_gfxdev.vsync) { pb_wait_for_vbl(); }
    pb_reset();
    pb_target_back_buffer();
    pb_erase_depth_stencil_buffer(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    pb_fill(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, *((uint32_t*)&color));
    pb_erase_text_screen();
    while (pb_busy());
}

void GfxDisplay()
{
    while (pb_busy());
    if (_gfxdev.vsync) { while (pb_finished()) { } return; }
    pb_finished();
}

void GfxToggleVSync(bool enabled)
{
    _gfxdev.vsync = enabled;
}

void GfxSetConstant(uint32_t reg, size_t reg_count, const void* data)
{
    size_t sz = reg_count * 4;

    uint32_t* p = pb_begin();
    p = pb_push1(p, NV097_SET_TRANSFORM_CONSTANT_LOAD, 96 + reg);

    pb_push(p++, NV097_SET_TRANSFORM_CONSTANT, sz);
    memcpy(p, data, sz * sizeof(float)); 
    p += sz;
    pb_end(p);
}

void GfxSetAttributePointer(uint32_t index, uint32_t fmt, uint32_t sz, uint32_t stride, const void* data)
{
    DWORD flags = MASK(NV097_SET_VERTEX_DATA_ARRAY_FORMAT_TYPE, fmt) | MASK(NV097_SET_VERTEX_DATA_ARRAY_FORMAT_SIZE, sz) | MASK(NV097_SET_VERTEX_DATA_ARRAY_FORMAT_STRIDE, stride);

    uint32_t *p = pb_begin();
    p = pb_push1(p, NV097_SET_VERTEX_DATA_ARRAY_FORMAT + index * 4, flags);
    p = pb_push1(p, NV097_SET_VERTEX_DATA_ARRAY_OFFSET + index * 4, (uint32_t)data & 0x03FFFFFF);
    pb_end(p);
}

void GfxDrawArrays(uint32_t mode, int start, int count)
{
    uint32_t *p = pb_begin();
    p = pb_push1(p, NV097_SET_BEGIN_END, mode);
    p = pb_push1(p, 0x40000000 | NV097_DRAW_ARRAYS, MASK(NV097_DRAW_ARRAYS_COUNT, (count - 1)) | MASK(NV097_DRAW_ARRAYS_START_INDEX, start));
    p = pb_push1(p, NV097_SET_BEGIN_END, NV097_SET_BEGIN_END_OP_END);
    pb_end(p);
}

Point GetScreenSize()
{
    Point p = (Point){ _gfxdev.w, _gfxdev.h };
    return p;
}