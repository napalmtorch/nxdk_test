#pragma once
#include "platform/common.h"

typedef struct
{
    float x, y, z;
} Vector3;

bool VectorEquals3(Vector3 v1, Vector3 v2);
bool VectorEquals3p(Vector3* v1, Vector3* v2);

void VectorAdd3(Vector3* v_out, Vector3 v1, Vector3 v2);
void VectorAdd3p(Vector3* v_out, Vector3* v1, Vector3* v2);
void VectorAdd3f(Vector3* v_out, Vector3* v1, float factor);

void VectorSub3(Vector3* v_out, Vector3 v1, Vector3 v2);
void VectorSub3p(Vector3* v_out, Vector3* v1, Vector3* v2);
void VectorSub3f(Vector3* v_out, Vector3* v1, float factor);

void VectorMul3(Vector3* v_out, Vector3 v1, Vector3 v2);
void VectorMul3p(Vector3* v_out, Vector3* v1, Vector3* v2);
void VectorMul3f(Vector3* v_out, Vector3* v1, float factor);

void VectorDiv3(Vector3* v_out, Vector3 v1, Vector3 v2);
void VectorDiv3p(Vector3* v_out, Vector3* v1, Vector3* v2);
void VectorDiv3f(Vector3* v_out, Vector3* v1, float factor);

void VectorCross3(Vector3* v_out, Vector3 v1, Vector3 v2);
void VectorCross3p(Vector3* v_out, Vector3* v1, Vector3* v2);

float VectorDot3(Vector3 v1, Vector3 v2);
float VectorDot3p(Vector3* v1, Vector3* v2);

void VectorNormalize3(Vector3* v_out, Vector3 v);
void VectorNormalize3p(Vector3* v_out, Vector3* v);

float VectorDistance3(Vector3 v1, Vector3 v2);
float VectorDistance3p(Vector3* v1, Vector3* v2);

float VectorLength3(Vector3 v);
float VectorLength3p(Vector3* v);

void VectorToArray3(float* arr_out, Vector3* v);