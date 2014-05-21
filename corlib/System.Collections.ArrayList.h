#pragma once
#include "System.Object.h"
#include "System.Collections.IList.h"

namespace System
  {
  namespace Collections
    {
    class ArrayList : public IList
      {
      public:
        ArrayList();
        ArrayList(sizet capacity);
        virtual ~ArrayList();
        // From ICollection
        virtual sizet Count() override;
        virtual bool IsSynchronized() override;
        // From IList
        virtual void Clear() override;
      private:
        void Free();
      private:
        sizet           _size;
        int             _version;
        Array<Object*>  _items;
      };
    }
  }
