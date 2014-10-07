#pragma once
#include "System.Text.RegularExpressions.RegexOptions.h"
#include "System.Text.RegularExpressions.Syntax.RegularExpression.h"

namespace System
  {
  namespace Text
    {
    namespace RegularExpressions
      {
      namespace Syntax
        {
        class Assertion;
        class Parser
          {
          public:
            Parser();
            ~Parser();
            RegularExpression* ParseRegularExpression(String pattern, RegexOptions options);
            int GetMapping(Collections::Hashtable* mapping);
          private:
            void ParseGroup(Group* group, RegexOptions options, Assertion* assertion);
            void ResolveReferences();
            void ConsumeWhitespace(bool /*ignore*/);
            static bool IsIgnorePatternWhitespace(RegexOptions /*options*/);
          private:
            String                 _pattern;
            int                    _ptr;
            int                    _numGroups;
            int                    _gap;
            Collections::ArrayList _caps;
            Collections::Hashtable _refs;
          };
        }
      }
    }
  }