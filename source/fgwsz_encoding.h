#ifndef FGWSZ_ENCODING_H
#define FGWSZ_ENCODING_H

#ifdef _WIN32

#include<string>//::std::string ::std::wstring
#include<vector>//::std::vector
#include<system_error>

#include<windows.h>

namespace fgwsz{

inline ::std::string wide_to_utf8(::std::wstring const& input){
    if(input.empty()){
        return ::std::string();
    }
    //计算需要的UTF-8缓冲区大小
    int utf8_length=::WideCharToMultiByte(
        CP_UTF8,0,input.c_str(),static_cast<int>(input.length())
        ,nullptr,0,nullptr,nullptr
    );
    if(utf8_length==0){
        throw ::std::system_error(
            ::GetLastError(),
            ::std::system_category(),
            "WideCharToMultiByte failed"
        );
    }
    //分配缓冲区并转换
    ::std::vector<char> buffer(utf8_length);
    int result=::WideCharToMultiByte(
        CP_UTF8,0,input.c_str(),static_cast<int>(input.length())
        ,buffer.data(),static_cast<int>(buffer.size()),nullptr,nullptr
    );
    if(result==0){
        throw ::std::system_error(
            ::GetLastError(),
            ::std::system_category(),
            "WideCharToMultiByte failed"
        );
    }
    return ::std::string(buffer.data(),buffer.size());
}
inline ::std::wstring utf8_to_wide(::std::string const& input){
    if(input.empty()){
        return ::std::wstring();
    }
    //计算需要的宽字符缓冲区大小
    int wide_length=::MultiByteToWideChar(
        CP_UTF8,0,input.c_str(),static_cast<int>(input.length()),nullptr,0
    );
    if(wide_length==0){
        throw ::std::system_error(
            ::GetLastError(),
            ::std::system_category(),
            "MultiByteToWideChar failed"
        );
    }
    //分配缓冲区并转换
    ::std::vector<wchar_t> buffer(wide_length);
    int result=::MultiByteToWideChar(
        CP_UTF8,0,input.c_str(),static_cast<int>(input.length())
        ,buffer.data(),static_cast<int>(buffer.size())
    );
    if(result==0){
        throw ::std::system_error(
            ::GetLastError(),
            ::std::system_category(),
            "MultiByteToWideChar failed"
        );
    }
    return ::std::wstring(buffer.data(),buffer.size());
}

}//namespace fgwsz

#endif//_WIN32

#endif//FGWSZ_ENCODING_H
