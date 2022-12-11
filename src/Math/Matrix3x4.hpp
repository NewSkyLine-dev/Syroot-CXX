#pragma once

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

namespace Syroot::Maths
{
    struct Matrix3x4
    {
        static constexpr std::size_t Rows = 3;
        static constexpr std::size_t Columns = 4;
        static constexpr std::size_t ValueCount = 12;
        static constexpr std::size_t SizeInBytes = 48;

        float M11;
        float M12;
        float M13;
        float M14;
        float M21;
        float M22;
        float M23;
        float M24;
        float M31;
        float M32;
        float M33;
        float M34;

        Matrix3x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34)
            : M11(m11), M12(m12), M13(m13), M14(m14), M21(m21), M22(m22), M23(m23), M24(m24), M31(m31), M32(m32), M33(M33), M34(m34)
        {
        }

        static Matrix3x4 Zero()
        {
            return Matrix3x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        }

        bool operator==(const Matrix3x4 &other) const
        {
            return (*this == other);
        }

        bool operator!=(const Matrix3x4 &other) const
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
                return M14;
            case 4:
                return M21;
            case 5:
                return M22;
            case 6:
                return M23;
            case 7:
                return M24;
            case 8:
                return M31;
            case 9:
                return M32;
            case 10:
                return M33;
            case 11:
                return M34;
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
                return M14;
            case 4:
                return M21;
            case 5:
                return M22;
            case 6:
                return M23;
            case 7:
                return M24;
            case 8:
                return M31;
            case 9:
                return M32;
            case 10:
                return M33;
            case 11:
                return M34;
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
            std::size_t hash = 1531;
            hash = hash * 4519 + static_cast<std::size_t>(M11);
            hash = hash * 4519 + static_cast<std::size_t>(M12);
            hash = hash * 4519 + static_cast<std::size_t>(M13);
            hash = hash * 4519 + static_cast<std::size_t>(M14);
            hash = hash * 4519 + static_cast<std::size_t>(M21);
            hash = hash * 4519 + static_cast<std::size_t>(M22);
            hash = hash * 4519 + static_cast<std::size_t>(M23);
            hash = hash * 4519 + static_cast<std::size_t>(M24);
            hash = hash * 4519 + static_cast<std::size_t>(M31);
            hash = hash * 4519 + static_cast<std::size_t>(M32);
            hash = hash * 4519 + static_cast<std::size_t>(M33);
            hash = hash * 4519 + static_cast<std::size_t>(M34);
            return hash;
        }

        bool NearlyEquals(const Matrix3x4 &other, float epsilon) const
        {
            return std::abs(M11 - other.M11) < epsilon &&
                   std::abs(M12 - other.M12) < epsilon &&
                   std::abs(M13 - other.M13) < epsilon &&
                   std::abs(M21 - other.M21) < epsilon &&
                   std::abs(M22 - other.M22) < epsilon &&
                   std::abs(M23 - other.M23) < epsilon;
        }
    };
} // namespace Syroot::Maths
