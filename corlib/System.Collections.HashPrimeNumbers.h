#pragma once

namespace System
  {
  namespace Collections
    {
    class CRAPOCOREDLL_API HashPrimeNumbers
      {
      public:
        HashPrimeNumbers();
        ~HashPrimeNumbers();
        static bool TestPrime(int x);
        static int CalcPrime(int x);
        static int ToPrime(int x);
      private:
        static int primeTbl[];
      };
    }
  }

