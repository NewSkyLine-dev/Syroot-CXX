#pragma once

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

namespace Syroot::Maths
{
    struct Matrix2x3
    {
        static constexpr std::size_t Rows = 2;
        static constexpr std::size_t Columns = 3;
        static constexpr std::size_t ValueCount = 6;
        static constexpr std::size_t SizeInBytes = 24;

        float M11;
        float M12;
        float M13;
        float M21;
        float M22;
        float M23;

        Matrix2x3(float m11, float m12, float m13, float m21, float m22, float m23)
            : M11(m11), M12(m12), M13(m13), M21(m21), M22(m22), M23(m23)
        {
        }

        static Matrix2x3 Zero()
        {
            return Matrix2x3(0, 0, 0, 0, 0, 0);
        }

        bool operator==(const Matrix2x3 &other) const
        {
            return (*this == other);
        }

        bool operator!=(const Matrix2x3 &other) const
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
            default:
                 throw std::out_of_range("Index must be between 0 and  " + std::to_string(this->ValueCount) + ".");
            }
        }

        std::size_t hash() const
        {
            std::size_t hash = 167;
            hash = hash * 53 + static_cast<std::size_t>(M11);
            hash = hash * 53 + static_cast<std::size_t>(M12);
            hash = hash * 53 + static_cast<std::size_t>(M13);
            hash = hash * 53 + static_cast<std::size_t>(M21);
            hash = hash * 53 + static_cast<std::size_t>(M22);
            hash = hash * 53 + static_cast<std::size_t>(M23);
            return hash;
        }

        bool NearlyEquals(const Matrix2x3 &other, float epsilon) const
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
