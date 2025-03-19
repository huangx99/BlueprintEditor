#pragma once
#include <rttr\registration.h>
//变量类型
enum VariableSetType
{
    //单一
    VST_single,
    //数组
    VST_array,
    //集
    VST_set,
    //键值对
    VST_map
};

//访问控制
enum AccessSpecifierType
{
    AST_private,
    AST_public,
    AST_protected
};
