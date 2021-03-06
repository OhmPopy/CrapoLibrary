#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System;

namespace corlibtest
  {
  TEST_CLASS(UnitTestUTF8Encoding)
    {
    public:

      TEST_METHOD(TestEncodingGetBytes1)
        {
        using namespace Text;
        UTF8Encoding utf8Enc;
        String UniCode = L"\x0041\u2262\u0391\x002E";

        // "A<NOT IDENTICAL TO><ALPHA>." may be encoded as 41 E2 89 A2 CE 91 2E 
        // see (RFC 2044)
        ByteArray utf8Bytes = utf8Enc.GetBytes(UniCode);

        Assert::AreEqual<byte>(0x41, utf8Bytes[0], L"UTF #1");
        Assert::AreEqual<byte>(0xE2, utf8Bytes[1], L"UTF #2");
        Assert::AreEqual<byte>(0x89, utf8Bytes[2], L"UTF #3");
        Assert::AreEqual<byte>(0xA2, utf8Bytes[3], L"UTF #4");
        Assert::AreEqual<byte>(0xCE, utf8Bytes[4], L"UTF #5");
        Assert::AreEqual<byte>(0x91, utf8Bytes[5], L"UTF #6");
        Assert::AreEqual<byte>(0x2E, utf8Bytes[6], L"UTF #7");
        }

      TEST_METHOD(TestEncodingGetBytes2)
        {
        using namespace Text;
        UTF8Encoding utf8Enc;
        String UniCode = L"\x0048\x0069\x0020\x004D\x006F\x006D\x0020\u263A\x0021";

        // "Hi Mom <WHITE SMILING FACE>!" may be encoded as 48 69 20 4D 6F 6D 20 E2 98 BA 21 
        // see (RFC 2044)
        ByteArray utf8Bytes(11);

        CharArray chars = UniCode.ToCharArray();
        int ByteCnt = utf8Enc.GetBytes(chars, 0, UniCode.Length(), utf8Bytes, 0);
        Assert::AreEqual<int>(11, ByteCnt, L"UTF #1");
        Assert::AreEqual<byte>(0x48, utf8Bytes[0], L"UTF #2");
        Assert::AreEqual<byte>(0x69, utf8Bytes[1], L"UTF #3");
        Assert::AreEqual<byte>(0x20, utf8Bytes[2], L"UTF #4");
        Assert::AreEqual<byte>(0x4D, utf8Bytes[3], L"UTF #5");
        Assert::AreEqual<byte>(0x6F, utf8Bytes[4], L"UTF #6");
        Assert::AreEqual<byte>(0x6D, utf8Bytes[5], L"UTF #7");
        Assert::AreEqual<byte>(0x20, utf8Bytes[6], L"UTF #8");
        Assert::AreEqual<byte>(0xE2, utf8Bytes[7], L"UTF #9");
        Assert::AreEqual<byte>(0x98, utf8Bytes[8], L"UTF #10");
        Assert::AreEqual<byte>(0xBA, utf8Bytes[9], L"UTF #11");
        Assert::AreEqual<byte>(0x21, utf8Bytes[10], L"UTF #12");
        }

      TEST_METHOD(TestDecodingGetChars1)
        {
        using namespace Text;
        UTF8Encoding utf8Enc;
        // 41 E2 89 A2 CE 91 2E may be decoded as "A<NOT IDENTICAL TO><ALPHA>." 
        // see (RFC 2044)
        byte utf8Bytes[] = {0x41, 0xE2, 0x89, 0xA2, 0xCE, 0x91, 0x2E};
        ByteArray bytes((byte*)utf8Bytes, 7);
        CharArray UniCodeChars = utf8Enc.GetChars(bytes);

        Assert::AreEqual<wchar_t>(0x0041, UniCodeChars [0], L"UTF #1");
        Assert::AreEqual<wchar_t>(0x2262, UniCodeChars [1], L"UTF #2");
        Assert::AreEqual<wchar_t>(0x0391, UniCodeChars [2], L"UTF #3");
        Assert::AreEqual<wchar_t>(0x002E, UniCodeChars [3], L"UTF #4");
        }

    };
  }