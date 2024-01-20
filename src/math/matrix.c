#include "math/matrix.h"
#include "minecraft.h"

void MatrixIdentity(Matrix* matrix)
{
    memset(matrix, 0, sizeof(Matrix));
    matrix->m[0][0] = 1.0f;
    matrix->m[1][1] = 1.0f;
    matrix->m[2][2] = 1.0f;
    matrix->m[3][3] = 1.0f;
}

void MatrixMultiply(Matrix* m_out, const Matrix* m1, const Matrix* m2) 
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            m_out->m[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) { m_out->m[i][j] += m1->m[i][k] * m2->m[k][j]; }
        }
    }
}

void MatrixOrthoLH(Matrix* m_out, float x, float y, float w, float h, float z_near, float z_far)
{
    memset(m_out, 0, sizeof(Matrix));
    m_out->m[0][0] = w / 2.0f;
    m_out->m[1][1] = h / -2.0f;
    m_out->m[2][2] = z_far - z_near;
    m_out->m[3][3] = 1.0f;
    m_out->m[3][0] = x + w / 2.0f;
    m_out->m[3][1] = y + h / 2.0f; 
    m_out->m[3][2] = z_near;
}

void MatrixOrthoOffCenterLH(Matrix* m_out, float l, float r, float b, float t, float z_near, float z_far)
{
    float zr = 1.0f / (z_far - z_near);
    
    MatrixIdentity(m_out);
    m_out->m[0][0] = 2.0f / (r - l);
    m_out->m[1][1] = 2.0f / (t - b);
    m_out->m[2][2] = zr;
    m_out->m[3][3] = 1.0f;
    m_out->m[3][0] = (l + r) / (l - r);
    m_out->m[3][1] = (t + b) / (b - t);
    m_out->m[3][2] = -z_near * zr;
}

void MatrixPerspectiveFovLH(Matrix* m_out, float fov, float aspect, float z_near, float z_far)
{
    float ys = (float)(1.0f / tanf(fov * 0.5f));
    float q  = z_far / (z_far - z_near);

    memset(m_out, 0, sizeof(Matrix));
    m_out->m[0][0] = ys / aspect;
    m_out->m[1][1] = ys;
    m_out->m[2][2] = q;
    m_out->m[2][3] = 1.0f;
    m_out->m[3][2] = -q * z_near;
}

void MatrixLookAtLH(Matrix* m_out, Vector3* v_eye, Vector3* v_target, Vector3* v_up)
{
    Vector3 xaxis, yaxis, zaxis;
    VectorSub3p(&zaxis, v_target, v_eye);
    VectorCross3p(&xaxis, v_up, &zaxis);
    VectorCross3p(&yaxis, &zaxis, &xaxis);

    MatrixIdentity(m_out);
    m_out->m[0][0] = xaxis.x; m_out->m[1][0] = xaxis.y; m_out->m[2][0] = xaxis.z;
    m_out->m[0][1] = yaxis.x; m_out->m[1][1] = yaxis.y; m_out->m[2][1] = yaxis.z;
    m_out->m[0][2] = zaxis.x; m_out->m[1][2] = zaxis.y; m_out->m[2][2] = zaxis.z;

    m_out->m[3][0] = -VectorDot3p(&xaxis, v_eye);
    m_out->m[3][1] = -VectorDot3p(&yaxis, v_eye);
    m_out->m[3][2] = -VectorDot3p(&zaxis, v_eye);
}