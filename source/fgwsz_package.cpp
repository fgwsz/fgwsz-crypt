#include<string>    //::std::string
#include<exception> //::std::exception

#include"fgwsz_cout.h"
#include"fgwsz_packer.h"
#include"fgwsz_unpacker.h"

//终端打印帮助信息
inline void help(void){
    ::fgwsz::cout<<
R"(Usages:
    Pack  : -c <output package path> <input path 1> ... <input path N>
    Unpack: -x <input package path> <output directory path>
Examples:
    Pack a file and directory: -c mypkg.fgwsz README.md source
    Unpack                   : -x mypkg.fgwsz output
)";
}

int main(int argc,char* argv[]){
    //输入参数太少
    if(argc<4){
        ::help();
        return -1;
    }
    //检查功能选项
    ::std::string option=argv[1];
    if(option!="-c"&&option!="-x"){
        ::help();
        return -1;
    }
    try{
        if('x'==option[1]){//解包模式
            //排除解包模式输入参数过多的情况
            if(argc>4){
                ::help();
                return -1;
            }
            ::fgwsz::Unpacker unpacker(argv[2]);
            unpacker.unpack_package(argv[3]);
        }else{//打包模式
            ::fgwsz::Packer packer(argv[2]);
            for(int index=3;index<argc;++index){
                packer.pack_path(argv[index]);
            }
        }
    }catch(::std::exception const& e){
        ::fgwsz::cout<<e.what()<<'\n';
        return -1;
    }
    return 0;
}
