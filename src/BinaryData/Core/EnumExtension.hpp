#pragma once

#include <typeinfo>
#include <type_traits>

namespace Syroot::BinaryData::Core
{
    class EnumExtensions
    {
    public:
        template <typename T>
        static bool IsValid(T value)
        {
            static_assert(std::is_enum<T>::value, "Argument must be an enumerated type");

            bool flag = false;

            // TODO
            // Check if the value is defined in the enumeration.
            if (flag = value >= 0 && value < __number_of_enumerators(T))
            {
                // Check if the enumeration has the FlagsAttribute applied to it.
                const std::type_info &type_info = typeid(T);

                // Check if the value is a valid combination of flags.
                long num = 0;
                for (int i = 0; i < __number_of_enumerators(T); i++)
                {
                    num |= static_cast<long>(i);
                }
                long int64 = static_cast<long>(value);
                flag = (num & int64) == int64;
            }

            return flag;
        }

    private:
        template <typename T>
        static constexpr std::size_t __number_of_enumerators(T)
        {
            return static_cast<std::size_t>(T::__number_of_enumerators);
        }
    };
}