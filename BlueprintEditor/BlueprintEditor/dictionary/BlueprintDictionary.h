#pragma once
#include <rttr\registration.h>
//��������
enum VariableSetType
{
    //��һ
    VST_single,
    //����
    VST_array,
    //��
    VST_set,
    //��ֵ��
    VST_map
};

//���ʿ���
enum AccessSpecifierType
{
    AST_private,
    AST_public,
    AST_protected
};
