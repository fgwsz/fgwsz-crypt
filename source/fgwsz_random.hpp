#ifndef FGWSZ_RANDOM_HPP
#define FGWSZ_RANDOM_HPP

#include<random>    //::std::uniform_int_distribution ::std::random_device
                    //::std::mt19937

//============================================================================
//随机数生成相关
//============================================================================
namespace fgwsz{
//生成类型为NumberType_,取值范围为闭区间[begin,finish]的随机数
template<typename NumberType_>
inline NumberType_ random(NumberType_ const& begin,NumberType_ const& finish){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<NumberType_> distrib(begin,finish);
    return distrib(gen);
}
}//namespace fgwsz

#endif//FGWSZ_RANDOM_HPP
