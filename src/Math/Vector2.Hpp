#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include "Vector2F.hpp"
#include "Vector2U.hpp"
#include "Rectangle.hpp"

namespace Syroot::Maths
{
    struct Vector2
    {
    public:
        constexpr static int ValueCount = 2;
        constexpr static int SizeInBytes = 8;

        int X;
        int Y;
        int Width;
        int Height;

        constexpr Vector2() : X(0), Y(0) {}

        constexpr Vector2(int x, int y) : X(x), Y(y) {}

        constexpr Vector2 operator+() const { return *this; }

        constexpr Vector2 operator+(const Vector2 &b) const { return Vector2(X + b.X, Y + b.Y); }

        constexpr Vector2 operator-() const { return Vector2(-X, -Y); }

        constexpr Vector2 operator-(const Vector2 &b) const { return Vector2(X - b.X, Y - b.Y); }

        constexpr Vector2 operator*(float s) const { return Vector2((int)((double)X * (double)s), (int)((double)Y * (double)s)); }

        constexpr Vector2 operator*(const Vector2 &b) const { return Vector2(X * b.X, Y * b.Y); }

        constexpr Vector2 operator/(float s) const { return Vector2((int)((double)X / (double)s), (int)((double)Y / (double)s)); }

        constexpr Vector2 operator/(const Vector2 &b) const { return Vector2(X / b.X, Y / b.Y); }

        constexpr bool operator==(const Vector2 &b) const { return Equals(b); }

        constexpr bool operator!=(const Vector2 &b) const { return !Equals(b); }

        explicit operator Vector2() { return Vector2((int)X, (int)Y); }

        explicit operator Vector2() const { return Vector2((int)X, (int)Y); }

        constexpr int operator[](int index) const
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

        int &operator[](int index)
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

        constexpr bool Equals(const Vector2 &b) const
        {
            return X == b.X && Y == b.Y;
        }

        constexpr bool Equals(const Vector2 &b, float delta) const
        {
            return std::abs(X - b.X) <= delta && std::abs(Y - b.Y) <= delta;
        }

        constexpr int GetHashCode() const
        {
            int hash = 17;
            
            hash = hash * 31 + static_cast<std::size_t>(X);
            hash = hash * 31 + static_cast<std::size_t>(Y);
            hash = hash * 31 + static_cast<std::size_t>(Width);
            hash = hash * 31 + static_cast<std::size_t>(Height);
            return hash;
        }

        constexpr bool Intersect(Rectangle &other) const
        {
            return this->X == other.X && this->Y == other.Y && this->Width == other.Width && this->Height == other.Height;
        }
    };
} // namespace Syroot::Maths
