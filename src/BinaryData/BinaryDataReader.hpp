#pragma once

#include "ByteOrder.hpp"
#include "ByteOrderHelper.hpp"
#include "BinaryBooleanFormat.hpp"
#include "BinaryDateTimeFormat.hpp"
#include "BinaryStringFormat.hpp"
#include "BinaryMemberAttribute.hpp"
#include "BinaryConverterCache.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <chrono>
#include <functional>
#include <codecvt>
#include <numeric>
#include <array>
#include <ctime>

#include "Helpers/Helper.hpp"

enum SeekOrigin
{
    Begin,
    Current,
    End,
};

namespace Syroot::BinaryData
{
    class BinaryDataReader
    {
    private:
        ByteOrder byteOrder_;
        std::istream &input_;
        std::string Encoding;
        bool leaveOpen_;
        bool NeedsReversion;

        template <typename T>
        std::vector<T> ReadMultiple(int count, std::function<T()> readFunc)
        {
            std::vector<T> objArray(count);
            for (int index = 0; index < count; ++index)
                objArray.push_back(readFunc(*this));
            return objArray;
        }

        double DecimalFromBytes(std::vector<char> bytes)
        {
            if (bytes.size() < 16)
                throw std::invalid_argument("Not enough bytes to convert to decimal form");
            std::vector<int> bits(4);
            for (int startIndex = 0; startIndex < 16; startIndex += 4)
                bits[startIndex / 4] = BitConverter::ToInt32(bytes, startIndex);
            return bits[3] + (double)bits[2] / 100000000 + (double)bits[1] / 1000000000000 + (double)bits[0] / 10000000000000000;
        }

        uint8_t ReadByte()
        {
            if (!input_)
                throw std::runtime_error("FileNotOpen");
            int num = input_.get();
            if (num == EOF)
                throw std::runtime_error("EndOfFile");
            return static_cast<uint8_t>(num);
        }

        std::vector<char> ReadBytes(size_t numBytes)
        {
            std::vector<char> bytes(numBytes);

            input_.read(reinterpret_cast<char *>(bytes.data()), numBytes);

            input_.seekg(numBytes, std::ios_base::cur);

            return bytes;
        }

        constexpr int Read7BitEncodedInt()
        {
            int num, num2 = 0;
            char b;
            do
            {
                if (num2 == 35)
                    throw new std::runtime_error("Format bad");
                b = ReadByte();
            } while ((b & 0x80u) != 0);
            return num;
        }

        std::string ReadStringInternal(int length, const std::string &encoding)
        {
            // Create an instance of the std::locale class for the given encoding
            std::locale loc(encoding);

            // Create an instance of the std::codecvt facet for the given encoding
            const std::codecvt<wchar_t, char, std::mbstate_t> &facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);

            // Calculate the number of bytes in the encoded string
            std::mbstate_t state;
            const int bytes = length * std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc).length(state, "a", "a", 254);

            // Read the encoded bytes from the input stream
            std::vector<char> buffer = ReadBytes(bytes);

            // Convert the encoded bytes to a wide string
            std::wstring wstr(length, L'\0');

            const char *from_next = nullptr;
            wchar_t *to_next = nullptr;

            // Call the in member function of the std::codecvt facet to convert the encoded bytes to a wide string.
            // TODO
            const auto res = facet.in(state, buffer.data(), buffer.data() + buffer.size(), from_next, wstr.data(), wstr.data() + wstr.size(), to_next);

            // Check if the conversion was successful
            if (res != std::codecvt_base::ok)
            {
                // If not, throw an exception
                throw std::runtime_error("Error converting string");
            }

            // Return the converted wide string as a standard string
            return std::string(wstr.begin(), wstr.end());
        }

        std::string ReadZeroTerminatedString()
        {
            std::string result;
            char ch;

            // Read each character from the input stream until we reach the zero terminator
            while (input_.get(ch) && ch != '\0')
                result.push_back(ch);
            return result;
        }

    public:
        BinaryDataReader(std::istream &input)
            : BinaryDataReader(input, std::string(), false)
        {
        }

        BinaryDataReader(std::istream &input, bool leaveOpen)
            : BinaryDataReader(input, std::string(), leaveOpen)
        {
        }

        BinaryDataReader(std::istream &input, const std::string &encoding)
            : BinaryDataReader(input, encoding, false)
        {
        }

        BinaryDataReader(std::istream &input, const std::string &encoding, bool leaveOpen)
            : input_(input), Encoding(encoding), leaveOpen_(leaveOpen)
        {
            this->Encoding = encoding;
            this->byteOrder_ = ByteOrderHelper::SystemByteOrder();
        }

        void ByteOrder(ByteOrder value)
        {
            this->byteOrder_ = value;
            this->NeedsReversion = this->byteOrder_ != ByteOrderHelper::SystemByteOrder();
        }

        std::string Encoding() const
        {
            return this->Encoding;
        }

        bool EndOfStream()
        {
            return this->input_.tellg() >= this->input_.seekg(0, this->input_.end).tellg();
        }

        long Length() const
        {
            return this->input_.seekg(0, this->input_.end).tellg();
        }

        long Position() const
        {
            return this->input_.tellg();
        }

        void Position(long value)
        {
            this->input_.seekg(value, this->input_.beg);
        }

        long Seek(long offset, SeekOrigin origin)
        {
            std::ios_base::seekdir dir;
            switch (origin)
            {
            case SeekOrigin::Begin:
                dir = this->input_.beg;
                break;
            case SeekOrigin::Current:
                dir = this->input_.cur;
                break;
            case SeekOrigin::End:
                dir = this->input_.end;
                break;
            }
            this->input_.seekg(offset, dir);
            return this->input_.tellg();
        }

        long Seek(long offset)
        {
            return this->Seek(offset, SeekOrigin::Current);
        }

        void Align(int alignment)
        {
            this->Seek((-this->Position() % (long)alignment + (long)alignment) % (long)alignment);
        }

        short ReadInt16()
        {
            char n[2];
            if (!this->NeedsReversion)
                return this->input_.read(reinterpret_cast<char *>(&n), sizeof(short)).tellg();
            else
            {
                this->input_.read(n, 2);
                std::reverse(n, n + 2);
                return *reinterpret_cast<short *>(n);
            }
        }

        int ReadInt32()
        {
            char n[2];
            if (!this->NeedsReversion)
                return this->input_.read(reinterpret_cast<char *>(&n), sizeof(int)).tellg();
            else
            {
                this->input_.read(n, 2);
                std::reverse(n, n + 2);
                return *reinterpret_cast<int *>(n);
            }
        }

        bool ReadBoolean(BinaryBooleanFormat format)
        {
            switch (format)
            {
            case BinaryBooleanFormat::NonZeroByte:
                return this->input_.get();
            case BinaryBooleanFormat::NonZeroWord:
                return this->ReadInt16() != 0;
            case BinaryBooleanFormat::NonZeroDword:
                return this->ReadInt32() != 0;
            default:
                throw std::invalid_argument("The specified binary boolean format is invalid.");
            }
        }

        std::vector<bool> ReadBooleans(int count, BinaryBooleanFormat format)
        {
            std::vector<bool> flagArray(count);
            for (int i = 0; i < flagArray.size(); ++i)
                flagArray[i] = this->ReadBoolean(format);
            return flagArray;
        }

        std::vector<bool> ReadBooleans(int count)
        {
            // Use a lambda function as the third argument to ReadMultiple
            return ReadMultiple<bool>(count, [&]
                                      {
                char buffer[1];
                input_.read(buffer, 1);
                return buffer[0] != 0; });
        }

        long ReadInt64()
        {
            char n[2];
            if (!this->NeedsReversion)
            {
                return this->input_.read(reinterpret_cast<char *>(&n), sizeof(long)).tellg();
            }
            else
            {
                this->input_.read(n, 8);
                std::reverse(n, n + 8);
                return *reinterpret_cast<long *>(n);
            }
        }

        uint8_t ReadUInt32()
        {
            char n[4];
            if (!this->NeedsReversion)
            {
                return this->input_.read(reinterpret_cast<char *>(&n), sizeof(uint8_t)).tellg();
            }
            else
            {
                this->input_.read(n, 4);
                std::reverse(n, n + 4);
                return *reinterpret_cast<uint8_t *>(n);
            }
        }

        std::tm ReadDateTime(BinaryDateTimeFormat format)
        {
            if (format == BinaryDateTimeFormat::NetTicks)
            {
                // Read the number of ticks from the input stream
                int64_t ticks = 0;
                input_.read(reinterpret_cast<char *>(&ticks), sizeof(int64_t));

                // Convert the ticks to a time_t value
                // and return it as a std::tm object
                time_t t = ticks / 10000000 - 62135596800;
                return *std::localtime(&t);
            }
            else if (format == BinaryDateTimeFormat::CTime)
            {
                // Read the number of seconds from the input stream
                uint32_t seconds = 0;
                input_.read(reinterpret_cast<char *>(&seconds), sizeof(uint32_t));

                // Convert the seconds to a time_t value
                // and return it as a std::tm object
                time_t t = seconds;
                return *std::localtime(&t);
            }
            else
            {
                // The format is invalid, so throw an exception
                throw std::invalid_argument("The specified binary date time format is invalid.");
            }
        }

        std::tm ReadDateTime()
        {
            return this->ReadDateTime(BinaryDateTimeFormat::NetTicks);
        }

        std::vector<std::tm> ReadDateTimes(int count)
        {
            std::vector<std::tm> dateTimeArray(count);
            for (int index = 0; index < dateTimeArray.size(); index++)
                dateTimeArray[index] = ReadDateTime();
            return dateTimeArray;
        }

        std::vector<std::tm> ReadDateTimes(int count, BinaryDateTimeFormat format)
        {
            std::vector<std::tm> dateTimeArray(count);
            for (int index = 0; index < dateTimeArray.size(); index++)
                dateTimeArray[index] = ReadDateTime(format);
            return dateTimeArray;
        }

        template <typename T>
        T ReadObject()
        {
            // Define the lambda function
            auto readObjectFunc = []() -> T
            {
                // Call ReadObject with the appropriate arguments
                return (T)ReadObject(nullptr, BinaryMemberAttribute::Default, typeid(T));
            };

            return readObjectFunc();
        }

        std::string ReadString(BinaryStringFormat format, std::string encoding)
        {
            switch (format)
            {
            case BinaryStringFormat::VariableLengthPrefix:
                return this->ReadStringInternal(this->Read7BitEncodedInt(), encoding);
            case BinaryStringFormat::ByteLengthPrefix:
                return this->ReadStringInternal(this->ReadByte(), encoding);
            case BinaryStringFormat::WordLengthPrefix:
                return this->ReadStringInternal(this->ReadInt16(), encoding);
            case BinaryStringFormat::DwordLengthPrefix:
                return this->ReadStringInternal(this->ReadInt32(), encoding);
            case BinaryStringFormat::ZeroTerminated:
                return this->ReadZeroTerminatedString();
            case BinaryStringFormat::NoPrefixOrTermination:
                throw new std::out_of_range("NoPrefixOrTermination cannot be used for read operations if no length has been specified.");
            default:
                throw new std::out_of_range("The specified binary string format is invalid.");
            }
        }
    };
} // namespace Syroot::BinaryData
