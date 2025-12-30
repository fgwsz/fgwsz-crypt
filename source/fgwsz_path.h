#ifndef FGWSZ_PATH_H
#define FGWSZ_PATH_H

#include<filesystem>//::std::filesystem

#include"fgwsz_except.h"//FGWSZ_THROW_WHAT

//============================================================================
//路径操作相关
//============================================================================
namespace fgwsz{
inline void path_assert_exists(::std::filesystem::path const& path){
    if(!::std::filesystem::exists(path)){
        FGWSZ_THROW_WHAT("path doesn't exist: "+path.string());
    }
}
inline void path_assert_not_exists(::std::filesystem::path const& path){
    if(::std::filesystem::exists(path)){
        FGWSZ_THROW_WHAT("path does exist: "+path.string());
    }
}
inline void path_assert_is_directory(::std::filesystem::path const& path){
    if(!::std::filesystem::is_directory(path)){
        FGWSZ_THROW_WHAT("path isn't directory: "+path.string());
    }
}
inline void path_assert_is_not_directory(::std::filesystem::path const& path){
    if(::std::filesystem::is_directory(path)){
        FGWSZ_THROW_WHAT("path is directory: "+path.string());
    }
}
inline void path_assert_is_symlink(::std::filesystem::path const& path){
    if(!::std::filesystem::is_symlink(path)){
        FGWSZ_THROW_WHAT("path isn't symlink: "+path.string());
    }
}
inline void path_assert_is_not_symlink(::std::filesystem::path const& path){
    if(::std::filesystem::is_symlink(path)){
        FGWSZ_THROW_WHAT("path is symlink: "+path.string());
    }
}
inline ::std::filesystem::path parent_path(
    ::std::filesystem::path const& path
){
    auto absolute_path=::std::filesystem::absolute(path);
    return absolute_path.parent_path();
}
inline ::std::filesystem::path relative_path(
    ::std::filesystem::path const& path
    ,::std::filesystem::path const& base_path
){
    auto absolute_path=::std::filesystem::absolute(path);
    auto absolute_base_path=::std::filesystem::absolute(base_path);
    return ::std::filesystem::proximate(absolute_path,absolute_base_path);
}
inline bool is_safe_relative_path(
    ::std::filesystem::path const& relative_path
){
    for(auto const& component:relative_path){
        //若包含"..",则存在上级路径攻击的风险
        if(".."==component){
            return false;
        }
    }
    return true;
}
inline void path_assert_is_safe_relative_path(
    ::std::filesystem::path const& relative_path
){
    if(!::fgwsz::is_safe_relative_path(relative_path)){
        FGWSZ_THROW_WHAT("relative path is unsafe: "+relative_path.string());
    }
}
inline void try_create_directories(
    ::std::filesystem::path const& path
){
    if(!::std::filesystem::exists(path)){
        ::std::filesystem::create_directories(path);
    }
}
}//namespace fgwsz

#endif//FGWSZ_PATH_H
