#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System;

namespace corlibtest
  {
  TEST_CLASS(UnitTestHashTable)
    {
    BEGIN_TEST_CLASS_ATTRIBUTE()
      TEST_CLASS_ATTRIBUTE(L"Namespace", L"System.Collections")
      END_TEST_CLASS_ATTRIBUTE()
    public:
      TEST_METHOD(TestCtor2)
        {
          using namespace Collections;

          {
          bool errorThrown = false;
          try
            {
            Hashtable h((IDictionary*)nullptr);
            }
          catch(ArgumentException)
            {
            errorThrown = true;
            }
          Assert::IsTrue(errorThrown, L"null hashtable error not thrown");
          }

          {
          String keys[4] = { L"this", L"is", L"a", L"test" };
          wchar_t values[4] = { L'a', L'b', L'c', L'd' };
          Hashtable h1;
          int i  = 0;
          for(; i < 4; ++i)
            {
            h1.Add(new String(keys[i]), new Char(values[i]));
            }
          
          for(i = 0; i < 4; ++i)
            {
            String key(keys[i]);
            Object* obj = h1.Get(&key);
            Char* val = reinterpret_cast<Char*>(obj);
            Assert::AreEqual<wchar_t>(values[i], (*val));
            }
          }
        }
    };
  }