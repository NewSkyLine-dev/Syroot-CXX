#pragma once

#include <typeinfo>
#include <type_traits>
#include <vector>

namespace Syroot::BinaryData::Core
{
    class TypeExtensions
    {
        template <typename T>
        static bool IsEnumerable()
        {
            // Check if the type is a string.
            if (std::is_same<T, std::string>::value)
            {
                return false;
            }

            // Check if the type is an array.
            if (std::is_array<T>::value)
            {
                return true;
            }

            // Check if the type is a subclass of IEnumerable.
            return std::is_base_of<std::vector<typename T::value_type>, T>::value;
        }

        template <typename T>
        typename T::value_type GetEnumerableElementType()
        {
            static_assert(IsEnumerable<T>(), "T must be an enumerable type");

            // Return the element type of an array.
            if (std::is_array<T>::value)
            {
                return std::remove_reference<decltype(*std::begin(std::declval<T>()))>::type();
            }

            // Return the element type of an IEnumerable.
            return std::vector<typename T::value_type>::value_type();
        }
    };
} // namespace Syroot::BinaryData::Core