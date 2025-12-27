#include<cstddef>//::std::size_t
#include<stdint>//::std::uint64_t
#include<ios>//::std::ios ::std::streamsize
#include<iostream>//::std::cout ::std::cin
#include<string>//::std::string
#include<vector>//::std::vector
#include<fstream>//::std::ifstream ::std::ofstream
#include<stdexcept>// ::std::runtime_error
#include<filesystem>//::std::filesystem

struct File{
    ::std::filesystem::path relative_path;//归档之后的相对路径
    ::std::vector<char> content;//文件内容
    //移动语义
    File(File&&)noexcept=default;
    File& operator=(File&&)noexcept=default;
};
::File read_file(
    ::std::filesystem::path const& file_path
    ,::std::filesystem::path const& base_path=file_path.parent_path()
){
    //检查输入参数有效性
    ::std::ifstream file(file_path,::std::ios::binary|::std::ios::ate);
    //文件打不开
    if(!file.is_open()){
        throw ::std::runtime_error("Failed to open file:"+file_path.string());
    }
    //基准路径不是目录
    if(!::std::filesystem::is_directory(base_path)){
        throw ::std::runtime_error(
            "Base path isn't directory:"+base_path.string()
        );
    }
    //根据基准路路径和文件路径得到归档之后的相对路径
    auto relative_path=::std::filesystem::proximate(file_path,base_path);
    //设置返回值初始值
    auto ret=::File{relative_path,{}};
    //读取文件内容
    ::std::size_t file_size=file.tellg();
    //文件内容为空,提前返回
    if(0==file_size){
        return ret;
    }
    file.seekg(0);
    //预先分配内存,减少内存分配次数
    ret.content.resize(file_size);
    file.read(
        &(ret.content[0])
        ,static_cast<::std::streamsize>(file_size)
    );
    //文件内容读取不完整
    if(file.gcount()!=file_size){
        throw ::std::runtime_error(
            "File read incomplete:"+file_path.string()
        );
    }
    return ret;
}
::std::vector<::File> read_dir(::std::filesystem::path const& dir_path){
    //检查输入路径是否为目录
    if(!::std::filesystem::is_directory(dir_path)){
        throw ::std::runtime_error(
            "Dir path isn't directory:"+dir_path.string()
        );
    }
    //设置返回值初始值
    ::std::vector<::File> ret={};
    //递归遍历所有的文件进行读取
    try{
        for(::std::filesystem::directory_entry const& dir_entry
            : ::std::filesystem::recursive_directory_iterator(dir_path)
        ){
            //对所有的文件进行读取
            if(!::std::filesystem::is_directory(dir_entry.path())){
                ret.emplace_back(::read_file(dir_entry.path(),dir_path));
            }
        }
    }catch(::std::filesystem::filesystem_error const& e){
        throw ::std::runtime_error(
            "Failed to read files from directory:"+dir_path.string()
        );
    }
    return ret;
}
::std::vector<::File> read_path(::std::filesystem::path const& path){
    //检查输入路径类型
    if(::std::filesystem::is_directory(path)){//目录路径
        return ::read_dir(path);
    }else{//文件路径
        ::std::vector<::File> ret={};
        ret.emplace_back(::read_file(path));
        return ret;
    }
}
::std::vector<::File> read_paths(
    ::std::vector<::std::filesystem::path> const& paths
){
    ::std::vector<::File> ret={};
    for(auto const& path:paths){
        ::std::vector<::File> files=::read_path(path);
        ret.insert(ret.end()
            ,::std::make_move_iterator(files.begin())
            ,::std::make_move_iterator(files.end())
        );
    }
    return ret;
}
::std::vector<char> create_package(::std::vector<::File> const& files){
    //设置返回值初始值
    ::std::vector<char> ret={};
    //预遍历提前分配返回值内存容量
    ::std::uint64_t bytes=0;
    for(auto const& file:files){
        bytes+=16+file.relative_path.string().size()+file.content.size();
    }
    ret.reserve(bytes);
    //遍历写入返回值
    ::std::uint64_t index=0;
    ::std::uint64_t relative_path_bytes=0;
    ::std::uint64_t content_bytes=0;
    for(auto const& file:files){
        auto relative_path_string=file.relative_path.string();
        //写入相对路径的字节数(这部分占用8字节)
        relative_path_bytes=static_cast<::std::uint64_t>(
            relative_path_string.length()
        );
        //首先把uint64_t从主机序转变为网络序
        //把网络序写入char[8]
        //从char[8]插入ret
        //TODO
        index+=8;
        //写入相对路径
        ret.insert(
            ret.end()
            ,relative_path_string.begin()
            ,relative_path_string.begin()+relative_path_bytes
        );
        index+=relative_path_bytes;
        //写入文件内容的字节数(这部分占用8字节)
        content_bytes=static_cast<::std::uint64_t>(file.content.size());
        //首先把uint64_t从主机序转变为网络序
        //把网络序写入char[8]
        //从char[8]插入ret
        //TODO
        index+=8;
        //写入文件内容
        ret.insert(ret.end(),file.content.begin(),file.content.end());
        index+=content_bytes;
    }
    return ret;
}
void write_package(
    ::std::vector<char> const& package
    ,::std::filesystem::path const& package_path
){
    //TODO
}
::std::vector<char> read_package(::std::filesystem::path const& package_path){
    //TODO
}
::std::vector<::File> extract_package(::std::vector<char> const& package){
    //TODO
}
void write_file(::File const& file,::std::filesystem::path output_dir_path){
    //检查输出路径是否为目录
    if(!::std::filesystem::is_directory(output_dir_path)){
        throw ::std::runtime_error(
            "Output dir path isn't directory:"+output_dir_path.string()
        );
    }
    //TODO
    //构建输出文件路径
    //检查输出文件路径的父路径是否存在,如果不存在就创建
    //写入文件内容
}
void write_files(
    ::std::vector<::File> const& files
    ,::std::filesystem::path output_dir_path
){
    //检查输出路径是否为目录
    if(!::std::filesystem::is_directory(output_dir_path)){
        throw ::std::runtime_error(
            "Output dir path isn't directory:"+output_dir_path.string()
        );
    }
    for(auto const& file:files){
        ::write_file(file,output_dir_path);
    }
}
//----------------------------------------------------------------------------
static bool const std_cout_init=[](void){
    //关闭与C语言的输入输出流同步
    ::std::ios_base::sync_with_stdio(false);
    //解除cin和cout的绑定
    ::std::cin.tie(nullptr);
    ::std::cout.tie(nullptr);
    return true;
}();
inline void help(void){
    ::std::cout<<
        "Usage:--encrypt <input file path> <output dir path>\n"
        "Usage:-e <input file path> <output dir path>\n"
        "Usage:--decrypt <input file path> <output dir path>\n";
        "Usage:-d <input file path> <output dir path>\n";
}
//加密文件结构
//[分隔符][加密文件名][分隔符][密钥(分隔符模运算后的加密样式)][分隔符][加密内容]
//首先需要解决一个问题:各个部分之间的分隔符是什么?规定分隔符为x
//x是区间[0,255]中的一个随机数.
//加密的任何内容都不能是分隔符x
//解密的过程如下:
//由于分隔符号是一个字节:所以直接得到分隔符.
//然后根据加密分隔符号对内容进行拆分,得到加密文件名,密钥和加密内容
//然后根据根据密钥解密得到真实的文件名和真实的文件内容
//之后将真实的文件名,根据用户输入的输出路径和真实的文件名,进行写入
//得到真实的文件
//filename包含文件后缀名

//package:[filename][/][bytes(string type)][/][content]
//[encrypted package][key]
//key:[1,255]random

//我想自己制定一个压缩包:
//压缩包的二进制的文件结构如下:
//[A|B|C|D]
//表示单个文件的信息
//A部分是[path_size]
//B部分是[path]
//C部分是[content_size]
//D部分是[content(binary)]
inline ::std::string encrypt_package(
    unsigned char key
    ,::std::string const& package
){
    ::std::string ret;
    ret.reserve(package.size());
    for(unsigned char byte:package){
        ret.push_back(static_cast<unsigned char>((byte^key)+key));
    }
    return ret;
}
inline ::std::string decrypt_package(
    unsigned char key
    ,::std::string const& package
){
    ::std::string ret;
    ret.reserve(package.size());
    for(unsigned char byte:package){
        ret.push_back(static_cast<unsigned char>(byte-key)^key);
    }
    return ret;
}
inline ::std::string encrypt(::std::string const& file_path){
    
}
inline ::File decrypt(::std::string const& file_path){
    
}
int main(int argc,char* argv[]){
    if(argc!=4){
        ::help();
        return -1;
    }
    ::std::string option=argv[1];
    ::std::string input_file_path=argv[2];
    ::std::string output_dir_path=argv[3];
    if("--encrypt"==option||"-e"==option){
        ::write_file(argv[3],::encrypt(::read_file(argv[2])));
    }else if("--decrypt"==option||"-d"==option){
        ::write_file(argv[3],::decrypt(::read_file(argv[2])));
    }else{
        ::help();
        return -1;
    }
    return 0;
}
