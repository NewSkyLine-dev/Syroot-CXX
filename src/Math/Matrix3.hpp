#pragma once

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

namespace Syroot::Maths
{
    struct Matrix3
    {
        static constexpr std::size_t Rows = 3;
        static constexpr std::size_t Columns = 3;
        static constexpr std::size_t ValueCount = 9;
        static constexpr std::size_t SizeInBytes = 36;

        float M11;
        float M12;
        float M13;
        float M21;
        float M22;
        float M23;
        float M31;
        float M32;
        float M33;

        Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
            : M11(m11), M12(m12), M13(m13), M21(m21), M22(m22), M23(m23), M31(m31), M32(m32), M33(M33)
        {
        }

        static Matrix3 Zero()
        {
            return Matrix3(0, 0, 0, 0, 0, 0, 0, 0, 0);
        }

        Matrix3 operator* (const Matrix3& b) const
        {
            return Matrix3(
                M11 * b.M11 + M12 * b.M21 + M13 * b.M31,
                M11 * b.M12 + M12 * b.M22 + M13 * b.M32,
                M11 * b.M13 + M12 * b.M23 + M13 * b.M33,
                M21 * b.M11 + M22 * b.M21 + M23 * b.M31,
                M21 * b.M12 + M22 * b.M22 + M23 * b.M32,
                M21 * b.M13 + M22 * b.M23 + M23 * b.M33,
                M31 * b.M11 + M32 * b.M21 + M33 * b.M31,
                M31 * b.M12 + M32 * b.M22 + M33 * b.M32,
                M31 * b.M13 + M32 * b.M23 + M33 * b.M33
            );
        }

        bool operator==(const Matrix3 &other) const
        {
            return (*this == other);
        }

        bool operator!=(const Matrix3 &other) const
        {
            return !(*this == other);
        }

        float operator[](std::size_t index) const
        {
            switch (index)
            {
            case 0:
                return M11;
            case 1:
                return M12;
            case 2:
                return M13;
            case 3:
                return M21;
            case 4:
                return M22;
            case 5:
                return M23;
            case 6:
            	return M31;
            case 7:
            	return M32;
            case 8:
            	return M33;
            default:
                 throw std::out_of_range("Index must be between 0 and  " + std::to_string(this->ValueCount) + ".");
            }
        }

        float &operator[](std::size_t index)
        {
            switch (index)
            {
            case 0:
                return M11;
            case 1:
                return M12;
            case 2:
                return M13;
            case 3:
                return M21;
            case 4:
                return M22;
            case 5:
                return M23;
            case 6:
            	return M31;
            case 7:
            	return M32;
            case 8:
            	return M33;
            default:
                 throw std::out_of_range("Index must be between 0 and  " + std::to_string(this->ValueCount) + ".");
            }
        }

        float operator()(std::size_t row, std::size_t column) const
        {
            return this->operator[](row * Columns + column);
        }

        float &operator()(std::size_t row, std::size_t column)
        {
            return this->operator[](row * Columns + column);
        }

        std::size_t hash() const
        {
            std::size_t hash = 239;
            hash = hash * 433 + static_cast<std::size_t>(M11);
            hash = hash * 433 + static_cast<std::size_t>(M12);
            hash = hash * 433 + static_cast<std::size_t>(M13);
            hash = hash * 433 + static_cast<std::size_t>(M21);
            hash = hash * 433 + static_cast<std::size_t>(M22);
            hash = hash * 433 + static_cast<std::size_t>(M23);
            hash = hash * 433 + static_cast<std::size_t>(M31);
            hash = hash * 433 + static_cast<std::size_t>(M32);
            hash = hash * 433 + static_cast<std::size_t>(M33);
            return hash;
        }

        bool NearlyEquals(const Matrix3 &other, float epsilon) const
        {
            return std::abs(M11 - other.M11) < epsilon &&
                   std::abs(M12 - other.M12) < epsilon &&
                   std::abs(M13 - other.M13) < epsilon &&
                   std::abs(M21 - other.M21) < epsilon &&
                   std::abs(M22 - other.M22) < epsilon &&
                   std::abs(M23 - other.M23) < epsilon && 
                   std::abs(M31 - other.M31) < epsilon &&
                   std::abs(M32 - other.M32) < epsilon &&
                   std::abs(M33 - other.M33) < epsilon;
        }
    };
} // namespace Syroot::Maths
