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


// ������Ϣ����Ա������
struct VariableInfo
{
    AccessSpecifierType accessSpecifier = AccessSpecifierType::AST_private;   // ��Ա�����ķ��ʿ��ƣ�public, private, protected��
    std::string type;              // �������� (�� int, double)
    std::string name;              // ��������
    bool isPointer = false;                // �Ƿ���ָ��
    std::string defaultValue;      // Ĭ��ֵ����ѡ��
    VariableSetType setType = VST_single; //��ֵ����
   TestClass ttt;
};


// ������Ϣ����Ա������
struct FunctionInfo
{
    std::string accessSpecifier;       // �����ķ��ʿ��ƣ�public, private, protected��
    std::string storageClass;          // �洢���ͣ�static, extern, inline��
    std::string returnType;            // ��������
    std::string name;                  // ������
    std::vector<VariableInfo> intputParameters; // �����б�
    std::vector<VariableInfo> outputParameters; // ����б�
    std::vector<std::string> qualifiers; // ���η���virtual, override, final, explicit��
    std::string scope;                 // ������global, class��Ա��
    bool isMemberFunction = false;             // �Ƿ��ǳ�Ա����
    bool isVirtual = false;                    // �Ƿ����麯��
    bool isPureVirtual = false;                // �Ƿ��Ǵ��麯��
    bool isConst = false;                      // �Ƿ��� const ��Ա����
    bool isNoexcept = false;                   // �Ƿ��� noexcept
    bool isDefaulted = false;                  // �Ƿ��� `= default`
    bool isDeleted = false;                    // �Ƿ��� `= delete`
    bool isTemplate = false;                   // �Ƿ���ģ�庯��
    std::string templateParams;        // ģ����� (�� `<typename T>`)
    std::string functionBody;          // ������ (Ϊ�ձ�ʾ����)

};

// ����Ϣ
struct ClassInfo
{
    std::string className;                        // ����
    std::vector<VariableInfo> memberVariables;    // ��Ա����
    std::vector<FunctionInfo> memberFunctions;    // ��Ա����
    std::vector<std::pair<std::string, std::string>> baseClasses; // ���༰�̳з�ʽ���� public, private, protected��
    std::string importantInterface;               //��Ҫ�ӿ�
    bool isAbstract = false;                              // �Ƿ��ǳ�����
    bool isFinal = false;                                 // �Ƿ��������ࣨ�޷��̳У�
    bool isTemplate = false;                              // �Ƿ���ģ����
    std::string templateParams;                   // ģ����� (�� `<typename T>`)
};

struct ClassInfos
{
    std::list<ClassInfo> classInfos;
};
