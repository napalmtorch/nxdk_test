#include "math/vector3.h"
#include "minecraft.h"

bool VectorEquals3(Vector3 v1, Vector3 v2) { return v1.x == v2.x && v1.y == v2.y; }

bool VectorEquals3p(Vector3* v1, Vector3* v2) { return v1->x == v2->x && v1->y == v2->y; }

void VectorAdd3(Vector3* v_out, Vector3 v1, Vector3 v2) { *v_out = (Vector3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }; }

void VectorAdd3p(Vector3* v_out, Vector3* v1, Vector3* v2) { *v_out = (Vector3){ v1->x + v2->x, v1->y + v2->y, v1->z + v2->z }; }

void VectorAdd3f(Vector3* v_out, Vector3* v1, float factor) { *v_out = (Vector3){ v1->x + factor, v1->y + factor, v1->z + factor }; }

void VectorSub3(Vector3* v_out, Vector3 v1, Vector3 v2) { *v_out = (Vector3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }; }

void VectorSub3p(Vector3* v_out, Vector3* v1, Vector3* v2) { *v_out = (Vector3){ v1->x - v2->x, v1->y - v2->y, v1->z - v2->z }; }

void VectorSub3f(Vector3* v_out, Vector3* v1, float factor) { *v_out = (Vector3){ v1->x - factor, v1->y - factor, v1->z - factor }; }

void VectorMul3(Vector3* v_out, Vector3 v1, Vector3 v2) { *v_out = (Vector3){ v1.x * v2.x, v1.y * v2.y, v1.z * v2.z }; }

void VectorMul3p(Vector3* v_out, Vector3* v1, Vector3* v2) { *v_out = (Vector3){ v1->x * v2->x, v1->y * v2->y, v1->z * v2->z }; }

void VectorMul3f(Vector3* v_out, Vector3* v1, float factor) { *v_out = (Vector3){ v1->x * factor, v1->y * factor, v1->z * factor }; }

void VectorDiv3(Vector3* v_out, Vector3 v1, Vector3 v2) { *v_out = (Vector3){ v1.x / v2.x, v1.y / v2.y, v1.z / v2.z }; }

void VectorDiv3p(Vector3* v_out, Vector3* v1, Vector3* v2) { *v_out = (Vector3){ v1->x / v2->x, v1->y / v2->y, v1->z / v2->z }; }

void VectorDiv3f(Vector3* v_out, Vector3* v1, float factor) { *v_out = (Vector3){ v1->x / factor, v1->y / factor, v1->z / factor }; }

void VectorCross3(Vector3* v_out, Vector3 v1, Vector3 v2)
{
    *v_out = (Vector3)
    {
        (v1.x * v2.z) - (v1.z * v2.x),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x)
    };
}

void VectorCross3p(Vector3* v_out, Vector3* v1, Vector3* v2)
{
    *v_out = (Vector3)
    {
        (v1->x * v2->z) - (v1->z * v2->x),
        (v1->z * v2->x) - (v1->x * v2->z),
        (v1->x * v2->y) - (v1->y * v2->x)
    };
}

float VectorDot3(Vector3 v1, Vector3 v2) { return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z); }

float VectorDot3p(Vector3* v1, Vector3* v2) { return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z); }

void VectorNormalize3(Vector3* v_out, Vector3 v)
{
    *v_out = v;

    float len = VectorLength3p(&v);
    if (len != 0)
    {
        float inv = 1.0f / len;
        v_out->x *= inv;
        v_out->y *= inv;
        v_out->z *= inv;
    }
}

void VectorNormalize3p(Vector3* v_out, Vector3* v)
{
    *v_out = *v;

    float len = VectorLength3p(v);
    if (len != 0)
    {
        float inv = 1.0f / len;
        v_out->x *= inv;
        v_out->y *= inv;
        v_out->z *= inv;
    }
}

float VectorDistance3(Vector3 v1, Vector3 v2)
{
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;
    float z = v1.z - v2.z;
    return sqrtf((x * x) + (y * y) + (z * z));
}

float VectorDistance3p(Vector3* v1, Vector3* v2)
{
    float x = v1->x - v2->x;
    float y = v1->y - v2->y;
    float z = v1->z - v2->z;
    return sqrtf((x * x) + (y * y) + (z * z));
}

float VectorLength3(Vector3 v) { return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }

float VectorLength3p(Vector3* v) { return sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z)); }

void VectorToArray3(float* arr_out, Vector3* v)
{
    arr_out[0] = v->x;
    arr_out[1] = v->y;
    arr_out[2] = v->z;
}