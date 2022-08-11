#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <framework_build.hpp>

#include <stdlib.h>

namespace ai_framework {
    /// <summary>
    /// Stores a bi-dimensional point of the specified type.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template <typename T>
    struct Vector2 {
        Vector2()
            : x(0), y(0) {
        }

        Vector2(const Vector2<T> &rhs)
            : x(rhs.x), y(rhs.y) {
        }

        Vector2(T x, T y)
            : x(x), y(y) {
        }

        T x;
        T y;

        Vector2 abs() const {
            return {::abs(x), ::abs(y)};
        }

        template <typename _T>
        Vector2 &operator+=(const Vector2<_T> &r) {
            x += r.x;
            y += r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator+=(const _T &r) {
            x += r;
            y += r;

            return *this;
        }

        template <typename _T>
        Vector2 &operator-=(const Vector2<_T> &r) {
            x -= r.x;
            y -= r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator-=(const _T &r) {
            x -= r;
            y -= r;

            return *this;
        }

        template <typename _T>
        Vector2 &operator/=(const Vector2<_T> &r) {
            x /= r.x;
            y /= r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator/=(const _T &r) {
            x /= r;
            y /= r;

            return *this;
        }

        template <typename _T>
        Vector2 &operator*=(const Vector2<_T> &r) {
            x *= r.x;
            y *= r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator*=(const _T &r) {
            x *= r;
            y *= r;

            return *this;
        }

        template <typename _T>
        Vector2 operator+(const Vector2<_T> &r) {
            x += r.x;
            y += r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator+(const _T &r) {
            x += r;
            y += r;

            return *this;
        }

        template <typename _T>
        Vector2 operator-(const Vector2<_T> &r) {
            x -= r.x;
            y -= r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator-(const _T &r) {
            x -= r;
            y -= r;

            return *this;
        }

        template <typename _T>
        Vector2 operator/(const Vector2<_T> &r) {
            x /= r.x;
            y /= r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator/(const _T &r) {
            x /= r;
            y /= r;

            return *this;
        }

        template <typename _T>
        Vector2<T> operator*(const Vector2<_T> &r) {
            x *= r.x;
            y *= r.y;

            return *this;
        }

        template <typename _T>
        Vector2 &operator*(const _T &r) {
            x *= r;
            y *= r;

            return *this;
        }
    };

    using IntVector2 = Vector2<int>;
    using FloatVector2 = Vector2<float>;
} // namespace ai_framework

#endif