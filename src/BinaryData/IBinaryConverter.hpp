#pragma once

#include "BinaryDataReader.hpp"
#include "BinaryDataWriter.hpp"
#include "BinaryMemberAttribute.hpp"

namespace Syroot::BinaryData
{
    class IBinaryConverter
    {
    public:
        template <typename T>
        T Read(BinaryDataReader reader, T object, BinaryMemberAttribute memberAttribute);

        template <typename T>
        void Write(
            BinaryDataWriter writer,
            T instance,
            BinaryMemberAttribute memberAttribute,
            T value);
    };
} // namespace Syroot::BinaryData
