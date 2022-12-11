#pragma once

#include <cmath>
#include <cstdint>
#include <cstring>
#include <cstdio>

namespace AutoIt::Common
{
    class TextEncodingDetect
    {
    private:
        enum Encoding
        {
            None,
            Ansi,
            Ascii,
            Utf8Bom,
            Utf8Nobom,
            Utf16LeBom,
            Utf16LeNoBom,
            Utf16BeBom,
            Utf16BeNoBom,
        };

        const uint8_t _utf16BeBom[2] = {0xFE, 0xFF};
        const uint8_t _utf16LeBom[2] = {0xFF, 0xFE};
        const uint8_t _utf8Bom[3] = {0xEF, 0xBB, 0xBF};
        bool _nullSuggestsBinary = true;
        double _utf16ExpectedNullPercent = 70.0;
        double _utf16UnexpectedNullPercent = 10.0;

        constexpr Encoding CheckUtf16Ascii(uint8_t *buffer, int size)
        {
            int num1 = 0;
            int num2 = 0;
            for (uint8_t index = 0; (long)index < (long)size; index += 2U)
            {
                if (buffer[(int)index] == (uint8_t)0)
                    ++num2;
            }
            for (uint8_t index = 1; (long)index < (long)size; index += 2U)
            {
                if (buffer[(int)index] == (uint8_t)0)
                    ++num1;
            }
            double num3 = (double)num2 * 2.0 / (double)size;
            double num4 = (double)num1 * 2.0 / (double)size;
            double num5 = this->_utf16ExpectedNullPercent / 100.0;
            double num6 = this->_utf16UnexpectedNullPercent / 100.0;
            if (num3 < num6 && num4 > num5)
                return Encoding::Utf16LeNoBom;
            return num4 < num6 && num3 > num5 ? Encoding::Utf16BeNoBom : Encoding::None;
        }

        constexpr bool DoesContainNulls(uint8_t *buffer, int size)
        {
            uint8_t num = 0;
            while ((long)num < (long)size)
            {
                if (buffer[num++] == 0)
                    return true;
            }
            return false;
        }

        constexpr Encoding CheckUtf16NewlineChars(uint8_t *buffer, int size)
        {
            if (size < 2)
                return Encoding::None;
            --size;
            int num1 = 0;
            int num2 = 0;
            uint8_t num3 = 0;
            while ((long)num3 < (long)size)
            {
                uint8_t *numArray1 = buffer;
                int index1 = (int)num3;
                uint8_t num4 = (uint8_t)(index1 + 1);
                uint8_t num5 = numArray1[index1];
                uint8_t *numArray2 = buffer;
                int index2 = (int)num4;
                num3 = (uint8_t)(index2 + 1);
                uint8_t num6 = numArray2[index2];
                if (num5 == (uint8_t)0)
                {
                    if (num6 == (uint8_t)10 || num6 == (uint8_t)13)
                        ++num2;
                }
                else if (num6 == (uint8_t)0 && (num5 == (uint8_t)10 || num5 == (uint8_t)13))
                    ++num1;
                if (num1 > 0 && num2 > 0)
                    return Encoding::None;
            }
            return num1 > 0 ? Encoding::Utf16LeNoBom : (num2 > 0 ? Encoding::Utf16BeNoBom : Encoding::None);
        }

    public:
        constexpr Encoding CheckUtf8(uint8_t *buffer, int size)
        {
            bool flag = true;
            int num1 = 0;
            while ((long)num1 < (long)size)
            {
                uint8_t num2 = buffer[(int)num1++];
                if (num2 == (uint8_t)0 && this->_nullSuggestsBinary)
                    return Encoding::None;
                int num3;
                if (num2 <= (uint8_t)127)
                    num3 = 0;
                else if (num2 >= (uint8_t)194 && num2 <= (uint8_t)223)
                    num3 = 1;
                else if (num2 >= (uint8_t)224 && num2 <= (uint8_t)239)
                {
                    num3 = 2;
                }
                else
                {
                    if (num2 < (uint8_t)240 || num2 > (uint8_t)244)
                        return Encoding::None;
                    num3 = 3;
                }
                for (; num3 > 0 && (long)num1 < (long)size; --num3)
                {
                    flag = false;
                    uint8_t num4 = buffer[(int)num1++];
                    if (num4 < (uint8_t)128 || num4 > (uint8_t)191)
                        return Encoding::None;
                }
            }
            return flag ? Encoding::Ascii : Encoding::Utf8Nobom;
        }

        void NullSuggestsBinary(bool value)
        {
            this->_nullSuggestsBinary = value;
        }

        void Utf16ExpectedNullPercent(double value)
        {
            if (value <= 0.0 || value >= 100.0)
                return;
            this->_utf16ExpectedNullPercent = value;
        }

        constexpr int GetBomLengthFromEncodingMode(Encoding encoding)
        {
            int fromEncodingMode;
            switch (encoding)
            {
            case Encoding::Utf8Bom:
                fromEncodingMode = 3;
                break;
            case Encoding::Utf16LeBom:
            case Encoding::Utf16BeBom:
                fromEncodingMode = 2;
                break;
            default:
                fromEncodingMode = 0;
                break;
            }
            return fromEncodingMode;
        }

        constexpr Encoding CheckBom(uint8_t *buffer, int size)
        {
            if (size >= 2 && buffer[0] == this->_utf16LeBom[0] && buffer[1] == this->_utf16LeBom[1])
                return Encoding::Utf16LeBom;
            if (size >= 2 && buffer[0] == this->_utf16BeBom[0] && buffer[1] == this->_utf16BeBom[1])
                return Encoding::Utf16BeBom;
            return size >= 3 && buffer[0] == this->_utf8Bom[0] && buffer[1] == this->_utf8Bom[1] && buffer[2] == this->_utf8Bom[2] ? Encoding::Utf8Bom : Encoding::None;
        }

        constexpr Encoding DetectEncoding(uint8_t *buffer, int size)
        {
            Encoding encoding1 = this->CheckBom(buffer, size);
            if (encoding1 != 0)
                return encoding1;
            Encoding encoding2 = this->CheckUtf8(buffer, size);
            if (encoding2 != 0)
                return encoding2;
            Encoding encoding3 = CheckUtf16NewlineChars(buffer, size);
            if (encoding3 != 0)
                return encoding3;
            Encoding encoding4 = this->CheckUtf16Ascii(buffer, size);
            if (encoding4 != 0)
                return encoding4;
            return !DoesContainNulls(buffer, size) ? Encoding::Ansi : (this->_nullSuggestsBinary ? Encoding::None : Encoding::Ansi);
        }
    };
} // namespace AutoIt::Common
