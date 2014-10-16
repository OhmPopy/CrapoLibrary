#pragma once
#include "System.Object.h"

namespace System
  {
  namespace Collections
    {
    class DictionaryEntry : public Object
      {
      private:
        GCObject _key;
		    GCObject _value;
      public:
        DictionaryEntry(GCObject& key, GCObject& value);
        ~DictionaryEntry();
      };
    }
  }
