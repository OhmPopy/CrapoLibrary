// Perch Lake Computer System

#include "pch.h"
#include "System.Threading.InternalThread.h"

namespace System
  {
  namespace Threading
    {
    InternalThread::InternalThread()
      :_thread_id(0)
      ,_state(ThreadState::Unstarted)
      ,_system_thread_handle(NULL)
      {
      }
    InternalThread::~InternalThread()
      {
      }
    }
  } 
