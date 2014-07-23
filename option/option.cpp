///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013-2014 Dimitry Ishenko
// Distributed under the GNU GPL v2. For full terms please visit:
// http://www.gnu.org/licenses/gpl.html
//
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com

///////////////////////////////////////////////////////////////////////////////////////////////////
#include "option.h"

#include <iomanip>
#include <sstream>
#include <map>
#include <memory>

#include <getopt.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
namespace app
{

///////////////////////////////////////////////////////////////////////////////////////////////////
constexpr int unique_code_min= 1000;

void options::parse(int argc, char* argv[], int& index)
{
    std::vector<struct ::option> long_opt;
    std::vector<std::unique_ptr<char[]>> long_opt_name;

    std::string short_opt(":");

    int unique= unique_code_min;
    std::map<int, pointer> map;

    ////////////////////
    for(reference option: _M_options)
    {
        int code;
        if(option.name())
        {
            code= option.name();
            short_opt+= option.name();

            if(option.arg()==uncertain)
                short_opt+= "::";
            else if(option.arg()==true)
                short_opt+= ":";
        }
        else code= unique++;

        int length= option.longname().size();
        if(length)
        {
            long_opt_name.emplace_back(new char[length+1]);

            option.longname().copy(long_opt_name.back().get(), length);
            long_opt_name.back()[length]=0;

            long_opt.push_back({ long_opt_name.back().get(),
                option.arg()==uncertain? optional_argument: option.arg()? required_argument: no_argument,
            nullptr, code });
        }

        map[code]= &option;
    }
    long_opt.push_back({ nullptr, 0, nullptr, 0 });

    ////////////////////
    try
    {
        optind=1;
        opterr=0;

        while(true)
        {
            int c= getopt_long(argc, argv, short_opt.data(), &long_opt[0], nullptr);
            if(c==-1) break;

            if(c=='?')
                throw invalid_argument("Invalid option");
            else if(c==':')
                throw invalid_argument("Missing argument");

            auto ri= map.find(c);
                if(ri==map.end()) throw invalid_argument("Unexpected option");
            pointer option= ri->second;

            ++option->_M_count;
            if(option->once() && option->count()>1) throw invalid_argument("Extraneous option");

            if(option->arg() != false && optarg) option->_M_assign(optarg);
        }
    }
    catch(std::exception& e)
    {
        index= optind;

        std::string message= e.what();
        message+= " '";
            if(optopt && optopt < unique_code_min) message+= char(optopt); else message+= argv[--index];
        message+= "'";

        throw invalid_argument(message);
    }

    index= optind;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
using std::setw; using std::left; using std::right; using std::endl;

std::string options::usage()
{
    std::ostringstream stream;
    for(const_reference option: _M_options)
    {
        stream << setw(8) << right;
        if(option.name())
            stream << std::string("-")+ option.name()+ (option.longname().size()? ", ": "  ");
        else stream << ' ';

        stream << setw(20) << left;
        if(option.longname().size())
            stream << std::string("--")+ option.longname()+ (option.arg()==uncertain? "[=arg]": option.arg()? "=<arg>": "");
        else stream << ' ';

        stream << option.desc() << std::endl;
    }

    return stream.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
}
