#ifndef FGWSZ_EXCEPT_H
#define FGWSZ_EXCEPT_H

#include<string>            //::std::string
#include<source_location>   //::std::source_location
#include<format>            //::std::format
#include<stdexcept>         //::std::runtime_error

//============================================================================
//异常处理相关
//============================================================================
namespace fgwsz{
//用于错误处理的字符串信息
inline ::std::string what(
    ::std::string const& message
    ,::std::source_location location=::std::source_location::current()
){
    return ::std::format(
        "file: {}({}:{}) `{}`: {}"
        ,location.file_name()
        ,location.line()
        ,location.column()
        ,location.function_name()
        ,message
    );
}
}//namespace fgwsz

//抛出运行时异常(简化宏定义)
#define FGWSZ_THROW_RUNTIME_ERROR(...) do{\
    throw ::std::runtime_error(::fgwsz::what(__VA_ARGS__)); \
}while(0) \
//

#endif//FGWSZ_EXCEPT_H
