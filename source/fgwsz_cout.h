#ifndef FGWSZ_COUT_HPP
#define FGWSZ_COUT_HPP

#include<ios>       //::std::ios_base
#include<iostream>  //::std::ostream ::std::cin ::std::cout

//============================================================================
//终端打印相关
//============================================================================
namespace fgwsz{
namespace detail{
inline ::std::ostream& optimized_cout(void){
    static ::std::ostream& ret=[](void){
        //关闭与C语言的输入输出流同步
        ::std::ios_base::sync_with_stdio(false);
        //解除cin和cout的绑定
        ::std::cin.tie(nullptr);
        ::std::cout.tie(nullptr);
        return ::std::cout;
    }();
    return ret;
}
}//namespace fgwsz::detail
::std::ostream& cout=::fgwsz::detail::optimized_cout();
}//namespace fgwsz

#endif//FGWSZ_COUT_HPP
