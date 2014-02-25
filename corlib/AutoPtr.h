// Perch Lake Computer System

#pragma once

template<class T>
class AutoPtr
  {
  public:
    AutoPtr(T* ptr = nullptr, bool isMutable = true)
      :_ptr(ptr)
      ,_isMutable(isMutable)
      {
      }
    ~AutoPtr()
      {
      delete _ptr;
      }
    T* operator->() { return _ptr; }
    T* Get() { return _ptr; }
    void Set(T* ptr = nullptr)
      {
      if(_isMutable)
        {
        if(_ptr != nullptr)
          delete _ptr;
        _ptr = ptr;
        }
      }
  private:
    bool _isMutable;
    T*   _ptr;
  };