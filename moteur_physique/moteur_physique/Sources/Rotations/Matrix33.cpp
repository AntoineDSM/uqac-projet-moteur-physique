#include "Rotations/Matrix33.h"


Matrix33 Matrix33::Transpose() {
    values[1] = values[3] ;
    values[2] = values[6] ;
    values[3] = values[1] ;
    values[5] = values[7] ;
    values[6] = values[2] ;
    values[7] = values[5] ;
}

Matrix33 Matrix33::Inverse() {
    float valPos = values[0] * values[4] * values[8] + values[3] * values[7] * values[2] + values[6] * values[1] * values[5];
    float valNeg = values[0] * values[7] * values[5] - values[6] * values[7] * values[2] - values[3] * values[1] * values[8];
    float detVal = valPos - valNeg;

    values[0] = (values[4] * values[8]) - (values[6] * values[7]);
    values[1] = (values[2] * values[7]) - (values[1] * values[8]);
    values[2] = (values[1] * values[5]) - (values[2] * values[4]);
    values[3] = (values[5] * values[6]) - (values[3] * values[8]);
    values[4] = (values[0] * values[8]) - (values[2] * values[6]);
    values[5] = (values[2] * values[3]) - (values[0] * values[5]);
    values[6] = (values[3] * values[7]) - (values[4] * values[6]);
    values[7] = (values[3] * values[7]) - (values[0] * values[7]);
    values[8] = (values[0] * values[4]) - (values[1] * values[3]);

    *values = (1 / detVal) * *values;
}

Matrix33 const operator*(const Matrix33& other){

    return Matrix33{
        values[0] * other.values[0] + values[1] * other.values[3] + values[2] * other.values[6],
        values[0] * other.values[1] + values[1] * other.values[4] + values[2] * other.values[7],
        values[0] * other.values[2] + values[1] * other.values[5] + values[2] * other.values[8],
                                                                                
        values[3] * other.values[0] + values[4] * other.values[3] + values[5] * other.values[6],
        values[3] * other.values[1] + values[4] * other.values[4] + values[5] * other.values[7],
        values[3] * other.values[2] + values[4] * other.values[5] + values[5] * other.values[8],
                                                                                
        values[6] * other.values[0] + values[7] * other.values[3] + values[8] * other.values[6],
        values[6] * other.values[1] + values[7] * other.values[4] + values[8] * other.values[7],
        values[6] * other.values[2] + values[7] * other.values[5] + values[8] * other.values[8]
        };
}

Vector3D const operator* (const Vector3D& vector) {

    return Vector3D{
        vector.x * values[0] + vector.y * values[1] + vector.z * values[2],
        vector.x * values[3] + vector.y * values[4] + vector.z * values[5],
        vector.x * values[6] + vector.y * values[7] + vector.z * values[8]

    };
}

void Matrix33::Set0rientation(const Quaternion& q) {

    values[0] = 1 - (2*q.j * q.j + 2 * q.k * q.k);
    values[1] = 2 * q.i * q.j + 2 * q.k * q.w;
    values[2] = 2 * q.i * q.k - 2 * q.j * q.w;
    values[3] = 2 * q.i * q.j - 2 * q.k * q.w;
    values[4] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
    values[5] = 2 * q.j * q.k + 2 * q.i * q.w;
    values[6] = 2 * q.i * q.k + 2 * q.j * q.w;
    values[7] = 2 * q.j * q.k - 2 * q.i * q.w;
    values[8] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
}

/*
 * Retourne la transposé de la matrice
 * @return Une matrice 4
 */
 /*
Matrix3 Matrix3::TranpositionM()
{
    Matrix4 B(getA());
    B.TranpositionA();
    return B;
}

/**
 * Transpose la matrice A
 */

 /*
void Matrix3::TranpositionA()
{
    float B[16] = { 0 };
    for (int i = 0; i < 15; i++)
    {
        B[i] = A[(i * 4) % 15];
        B[15] = A[15];
    }
    setA(B);
}

*/