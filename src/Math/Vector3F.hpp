#include <cmath>
#include <iostream>
#include <utility>

namespace Syroot::Maths
{
    struct Vector3F
    {
        static const Vector3F Zero;
        static const Vector3F One;
        static constexpr int ValueCount = 3;
        static constexpr int SizeInBytes = 12;

        float X;
        float Y;
        float Z;

        Vector3F(float x, float y, float z) : X(x), Y(y), Z(z)
        {
        }

        constexpr float Length() const
        {
            return sqrt(X * X + Y * Y + Z * Z);
        }

        Vector3F operator+(const Vector3F &a) const
        {
            return Vector3F(X + a.X, Y + a.Y, Z + a.Z);
        }

        Vector3F operator-(const Vector3F &a) const
        {
            return Vector3F(X - a.X, Y - a.Y, Z - a.Z);
        }

        Vector3F operator*(const float s) const
        {
            return Vector3F(X * s, Y * s, Z * s);
        }

        Vector3F operator*(const Vector3F &a) const
        {
            return Vector3F(X * a.X, Y * a.Y, Z * a.Z);
        }

        Vector3F operator/(const float s) const
        {
            return Vector3F(X / s, Y / s, Z / s);
        }

        Vector3F operator/(const Vector3F &a) const
        {
            return Vector3F(X / a.X, Y / a.Y, Z / a.Z);
        }

        constexpr bool operator==(const Vector3F &a) const
        {
            return X == a.X && Y == a.Y && Z == a.Z;
        }

        constexpr bool operator!=(const Vector3F &a) const
        {
            return X != a.X || Y != a.Y || Z != a.Z;
        }

        constexpr float operator[](const int index) const
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

        constexpr float &operator[](const int index)
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

        constexpr float GetHashCode() const {
            int hash = 263;
            hash = hash * 383 + (int)X;
            hash = hash * 383 + (int)Y;
            hash = hash * 383 + (int)Z;
            return hash;
        }

        constexpr bool Equals(Vector3F &a)
        {
            return (*this == a);
        }

        constexpr float Angle(Vector3F &vector)
        {
            return (float) std::acos((double) this->Dot(vector) / ((double) this->Length() * (double) vector.Length()));
        }

        float Angle(const Vector3F &vector) const
        {
            return (float) std::acos((double) this->Dot(vector) / ((double) this->Length() * (double) vector.Length()));
        }

        constexpr float Dot(Vector3F &vector)
        {
            return (float) (float) ((int)this->X * (int)vector.X + (int)this->Y * (int)vector.Y + (int)this->Z * (int)vector.Z);
        } 

        float Dot(const Vector3F &vector) const
        {
            return (float) (float) ((int)this->X * (int)vector.X + (int)this->Y * (int)vector.Y + (int)this->Z * (int)vector.Z);
        }

        constexpr void Normalize()
        {
            *this = *this / this->Length();
        }

        Vector3F Normalized()
        {
            *this = *this / this->Length();
        }
    };
}