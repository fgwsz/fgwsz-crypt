#include<cstddef>//::std::size_t
#include<ios>//::std::ios ::std::streamsize
#include<iostream>//::std::cout
#include<string>//::std::string
#include<vector>//::std::vector
#include<fstream>//::std::ifstream ::std::ofstream
#include<stdexcept>// ::std::runtime_error

void encrypt(
    ::std::string const& input_file_path
    ,::std::string const& output_file_path
);
void decrypt(
    ::std::string input_file_path
    ,::std::string output_file_path
);
::std::string read_file(::std::string const& file_path);
void write_file(::std::string const& file_path,::std::string const& content);
::std::vector<unsigned char> _encrypt
    (::std::vector<unsigned char> const& content);
::std::vector<unsigned char> _decrypt
    (::std::vector<unsigned char> const& content);
void help(void);

int main(int argc,char* argv[]){
    if(argc!=4){
        ::help();
        return -1;
    }
    ::std::string option=argv[1];
    if("--encrypt"==option||"-e"==option){
        ::encrypt(argv[2],argv[3]);
    }else if("--decrypt"==option||"-d"==option){
        ::decrypt(argv[2],argv[3]);
    }else{
        ::help();
        return -1;
    }
    return 0;
}

void help(void){
    ::std::cout<<
        "Usage:--encrypt <input file path> <output file path>\n"
        "Usage:--decrypt <input file path> <output file path>\n";
        "Usage:-e <input file path> <output file path>\n"
        "Usage:-d <input file path> <output file path>\n";
}
::std::vector<unsigned char> read_file(::std::string const& file_path){
    ::std::ifstream file(file_path,::std::ios::binary|::std::ios::ate);
    if(!file.is_open()){
        throw ::std::runtime_error("Can't open file:"+file_path);
    }
    ::std::size_t file_size=file.tellg();
    if(0==file_size){
        return {};
    }
    file.seekg(0);
    ::std::vector<unsigned char> content;
    content.resize(file_size);
    file.read(
        reinterpret_cast<char*>(&content[0])
        ,static_cast<::std::streamsize>(file_size)
    );
    if(file.gcount()!=file_size){
        throw ::std::runtime_error("文件读取不完整:"+file_path);
    }
    return content;
}
void write_file(
    ::std::string const& file_path
    ,::std::vector<unsigned char>& content
){
    ::std::ofstream file(file_path,::std::ios::binary|::std::ios::trunc);
    if(!file.is_open()){
        throw ::std::runtime_error("Can't open file:"+file_path);
    }
    if(content.empty()){
        return;
    }
    file.write(
        reinterpret_cast<char const*>(content.data())
        ,static_cast<::std::streamsize>(content.size())
    );
    if(!file.good()){
        throw ::std::runtime_error("Write failed to file:"+file_path);
    }
}
void encrypt(
    ::std::string const& input_file_path
    ,::std::string const& output_file_path
){
    ::std::vector<unsigned char> input_content=::read_file(input_file_path);
    ::std::vector<unsigned char> output_content=::_encrypt(content);
}
void decrypt(
    ::std::string input_file_path
    ,::std::string output_file_path
){
    
}
