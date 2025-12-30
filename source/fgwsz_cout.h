#ifndef FGWSZ_COUT_HPP
#define FGWSZ_COUT_HPP

#include<ios>       //::std::ios_base
#include<iostream>  //::std::ostream ::std::cin ::std::cout

//============================================================================
//终端打印相关
//============================================================================
namespace fgwsz{
namespace detail{
static bool const std_cout_init=[](void){
    //关闭与C语言的输入输出流同步
    ::std::ios_base::sync_with_stdio(false);
    //解除cin和cout的绑定
    ::std::cin.tie(nullptr);
    ::std::cout.tie(nullptr);
    return true;
}();
}//namespace fgwsz::detail
inline ::std::ostream& cout=::std::cout;
}//namespace fgwsz

#endif//FGWSZ_COUT_HPP
