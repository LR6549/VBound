//
// Created by lenny on 23.01.2026.
//

#include "MathVector.h++"

//++ MathVector2

template <typename T>
double VBND::MathVector2<T>::length() {
    return std::sqrt((mv_x * mv_x) + (mv_y * mv_y ) + (mv_z * mv_z));
}

template<>
VBND::MathVector2<double> VBND::MathVector2<double>::normalized() {
    double len = length();
    if (len == 0.0) return {0, 0};
    return {static_cast<double>(mv_x) / len, static_cast<double>(mv_y) / len};
}

template <typename T>
void VBND::MathVector2<T>::normalize() {
    double len = length();
    if (len != 0.0) {
        mv_x /= len;
        mv_y /= len;
    } else {
        mv_x = 0;
        mv_y = 0;
    }
}

template <typename T>
double VBND::MathVector2<T>::dot(const VBND::MathVector2<T>& pVector) {
    const VBND::MathVector2 pVect1 = normalized();
    const VBND::MathVector2 pVect2 = pVector.normalized();
    return {(pVect1.mv_x * pVect2.mv_x) + (pVect1.mv_y * pVect2.mv_y)};
}

template <typename T>
VBND::MathVector2<T> VBND::MathVector2<T>::operator+(const VBND::MathVector2<T>& other)  {
    return {mv_x + other.mv_x, mv_y + other.mv_y};
}

template <typename T>
VBND::MathVector2<T> VBND::MathVector2<T>::operator-(const VBND::MathVector2<T>& other) {
    return {mv_x - other.mv_x, mv_y - other.mv_y};
}

template <typename T>
VBND::MathVector2<T> VBND::MathVector2<T>::operator*(const VBND::MathVector2<T>& other)  {
    return {mv_x * other.mv_x, mv_y * other.mv_y};
}

template <typename T>
VBND::MathVector2<T> VBND::MathVector2<T>::operator/(const VBND::MathVector2<T>& other)  {
    return {mv_x / other.mv_x, mv_y / other.mv_y};
}

template <typename T>
bool VBND::MathVector2<T>::isInFOV(VBND::MathVector2<T> pVectDirToObj, double tolerance) {
    return (this->dot(pVectDirToObj) > tolerance);
}

template <typename T>
VBND::MathVector2<T>::MathVector2() = default;

template <typename T>
VBND::MathVector2<T>::MathVector2(T x, T y) : mv_x(x), mv_y(y) {};

template <typename T>
VBND::MathVector2<T>::~MathVector2() = default;




//++ MathVector3:

template <typename T>
double VBND::MathVector3<T>::length() {
    return std::sqrt((mv_x * mv_x) + (mv_y * mv_y ) + (mv_z * mv_z));
}

template<>
VBND::MathVector3<double> VBND::MathVector3<double>::normalized() {
    double len = length();
    if (len == 0.0) return {0, 0, 0};
    return {static_cast<double>(mv_x) / len, static_cast<double>(mv_y) / len, static_cast<double>(mv_z) / len};
}

template <typename T>
void VBND::MathVector3<T>::normalize() {
    double len = length();
    if (len != 0.0) {
        mv_x /= len;
        mv_y /= len;
        mv_z /= len;
    } else {
        mv_x = 0;
        mv_y = 0;
        mv_z = 0;
    }
}

template <typename T>
double VBND::MathVector3<T>::dot(const VBND::MathVector3<T>& pVector) {
    const VBND::MathVector3 pVect1 = normalized();
    const VBND::MathVector3 pVect2 = pVector.normalized();
    return {(pVect1.mv_x * pVect2.mv_x) + (pVect1.mv_y * pVect2.mv_y) + (pVect1.mv_z * pVect2.mv_z)};
}

template <typename T>
VBND::MathVector3<T> VBND::MathVector3<T>::operator+(const VBND::MathVector3<T>& other)  {
    return {mv_x + other.mv_x, mv_y + other.mv_y , mv_z + other.mv_z };
}

template <typename T>
VBND::MathVector3<T> VBND::MathVector3<T>::operator-(const VBND::MathVector3<T>& other) {
    return {mv_x - other.mv_x, mv_y - other.mv_y , mv_z - other.mv_z };
}

template <typename T>
VBND::MathVector3<T> VBND::MathVector3<T>::operator*(const VBND::MathVector3<T>& other)  {
    return {mv_x * other.mv_x, mv_y * other.mv_y , mv_z * other.mv_z };
}

template <typename T>
VBND::MathVector3<T> VBND::MathVector3<T>::operator/(const VBND::MathVector3<T>& other)  {
    return {mv_x / other.mv_x, mv_y / other.mv_y , mv_z / other.mv_z };
}

template <typename T>
bool VBND::MathVector3<T>::isInFOV(VBND::MathVector3<T> pVectDirToObj, double tolerance) {
    return (this->dot(pVectDirToObj) > tolerance);
}

template <typename T>
VBND::MathVector3<T>::MathVector3() = default;

template <typename T>
VBND::MathVector3<T>::MathVector3(T x, T y, T z) : mv_x(x), mv_y(y), mv_z(z) {};

template <typename T>
VBND::MathVector3<T>::~MathVector3() = default;