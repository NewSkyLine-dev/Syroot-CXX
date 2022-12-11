#pragma once

#pragma once

#include <cstdint>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

#include "Vector2.hpp"

namespace Syroot::Maths
{
    struct Rectangle
    {
    public:
        int X, Y, Width, Height;

        constexpr Rectangle() : X(0), Y(0), Width(0), Height(0) {}

        constexpr Rectangle(int x, int y, int width, int height) : X(x), Y(y), Width(width), Height(height) {}

        constexpr Rectangle(Vector2 position, Vector2 size) : X(position.X), Y(position.Y), Width(size.X), Height(size.Y) {}

        constexpr Vector2 Position() const { return Vector2(X, Y); }

        void Position(Vector2 position)
        {
            X = position.X;
            Y = position.Y;
        }

        constexpr Vector2 Size() const { return Vector2(Width, Height); }

        void Size(Vector2 size)
        {
            Width = size.X;
            Height = size.Y;
        }

        constexpr int X2() const { return X + Width; }

        void X2(int x2) { Width = x2 - X; }

        constexpr int Y2() const { return Y + Height; }

        void Y2(int y2) { Height = y2 - Y; }

        constexpr bool operator==(const Rectangle &b) const { return Equals(b); }

        constexpr bool operator!=(const Rectangle &b) const { return !Equals(b); }

        // explicit operator Rectangle(RectangleF rectangle) { return Rectangle((int)rectangle.X, (int)rectangle.Y, (int)rectangle.Width, (int)rectangle.Height); }

        constexpr bool Equals(const Rectangle &b) const
        {
            return X == b.X && Y == b.Y && Width == b.Width && Height == b.Height;
        }
    };
} // namespace Syroot::Maths
