#pragma once

#include <stdexcept>
#include <string>
#include <cstddef>
#include <iostream>

namespace Syroot::Maths
{
    struct Matrix2
    {
        static constexpr std::size_t Rows = 2;
        static constexpr std::size_t Columns = 2;
        static constexpr std::size_t ValueCount = 4;
        static constexpr std::size_t SizeInBytes = 16;

        float M11;
        float M12;
        float M21;
        float M22;

        Matrix2(float m11 = 0, float m12 = 0, float m21 = 0, float m22 = 0) : M11(m11), M12(m12), M21(m21), M22(m22) {}

        static Matrix2 Zero() { return Matrix2(); }

        bool operator==(const Matrix2 &other) const
        {
            return (*this == other);
        }

        bool operator!=(const Matrix2 &other) const
        {
            return !(*this == other);
        }

        float operator()(std::size_t row, std::size_t column) const
        {
            return this->operator[](row * Columns + column);
        }

        float &operator()(std::size_t row, std::size_t column)
        {
            return this->operator[](row * Columns + column);
        }

        float operator[](std::size_t index) const
        {
            if (index >= ValueCount)
            {
                throw std::out_of_range("Index must be between 0 and  " + std::to_string(this->ValueCount) + ".");
            }
            return *(&M11 + index);
        }

        float &operator[](std::size_t index)
        {
            if (index >= ValueCount)
            {
                throw std::out_of_range("Index must be between 0 and " + std::to_string(this->ValueCount) + ".");
            }
            return *(&M11 + index);
        }

        std::size_t hash() const
        {
            std::size_t hash = 2339;
            hash = hash * 919 + static_cast<std::size_t>(M11);
            hash = hash * 919 + static_cast<std::size_t>(M12);
            hash = hash * 919 + static_cast<std::size_t>(M21);
            hash = hash * 919 + static_cast<std::size_t>(M22);
            return hash;
        }

        bool NearlyEquals(const Matrix2 &other, float epsilon) const
        {
            return std::abs(M11 - other.M11) < epsilon &&
                   std::abs(M12 - other.M12) < epsilon &&
                   std::abs(M21 - other.M21) < epsilon &&
                   std::abs(M22 - other.M22) < epsilon;
        }
    };
} // namespace Syroot::Maths
