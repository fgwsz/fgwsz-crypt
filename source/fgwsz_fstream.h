#ifndef FGWSZ_FSTREAM_H
#define FGWSZ_FSTREAM_H

#include<string>    //::std::string
#include<ios>       //::std::streamsize
#include<fstream>   //::std::ofstream

#include"fgwsz_except.h"

//============================================================================
//文件流读写相关
//============================================================================
namespace fgwsz{
//向正在打开的标准输出文件流写入缓冲区中的内容
inline void std_ofstream_write(
    ::std::ofstream& ofs
    ,char const* src
    ,::std::streamsize count
    ,::std::string const& file_path_string={}
){
    if(!ofs.is_open()){
        FGWSZ_THROW_WHAT("::std::ofstream open "+file_path_string);
    }
    ofs.write(src,count);
    ofs.flush();
    if(!ofs.good()){
        FGWSZ_THROW_WHAT("::std::ofstream write "+file_path_string);
    }
}
//从正在打开的标准输入文件流中读取内容到缓冲区
inline ::std::streamsize std_ifstream_read(
    ::std::ifstream& ifs
    ,char* data
    ,::std::streamsize count
    ,::std::string const& file_path_string={}
){
    if(!ifs.is_open()){
        FGWSZ_THROW_WHAT("::std::ifstream open "+file_path_string);
    }
    ifs.read(data,count);
    auto ret=file.gcount();
    if(!ifs.good()){
        FGWSZ_THROW_WHAT("::std::ifstream read "+file_path_string);
    }
    return ret;
}
}//namespace fgwsz

#endif//FGWSZ_FSTREAM_H
