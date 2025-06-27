#pragma once
#include <string>
#include <vector>
#include <list>
#include "dictionary\BlueprintDictionary.h"
using String = std::string;

struct TestClass2
{
    int a;
    int b;
    std::vector<String> c;
};

struct TestClass
{
    int a;
    int b;
    String c;
    TestClass2 class2;
};


// 变量信息（成员变量）
struct VariableInfo
{
    AccessSpecifierType accessSpecifier = AccessSpecifierType::AST_private;   // 成员变量的访问控制（public, private, protected）
    std::string type;              // 数据类型 (如 int, double)
    std::string name;              // 变量名称
    bool isPointer = false;                // 是否是指针
    std::string defaultValue;      // 默认值（可选）
    VariableSetType setType = VST_single; //数值类型
   TestClass ttt;
};


// 函数信息（成员函数）
struct FunctionInfo
{
    std::string accessSpecifier;       // 函数的访问控制（public, private, protected）
    std::string storageClass;          // 存储类型（static, extern, inline）
    std::string returnType;            // 返回类型
    std::string name;                  // 函数名
    std::vector<VariableInfo> intputParameters; // 输入列表
    std::vector<VariableInfo> outputParameters; // 输出列表
    std::vector<std::string> qualifiers; // 修饰符（virtual, override, final, explicit）
    std::string scope;                 // 作用域（global, class成员）
    bool isMemberFunction = false;             // 是否是成员函数
    bool isVirtual = false;                    // 是否是虚函数
    bool isPureVirtual = false;                // 是否是纯虚函数
    bool isConst = false;                      // 是否是 const 成员函数
    bool isNoexcept = false;                   // 是否是 noexcept
    bool isDefaulted = false;                  // 是否是 `= default`
    bool isDeleted = false;                    // 是否是 `= delete`
    bool isTemplate = false;                   // 是否是模板函数
    std::string templateParams;        // 模板参数 (如 `<typename T>`)
    std::string functionBody;          // 函数体 (为空表示声明)

};

// 类信息
struct ClassInfo
{
    std::string className;                        // 类名
    std::vector<VariableInfo> memberVariables;    // 成员变量
    std::vector<FunctionInfo> memberFunctions;    // 成员函数
    std::vector<std::pair<std::string, std::string>> baseClasses; // 基类及继承方式（如 public, private, protected）
    std::string importantInterface;               //主要接口
    bool isAbstract = false;                              // 是否是抽象类
    bool isFinal = false;                                 // 是否是最终类（无法继承）
    bool isTemplate = false;                              // 是否是模板类
    std::string templateParams;                   // 模板参数 (如 `<typename T>`)
};

struct ClassInfos
{
    std::list<ClassInfo> classInfos;
};
