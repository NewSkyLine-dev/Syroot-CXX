#pragma once

#include <climits>
#include <cstdint>

#include "ByteOrder.hpp"

namespace Syroot::BinaryData
{
    class ByteOrderHelper
    {
    private:
        static ByteOrder systemByteOrder_;

    public:
        static ByteOrder SystemByteOrder()
        {
            if (systemByteOrder_ == (ByteOrder)0)
            {
                uint32_t value = 1;
                systemByteOrder_ = *reinterpret_cast<uint8_t *>(&value) == 1 ? ByteOrder::LittleEndian : ByteOrder::BigEndian;
            }
        }
    };
} // namespace Syroot::BinaryData