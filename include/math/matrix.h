#pragma once
#include "platform/common.h"
#include "math/vector3.h"

typedef struct
{
    float m[4][4];
} Matrix;

void MatrixIdentity(Matrix* matrix);
void MatrixMultiply(Matrix* m_out, const Matrix* m1, const Matrix* m2);

void MatrixOrthoLH(Matrix* m_out, float x, float y, float w, float h, float z_near, float z_far);
void MatrixOrthoOffCenterLH(Matrix* m_out, float l, float r, float b, float t, float z_near, float z_far);
void MatrixPerspectiveFovLH(Matrix* m_out, float fov, float aspect, float z_near, float z_far);
void MatrixLookAtLH(Matrix* m_out, Vector3* v_eye, Vector3* v_target, Vector3* v_up);