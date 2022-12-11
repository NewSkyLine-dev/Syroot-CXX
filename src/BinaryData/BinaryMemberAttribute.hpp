#pragma once

#include <typeinfo>

#include "OffsetOrigin.hpp"
#include "BinaryBooleanFormat.hpp"
#include "BinaryDateTimeFormat.hpp"
#include  "BinaryStringFormat.hpp"

namespace Syroot::BinaryData
{
    class BinaryMemberAttribute
    {
    public:
        static constexpr BinaryMemberAttribute Default();

        int Offset;
        OffsetOrigin OffsetOrigin;
        BinaryBooleanFormat BooleanFormat;
        BinaryDateTimeFormat DateTimeFormat;
        BinaryStringFormat StringFormat;
        int Length;
        bool Strict;
        type_info Converter;
    };
} // namespace Syroot::BinaryData
