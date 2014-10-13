// Perch Lake Computer System
// Mark Mohr (markm11@charter.net)
//
// Excerpt from "Data Structures and Algorithms" by Bruno R Preiss.
// Probably the most common way to aggregate data is to use an array.  While the
// C++ programming language does indeed provide built-in support for arrays, that
// support is not without its shortcomings. Arrays in C++ are not first-class data types.
//
// According to Microsoft the .Net Array Class 
// Provides methods for creating, manipulating, searching, and sorting arrays,
// thereby serving as the base class for all arrays in the common language runtime.
//
// The purpose of this class is combining the above descriptions for the Crapo project

#pragma once

namespace System
  {
  template<class T>
  class Array
    {
    private:
      sizet _len;  // Current length
      sizet _base;
      T*    _ptr;  // Pointer to array
    public:
      Array(sizet len = 0);
      Array(const T*, sizet);
      Array(sizet, T);
      Array(const Array<T>& arr);

      // Destructor
      ~Array();
      Array<T>& operator = (const Array<T>& arr);
      const T& operator [] (sizet idx) const;
      T& operator [] (sizet idx);

      bool IsNull() { return _ptr != nullptr ? false : true; }
      bool IsNull() const { return _ptr != nullptr ? false : true; }
      void Set(T value);
      T* ToPtr() { return _ptr; }
      const T* ToConstPtr() const { return _ptr; }
      
      sizet Base() const { return _base; }
      void Base(sizet new_base);
      sizet GetLowerBound();
      sizet GetUpperBound();
      sizet Length() const { return _len; }
      void Length(sizet new_len);

      static void Copy(T*, sizet, T*, sizet, sizet);
      static void Copy(Array<T>&, sizet, Array<T>&, sizet, sizet);
      static int IndexOf(Array<T*>& arr, T& value);
      static int IndexOf(Array<T*>& arr, T& value, sizet startIndex);
      static int IndexOf(Array<T*>& arr, T& value, sizet startIndex, sizet count);

    private:
      void Free();
    };

  template <class T>
  class Array2D
  {
  protected:
    sizet    _numberOfRows;
    sizet    _numberOfColumns;
    Array<T> _array;
  public:
    class Row
    {
    private:
      Array2D& _array2D;
      sizet    _row;
    public:
      Row(Array2D& array2D, sizet row)
        :_array2D(array2D)
        ,_row(row)
        {
        }
      T& operator [] (sizet column) const
        {
        return _array2D.Select(_row, column);
        }
    };
    Array2D(sizet, sizet);
    T& Select(sizet, sizet);
    Row operator [] (sizet);
  };

  typedef Array<bool>    BoolArray;
  typedef Array<byte>    ByteArray;
  typedef Array<sbyte>   SByteArray;
  typedef Array<wchar_t> CharArray;
  typedef Array<int32>   IntArray;
  }
