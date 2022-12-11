#pragma once

namespace Syroot::BinaryData
{
    enum ByteOrder : unsigned short
    {
        BigEndian = 65279,    // 0xFEFF
        LittleEndian = 65534, // 0xFFFE
    };
} // namespace Syroot::BinaryData
