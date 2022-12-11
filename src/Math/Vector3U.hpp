#include <cmath>
#include <iostream>
#include <utility>

namespace Syroot::Maths
{
    struct Vector3U
    {
        static constexpr int ValueCount = 3;
        static constexpr int SizeInBytes = 12;

        unsigned int X;
        unsigned int Y;
        unsigned int Z;

        Vector3U(unsigned int x, unsigned int y, unsigned int z) : X(x), Y(y), Z(z)
        {
        }

        static Vector3U Zero()
        {
            return Vector3U(0, 0, 0);
        }

        static Vector3U One()
        {
            return Vector3U(1U, 1U, 1U);
        }

        constexpr float Length() const
        {
            return sqrt(X * X + Y * Y + Z * Z);
        }

        Vector3U operator+(const Vector3U &a) const
        {
            return Vector3U(X + a.X, Y + a.Y, Z + a.Z);
        }

        Vector3U operator-(const Vector3U &a) const
        {
            return Vector3U(X - a.X, Y - a.Y, Z - a.Z);
        }

        Vector3U operator*(const float s) const
        {
            return Vector3U(X * s, Y * s, Z * s);
        }

        Vector3U operator*(const Vector3U &a) const
        {
            return Vector3U(X * a.X, Y * a.Y, Z * a.Z);
        }

        Vector3U operator/(const float s) const
        {
            return Vector3U(X / s, Y / s, Z / s);
        }

        Vector3U operator/(const Vector3U &a) const
        {
            return Vector3U(X / a.X, Y / a.Y, Z / a.Z);
        }

        constexpr bool operator==(const Vector3U &a) const
        {
            return X == a.X && Y == a.Y && Z == a.Z;
        }

        constexpr bool operator!=(const Vector3U &a) const
        {
            return X != a.X || Y != a.Y || Z != a.Z;
        }

        constexpr unsigned int operator[](const int index) const
        {
            switch (index)
            {
            case 0:
                return X;
            case 1:
                return Y;
            case 2:
                return Z;
            default:
                throw std::invalid_argument(
                    "Index must be between 0 and " + std::to_string(ValueCount) + ".");
            }
        }

        constexpr unsigned int &operator[](const int index)
        {
            switch (index)
            {
            case 0:
                return X;
            case 1:
                return Y;
            case 2:
                return Z;
            default:
                throw std::invalid_argument(
                    "Index must be between 0 and " + std::to_string(ValueCount) + ".");
            }
        }

        constexpr unsigned int GetHashCode() const {
            int hash = 1531;
            hash = hash * 1319 + (int)X;
            hash = hash * 1319 + (int)Y;
            hash = hash * 1319 + (int)Z;
            return hash;
        }

        constexpr bool Equals(Vector3U &a)
        {
            return (*this == a);
        }

        constexpr float Angle(Vector3U &vector)
        {
            return (float) std::acos((double) this->Dot(vector) / ((double) this->Length() * (double) vector.Length()));
        }

        float Angle(const Vector3U &vector) const
        {
            return (float) std::acos((double) this->Dot(vector) / ((double) this->Length() * (double) vector.Length()));
        }

        constexpr float Dot(Vector3U &vector)
        {
            return (float) (unsigned int) ((int)this->X * (int)vector.X + (int)this->Y * (int)vector.Y + (int)this->Z * (int)vector.Z);
        } 

        float Dot(const Vector3U &vector) const
        {
            return (float) (unsigned int) ((int)this->X * (int)vector.X + (int)this->Y * (int)vector.Y + (int)this->Z * (int)vector.Z);
        }

        constexpr void Normalize()
        {
            *this = *this / this->Length();
        }

        Vector3U Normalized()
        {
            *this = *this / this->Length();
        }
    };
}