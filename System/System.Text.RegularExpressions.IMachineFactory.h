#pragma once

namespace System
  {
  namespace Text
    {
    namespace RegularExpressions
      {
      class Regex;
      class Match;
      class IMachine
        {
        public:
          virtual Match* Scan(Regex* regex, String text, int start, int end) = 0;
        }; 

      class IMachineFactory : public Object
        {
        public:
        virtual Collections::IDictionary* Mapping() = 0;     // get
        virtual void Mapping(Collections::IDictionary*) = 0; // set
        virtual int32 GroupCount() = 0;                      // get
        virtual int32 Gap() = 0;                             // get
        virtual void Gap(int32) = 0;                         // set
        virtual StringArray& NamesMapping() = 0;             // get
        virtual void NamesMapping(StringArray&) = 0;         // set
        virtual IMachine* NewInstance() = 0;
        };
      }
    }
  }