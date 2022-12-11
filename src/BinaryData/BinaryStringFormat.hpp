#pragma once

namespace Syroot::BinaryData
{
    enum BinaryStringFormat
    {
        VariableLengthPrefix,
        ByteLengthPrefix,
        WordLengthPrefix,
        DwordLengthPrefix,
        ZeroTerminated,
        NoPrefixOrTermination,
    };
} // namespace Syroot::BinaryData
