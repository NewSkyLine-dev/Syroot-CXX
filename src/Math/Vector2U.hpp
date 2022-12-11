#pragma once

#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include "Vector2U.hpp"

namespace Syroot::Maths
{
    struct Vector2F
    {
    public:
        constexpr static int ValueCount = 2;
        constexpr static int SizeInBytes = 8;

        unsigned int X;
        unsigned int Y;

        constexpr Vector2F() : X(0.0f), Y(0.0f) {}

        constexpr Vector2F(unsigned int x, unsigned int y) : X(x), Y(y) {}

        constexpr Vector2F operator+() const { return *this; }

        constexpr Vector2F operator+(const Vector2F &b) const { return Vector2F(X + b.X, Y + b.Y); }

        constexpr Vector2F operator-() const { return Vector2F(-X, -Y); }

        constexpr Vector2F operator-(const Vector2F &b) const { return Vector2F(X - b.X, Y - b.Y); }

        constexpr Vector2F operator*(unsigned int s) const { return Vector2F(X * s, Y * s); }

        constexpr Vector2F operator*(const Vector2F &b) const { return Vector2F(X * b.X, Y * b.Y); }

        constexpr Vector2F operator/(unsigned int s) const { return Vector2F(X / s, Y / s); }

        constexpr Vector2F operator/(const Vector2F &b) const { return Vector2F(X / b.X, Y / b.Y); }

        constexpr bool operator==(const Vector2F &b) const { return Equals(b); }

        constexpr bool operator!=(const Vector2F &b) const { return !Equals(b); }

        explicit operator Vector2F() const { return Vector2F((unsigned int)X, (unsigned int)Y); }

        constexpr unsigned int operator[](int index) const
        {
            switch (index)
            {
            case 0:
                return X;
            case 1:
                return Y;
            default:
                throw std::invalid_argument("Index must be between 0 and 2.");
            }
        }

        unsigned int &operator[](int index)
        {
            switch (index)
            {
            case 0:
                return X;
            case 1:
                return Y;
            default:
                throw std::invalid_argument("Index must be between 0 and 2.");
            }
        }

        constexpr bool Equals(const Vector2F &b) const
        {
            return X == b.X && Y == b.Y;
        }

        constexpr bool Equals(const Vector2F &b, unsigned int delta) const
        {
            return (X - b.X) <= delta && (Y - b.Y) <= delta;
        }

        constexpr int GetHashCode() const
        {
            return 43 * (7 + X) * (7 + Y);
        }
    };
} // namespace Syroot::Maths
