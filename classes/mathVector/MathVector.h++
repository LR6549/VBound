//
// Created by lenny on 23.01.2026.
//

#ifndef VBOUND_MATHVECTOR_H
#define VBOUND_MATHVECTOR_H

#include <cmath>
#include <concepts>

namespace VBND {
    template <typename T>
    class MathVector2 {
        static_assert(std::is_arithmetic<T>::value, "Vector2 only supports arithmetic types.");

        private:


        public:
            T mv_x, mv_y;

            MathVector2();
            MathVector2(T x, T y);
            ~MathVector2();

            double length();

            MathVector2<double> normalized();

            void normalize();

            double dot(const MathVector2<T>& pVector);

            MathVector2<T> operator+(const MathVector2<T>& other);

            MathVector2<T> operator-(const MathVector2<T>& other);

            MathVector2<T> operator*(const MathVector2<T>& other);

            MathVector2<T> operator/(const MathVector2<T>& other);

            bool isInFOV(MathVector2<T> pVectDirToObj, double tolerance = 0.0);
    };

    template <typename T>
    class MathVector3 {
        static_assert(std::is_arithmetic<T>::value, "Vector2 only supports arithmetic types.");
        private:


        public:
            T mv_x, mv_y, mv_z;

            MathVector3();
            MathVector3(T x, T y, T z);
            ~MathVector3();

            double length();

            MathVector3<double> normalized();

            void normalize();

            double dot(const MathVector3<T>& pVector);

            MathVector3<T> operator+(const MathVector3<T>& other);

            MathVector3<T> operator-(const MathVector3<T>& other);

            MathVector3<T> operator*(const MathVector3<T>& other);

            MathVector3<T> operator/(const MathVector3<T>& other);

            bool isInFOV(MathVector3<T> pVectDirToObj, double tolerance = 0.0);
    };
}

#endif //VBOUND_MATHVECTOR_H