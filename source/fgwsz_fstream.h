#ifndef FGWSZ_FSTREAM_H
#define FGWSZ_FSTREAM_H

namespace fgwsz{
void ofsteam_write(
    ::std::ofstream& ofs
    ,char const* src,::std::streamsize count
){
    if(!ofs.is_open()){
        THROW_RUNTIME_ERROR("Ofs open error");
    }
    ofs.write(src,count);
    ofs.flush();
    if(!ofs.good()){
        THROW_RUNTIME_ERROR("Ofs write error");
    }
}
}//namespace fgwsz

#endif//FGWSZ_FSTREAM_H
