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

    Matrix33 matrice = Matrix33();

    float detVal = GetDeterminant(*this);

    if (detVal == 0) return NULL;

    matrice.values[0] = (values[4] * values[8]) - (values[6] * values[7]);
    matrice.values[1] = (values[2] * values[7]) - (values[1] * values[8]);
    matrice.values[2] = (values[1] * values[5]) - (values[2] * values[4]);
    matrice.values[3] = (values[5] * values[6]) - (values[3] * values[8]);
    matrice.values[4] = (values[0] * values[8]) - (values[2] * values[6]);
    matrice.values[5] = (values[2] * values[3]) - (values[0] * values[5]);
    matrice.values[6] = (values[3] * values[7]) - (values[4] * values[6]);
    matrice.values[7] = (values[3] * values[7]) - (values[0] * values[7]);
    matrice.values[8] = (values[0] * values[4]) - (values[1] * values[3]);

    *matrice.values = (1 / detVal) * *values;

    return matrice;
}

Matrix33& const Matrix33::operator*=(const Matrix33& other){

    Matrix33 mat = Matrix33();
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            mat.values[i + j * 3] = 0;
            for (int k = 0; k < 3; k++)
                mat.values[i + j * 3] += values[k + i * 3] * other.values[j + k * 3];
        }
    for (int i = 0; i < 9; i++) {
        values[i] = mat.values[i];
    }
    return (*this);
}

Matrix33 operator*(const Matrix33& premiereMat, const Matrix33& secondeMat)
{
    Matrix33 troisiemeMat = premiereMat;
    troisiemeMat *= secondeMat;
    return troisiemeMat;
}

Vector3D const Matrix33::operator* (const Vector3D& vector) {

    return Vector3D{
        vector.x * values[0] + vector.y * values[1] + vector.z * values[2],
        vector.x * values[3] + vector.y * values[4] + vector.z * values[5],
        vector.x * values[6] + vector.y * values[7] + vector.z * values[8]
    };
}

float Matrix33::GetDeterminant(const Matrix33& matrice)
{
    return 
        matrice.values[0] * matrice.values[4] * matrice.values[8] +
        matrice.values[3] * matrice.values[7] * matrice.values[2] +
        matrice.values[6] * matrice.values[1] * matrice.values[5] -
        matrice.values[0] * matrice.values[7] * matrice.values[5] -
        matrice.values[6] * matrice.values[4] * matrice.values[2] -
        matrice.values[3] * matrice.values[1] * matrice.values[8];
}

void Matrix33::SetOrientation(const Quaternion& q) {

    values[0] = 1 - (2*q.value[2] * q.value[2] + 2 * q.value[3] * q.value[3]);
    values[1] = 2 * q.value[1] * q.value[2] + 2 * q.value[3] * q.value[0];
    values[2] = 2 * q.value[1] * q.value[3] - 2 * q.value[2] * q.value[0];
    values[3] = 2 * q.value[1] * q.value[2] - 2 * q.value[3] * q.value[0];
    values[4] = 1 - (2 * q.value[1] * q.value[1] + 2 * q.value[3] * q.value[3]);
    values[5] = 2 * q.value[2] * q.value[3] + 2 * q.value[1] * q.value[0];
    values[6] = 2 * q.value[1] * q.value[3] + 2 * q.value[2] * q.value[0];
    values[7] = 2 * q.value[2] * q.value[3] - 2 * q.value[1] * q.value[0];
    values[8] = 1 - (2 * q.value[1] * q.value[1] + 2 * q.value[2] * q.value[2]);
}

Vector3D Matrix33::Transform(const Vector3D& v) {
    return (*this) * v;
}
