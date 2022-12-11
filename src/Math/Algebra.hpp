#pragma once

#include <cmath>

namespace Syroot::Maths
{
    class Algebra
    {
    public:
        static constexpr float Pi = 3.14159274f;
        static constexpr float PiOver2 = 1.57079637f;
        static constexpr float PiOver4 = 0.7853982f;
        static constexpr float PiOver8 = 0.3926991f;
        static constexpr float _degreesToRadiansFactor = 0.0174532924f;
        static constexpr float _radiansToDegreesFactor = 57.2957764f;
        static constexpr float _floatEqualityEpsilon = 1E-05f;

        static int Clamp(int value, int min, int max)
        {
            return value < min ? min : (value > max ? max : value);
        }

        static float Clamp(float value, float min, float max)
        {
            return (double)value < (double)min ? min : ((double)value > (double)max ? max : value);
        }

        static float Sin(float value)
        {
            return (float)std::sin((double)value);
        }

        static float Cos(float value)
        {
            return (float)std::cos((double)value);
        }

        static float Tan(float value)
        {
            return (float)std::tan((double)value);
        }

        static float Lerp(float a, float b, float factor)
        {
            return a + (b - a) * factor;
        }

        static float DegreesToRadians(float degrees)
        {
            return degrees * ((float)std::acos(-1) / 180.0f);
        }

        static float RadiansToDegrees(float radians)
        {
            return radians * 57.2957764f;
        }

        static bool NearlyEquals(float current, float other)
        {
            float num1 = std::abs(current);
            float num2 = std::abs(other);
            float num3 = std::abs(current - other);
            if ((double)current == (double)other)
            {
                return true;
            }
            return (double)current == 0.0 || (double)other == 0.0 || (double)num3 < std::numeric_limits<double>::lowest() ? (double)num3 < -1.7976930894487672E+303 : (double)num3 / ((double)num1 + (double)num2) < 9.9999997473787516E-06;
        }
    };
} // namespace Syroot::Maths
