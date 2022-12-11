#include <cmath>
#include <iostream>
#include <utility>

#include "Vector3F.hpp"
#include "Vector3U.hpp"

namespace Syroot::Maths
{
    struct Vector3
    {
    public:
        static constexpr int ValueCount = 3;
        static constexpr int SizeInBytes = 12;

        int X;
        int Y;
        int Z;

        Vector3(int x, int y, int z) : X(x), Y(y), Z(z) {}

        static Vector3U Zero()
        {
            return Vector3U(0, 0, 0);
        }

        static Vector3U One()
        {
            return Vector3U(1, 1, 1);
        }

        constexpr float Length()
        {
            return sqrt(X * X + Y * Y + Z * Z);
        }

        Vector3 operator+(const Vector3 &a) const
        {
            return a;
        }

        friend Vector3 operator+(const Vector3 &a, const Vector3 &b)
        {
            return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        }

        Vector3 operator-(const Vector3 &a) const
        {
            return Vector3(-a.X, -a.Y, -a.Z);
        }

        friend Vector3 operator-(const Vector3 &a, const Vector3 &b)
        {
            return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }

        friend Vector3 operator*(const Vector3 &a, const float s)
        {
            return Vector3(a.X * s, a.Y * s, a.Z * s);
        }

        friend Vector3 operator*(const Vector3 &a, const Vector3 &b)
        {
            return Vector3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
        }

        friend Vector3 operator/(const Vector3 &a, const float s)
        {
            return Vector3(a.X / s, a.Y / s, a.Z / s);
        }

        friend Vector3 operator/(const Vector3 &a, const Vector3 &b)
        {
            return Vector3(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
        }

        friend bool operator==(const Vector3 &a, const Vector3 &b)
        {
            return a == b;
        }

        friend bool operator!=(const Vector3 &a, const Vector3 &b)
        {
            return a != b;
        }

        constexpr bool Equals(Vector3 &a)
        {
            return (*this == a);
        }

        constexpr float Angle(Vector3 &vector)
        {
            return std::acos(this->Dot(vector) / (this->Length() * vector.Length()));
        }

        constexpr float Dot(Vector3 &vector)
        {
            return (this->X * vector.X + this->Y * vector.Y + this->Z * vector.Z);
        }

        float Dot(const Vector3 &vector) const
        {
            return (this->X * vector.X + this->Y * vector.Y + this->Z * vector.Z);
        }

        constexpr void Normalize()
        {
            *this = *this / this->Length();
        }

        Vector3 Normalized()
        {
            *this = *this / this->Length();
        }
    };
} // namespace Syroot::Maths
