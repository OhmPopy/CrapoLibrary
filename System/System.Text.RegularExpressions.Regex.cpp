#include "pch.h"
#include "System.Text.RegularExpressions.Regex.h"
#include "System.Text.RegularExpressions.Syntax.Parser.h"
#include "System.Text.RegularExpressions.Syntax.RegularExpression.h"
#include "System.Text.RegularExpressions.RxCompiler.h"
#include "System.Text.RegularExpressions.Match.h"
#include "System.Text.RegularExpressions.IMachineFactory.h"

namespace System
  {
  namespace Text
    {
    namespace RegularExpressions
      {

      FactoryCache Regex::cache(15);      

      Regex::Regex()
        :_groupCount(0)
        ,_gap(0)
        ,_pattern()
        ,_roptions(RegexOptions::None)
        ,_machineFactory(nullptr)
        ,_mapping(nullptr)
        ,_groupNames()
        {
        }

      Regex::Regex(String& pattern, RegexOptions options)
        :_groupCount(0)
        ,_gap(0)
        ,_pattern(pattern)
        ,_roptions(options)
        ,_machineFactory(nullptr)
        ,_mapping(nullptr)
        ,_groupNames()
        {
        ValidateOptions(options);
        Init();
        }

      Regex::~Regex()
        {
        }

      GCMatch Regex::Match(cstring input, int startat)
        {
        String i(input);
        return Match(i, startat);
        }

      GCMatch Regex::Match(String& input, int startat)
        {
        if(startat < 0 || startat > input.Length())
          throw ArgumentOutOfRangeException(L"startat");

        return CreateMachine()->Scan(this, input, startat, input.Length());
        }

      GCIMachine Regex::CreateMachine()
        {
        return _machineFactory->NewInstance();
        }

      void Regex::ValidateOptions(RegexOptions options)
        {
        intptr allopts =
          (intptr)RegexOptions::None |
          (intptr)RegexOptions::IgnoreCase |
          (intptr)RegexOptions::Multiline |
          (intptr)RegexOptions::ExplicitCapture |
          (intptr)RegexOptions::Singleline |
          (intptr)RegexOptions::IgnorePatternWhitespace |
          (intptr)RegexOptions::RightToLeft |
          (intptr)RegexOptions::ECMAScript |
          (intptr)RegexOptions::CultureInvariant;

        intptr ecmaopts =
          (intptr)RegexOptions::IgnoreCase |
          (intptr)RegexOptions::Multiline |
          (intptr)RegexOptions::ECMAScript;

        if(((intptr)options & ~allopts) != 0)
          throw ArgumentOutOfRangeException(L"options");
        if(((intptr)options & (intptr)RegexOptions::ECMAScript) != 0 && ((intptr)options & ~ecmaopts) != 0)
          throw ArgumentOutOfRangeException(L"options");
        }

      void Regex::Init()
        {
        _machineFactory = cache.Lookup(_pattern, _roptions);

        if(_machineFactory == nullptr)
          {
          InitNewRegex();
          } 
        else
          {
          _groupCount = _machineFactory->GroupCount();
          _gap = _machineFactory->Gap();
          _mapping = _machineFactory->Mapping();
          _groupNames = _machineFactory->NamesMapping();
          }
        }

      void Regex::InitNewRegex() 
        {
        _machineFactory = CreateMachineFactory(_pattern, _roptions);
        cache.Add(_pattern, _roptions, _machineFactory);
        _groupCount = _machineFactory->GroupCount();
        _gap = _machineFactory->Gap();
        _mapping = _machineFactory->Mapping();
        _groupNames = _machineFactory->NamesMapping();
        }

      int Regex::DefaultStartat(String& input)
        {
        return (RightToLeft()) ? input.Length() : 0;
        }

      bool Regex::IsMatch(String& input)
        {
        return IsMatch(input, DefaultStartat(input));
        }

      bool Regex::IsMatch(String& input, int32 startat)
        {
        return Match(input, startat)->Success();
        }

      bool Regex::IsMatch(String& input, String& pattern)
        {
        return IsMatch (input, pattern, RegexOptions::None);
        }

      bool Regex::IsMatch(String& input, String& pattern, RegexOptions options)
        {
        Regex re(pattern, options);
        return re.IsMatch(input);
        }

      IMachineFactory* Regex::CreateMachineFactory(String& pattern, RegexOptions options)
        {
        using namespace Syntax;
        Parser parser;
        RegularExpression* regularExpression = parser.ParseRegularExpression(pattern, options);
        ICompiler* compiler = nullptr;
        int x = 0;
        if(x != 1)
          {
          if (((intptr)options & (intptr)RegexOptions::Compiled) != (intptr)RegexOptions::None)
            {
            //compiler = new CILCompiler();
            }
          else
            {
            compiler = new RxCompiler();
            }
          }
        else
          {
          //compiler = new PatternCompiler();
          }
        regularExpression->Compile(compiler, ((intptr)options & (intptr)RegexOptions::RightToLeft) != (intptr)RegexOptions::None);
        IMachineFactory* machineFactory = compiler->GetMachineFactory();
        Collections::Hashtable* hashtable = new Collections::Hashtable();
        machineFactory->Gap(parser.GetMapping(hashtable));
        machineFactory->Mapping(hashtable);
        machineFactory->NamesMapping() = Regex::GetGroupNamesArray(machineFactory->GroupCount(), machineFactory->Mapping());
        return machineFactory;
        }

      StringArray Regex::GetGroupNamesArray(int groupCount, Collections::IDictionary* mapping)
        {
        StringArray group_names(groupCount + 1);
        Collections::IDictionaryEnumerator* de = mapping->GetEnumerator();
        while(de->MoveNext())
          {
          Int32& i = static_cast<Int32&>(*de->Value());
          String& s = static_cast<String&>(*de->Key());
          group_names[(int32)i] = s;
          }
        return group_names;
        }

      bool Regex::RightToLeft()
        { 
        return((intptr)_roptions & (intptr)RegexOptions::RightToLeft) != 0;
        }

      }
    }
  }
