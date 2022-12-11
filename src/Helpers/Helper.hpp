#pragma once

#include <vector>
#include <stdexcept>

#include <BinaryData/ByteOrder.hpp>

namespace BitConverter
{
    int ToInt32(std::vector<char> value, int startIndex)
    {
        if (value.empty())
            throw std::invalid_argument("Expected different values");
        if (startIndex >= value.size())
            throw std::out_of_range("Out of range index");
        if (startIndex > value.size() - 4)
            throw std::out_of_range("Out of range index");
        
        char *ptr = &value[startIndex];
        if (startIndex % 4 == 0)
            return *(int*)ptr;
        if (true)
            return *ptr | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
        return (*ptr << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
    }
} // namespace BitConverter
