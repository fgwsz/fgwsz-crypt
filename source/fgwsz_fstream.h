#ifndef FGWSZ_FSTREAM_H
#define FGWSZ_FSTREAM_H

#include<cstdint>   //::std::uint64_t

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
        FGWSZ_THROW_WHAT("::std::ofstream isn't open: "+file_path_string);
    }
    //count为0也要写入,因为count==0,代表ofs第一次写入时需要创建空文件
    ofs.write(src,count);
    ofs.flush();
    if(!ofs.good()){
        if(ofs.bad()){
            FGWSZ_THROW_WHAT(
                "::std::ofstream write error(badbit): "+file_path_string
            );
        }else if(ofs.fail()){
            FGWSZ_THROW_WHAT(
                "::std::ofstream write error(failbit): "+file_path_string
            );
        }
    }
}
//从正在打开的标准输入文件流中读取内容到缓冲区
inline ::std::uint64_t std_ifstream_read(
    ::std::ifstream& ifs
    ,char* data
    ,::std::streamsize count
    ,::std::string const& file_path_string={}
){
    if(!ifs.is_open()){
        FGWSZ_THROW_WHAT("::std::ifstream isn't open: "+file_path_string);
    }
    if(count==0){
        return 0;
    }
    ifs.read(data,count);
    auto ret=static_cast<::std::uint64_t>(ifs.gcount());
    //只有在发生严重错误或者读取完全失败时才抛出异常
    if(ifs.bad()){
        FGWSZ_THROW_WHAT(
            "::std::ifstream read error(badbit): "+file_path_string
        );
    }
    //如果读取失败且没有读取到任何数据,也抛出异常
    if(ifs.fail()&&ret==0&&!ifs.eof()){
        //注意:这里检查!ifs.eof(),
        //因为如果是因为EOF而失败,且ret==0,那是正常情况
        //例如,文件当前位置已经在末尾,尝试读取会立即失败
        FGWSZ_THROW_WHAT(
            "::std::ifstream read error(failbit): "+file_path_string
        );
    }
    return ret;
}
}//namespace fgwsz

#endif//FGWSZ_FSTREAM_H
