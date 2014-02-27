#include "pch.h"
#include "System.Threading.ActiveObject.h"

namespace System
  {
  namespace Threading
    {
    ActiveObject::ActiveObject()
      :_isDying(false)
      ,_thread(ThreadEntry)
      {
      _thread.Start(this);
      }
    ActiveObject::~ActiveObject()
      {
      }
    uint32 _stdcall ActiveObject::ThreadEntry(void* arg)
      {
      ActiveObject* obj = reinterpret_cast<ActiveObject*>(arg);
      obj->InitThread();
      obj->Run();
      return 0;
      }
    }
  }
