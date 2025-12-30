#ifndef FGWSZ_ENDIAN_HPP
#define FGWSZ_ENDIAN_HPP

#include<cstdint>//::std::uint8_t

//============================================================================
//字节序相关
//============================================================================
namespace fgwsz{
//字节序辅助类
template<typename Type_>
union EndianHelper{
    ::std::uint8_t byte_array[sizeof(Type_)];
    Type_ data;
};
//检查主机字节序是否为大端序
inline constexpr bool is_big_endian(void)noexcept{
    return ::std::endian::native==::std::endian::big;
}
//检查主机字节序是否为小端序
inline constexpr bool is_little_endian(void)noexcept{
    return ::std::endian::native==::std::endian::little;
}
//将主机字节序转换为同类型的网络字节序
template<typename Type_>
inline constexpr Type_ host_to_net(Type_ host_data){
    if constexpr(::fgwsz::is_big_endian()){
        return host_data;
    }else{
        ::fgwsz::EndianHelper<Type_> host;
        host.data=host_data;
        ::fgwsz::EndianHelper<Type_> net;
        for(::std::size_t index=0;index<sizeof(Type_);++index){
            net.byte_array[sizeof(Type_)-1-index]=
                host.byte_array[index];
        }
        return net.data;
    }
}
//将网络字节序转换为同类型的主机字节序
template<typename Type_>
inline constexpr Type_ net_to_host(Type_ net_data){
    if constexpr(::fgwsz::is_big_endian()){
        return net_data;
    }else{
        ::fgwsz::EndianHelper<Type_> net;
        net.data=net_data;
        ::fgwsz::EndianHelper<Type_> host;
        for(::std::size_t index=0;index<sizeof(Type_);++index){
            host.byte_array[sizeof(Type_)-1-index]=
                net.byte_array[index];
        }
        return host.data;
    }
}
}//namespace fgwsz

#endif//FGWSZ_ENDIAN_HPP
