#pragma once

#include <iostream>
#include <version>
#if __cpp_lib_source_location >= 201907L
#include <source_location>
#endif
#define TRACE() std::cerr << __PRETTY_FUNCTION__ << '\n'

namespace fudge {
#if __cpp_lib_source_location >= 201907L
    using std::source_location;
#else
    struct source_location {
        static source_location current(){ return source_location{}; };
        std::string file_name() { return ""; }
        std::string function_name() { return ""; }
        int line() { return 0; }
        int column() { return 0; }
    };
#endif
}
void WHERE(fudge::source_location loc=fudge::source_location::current()){
    std::cerr << loc.file_name() << "("
            << loc.line() << ":"
            << loc.column() << ") '"
            << loc.function_name() << "'\n";
}

template <typename T>
void WHAT(std::string s="", fudge::source_location loc=fudge::source_location::current()){
    std::cerr << s << '\n';
    WHERE(loc);
    TRACE();
}

template <typename T>
void SHOW_IT_TAG(std::string s="", fudge::source_location loc=fudge::source_location::current()){
    if(!s.empty())std::cerr << s << '\n';
    WHERE(loc);
    std::string tag {"unknown"};
#if __cpp_lib_concepts >= 202002L
    if(std::contiguous_iterator<T>){
        tag = "contiguous";
    }
    else if(std::random_access_iterator<T>){
        tag = "random_access";
    }
    else if(std::bidirectional_iterator<T>){
        tag = "bidirectional";
    }
    else if(std::forward_iterator<T>){
        tag = "forward";
    }
    else if(std::input_iterator<T>){
        tag = "input";
    }
#endif
    std::cerr << tag << "_iterator" << '\n';
}

template <typename T>
void SHOW_ORDERING(std::string s="", fudge::source_location loc=fudge::source_location::current()){
    if(!s.empty())std::cerr << s << '\n';
    WHERE(loc);
    std::string tag {"unknown"};
#if __cpp_lib_concepts >= 202002L
    if(std::same_as<T,std::weak_ordering>){
        tag = "weak";
    }
    else if(std::same_as<T,std::strong_ordering>){
        tag = "strong";
    }
    else if(std::same_as<T,std::partial_ordering>){
        tag = "partial";
    }
#endif
    std::cerr << tag << "_ordering" << '\n';
}

