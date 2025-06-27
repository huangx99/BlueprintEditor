#include "BlueprintConfig.h"
#include "rttr/registration.h"
// RTTR 注册
RTTR_REGISTRATION
{
     rttr::registration::class_<VariableInfo>("VariableInfo")
        .constructor<>()
        .property("accessSpecifier", &VariableInfo::accessSpecifier)(rttr::metadata("displayName","访问权限"), rttr::metadata("editor","BPEnumEditor"), rttr::metadata("enumList", std::map<int, std::string>{{1, "公开"},{0, "私有"},{2, "受保护"}}))
        .property("type", &VariableInfo::type)(rttr::metadata("displayName","数据类型"), rttr::metadata("editor","BPValueTypeEditor"))
        .property("name", &VariableInfo::name)(rttr::metadata("displayName","变量名称"), rttr::metadata("editor","BPTextEditor"), rttr::metadata("isArray",true))
        .property("isPointer", &VariableInfo::isPointer)(rttr::metadata("displayName","是否为指针"), rttr::metadata("editor","BPCheckEditor"))
        .property("defaultValue", &VariableInfo::defaultValue)(rttr::metadata("displayName","默认值"), rttr::metadata("editor","BPTextEditor"))
        .property("setType", &VariableInfo::setType)(rttr::metadata("displayName","数值类型"), rttr::metadata("editor","BPEnumEditor"), rttr::metadata("enumList", std::map<int, std::string>{{0, "单一"},{1, "数组"},{2, "集"}, {3, "映射"}}))
         .property("ttt", &VariableInfo::ttt);


rttr::registration::class_<TestClass>("TestClass")(rttr::metadata("isCustomType", true), rttr::metadata("className", "测试类"))
.constructor<>()(rttr::policy::ctor::as_object)
.property("a", &TestClass::a)(rttr::metadata("displayName", "测试a"), rttr::metadata("editor", "BPValueTypeEditor"))
.property("b", &TestClass::b)(rttr::metadata("displayName", "测试b"), rttr::metadata("editor", "BPValueTypeEditor"))
.property("c", &TestClass::c)(rttr::metadata("displayName", "测试c"), rttr::metadata("editor", "BPTextEditor"))
.property("class2", &TestClass::class2);

rttr::registration::class_<TestClass2>("TestClass2")(rttr::metadata("isCustomType", true), rttr::metadata("className", "测试类2"))
.constructor<>()(rttr::policy::ctor::as_object)
.property("a", &TestClass2::a)(rttr::metadata("displayName", "测试a"), rttr::metadata("editor", "BPValueTypeEditor"))
.property("b", &TestClass2::b)(rttr::metadata("displayName", "测试b"), rttr::metadata("editor", "BPValueTypeEditor"))
.property("c", &TestClass2::c)(rttr::metadata("displayName", "测试c"), rttr::metadata("editor", "BPTextEditor"))
;


    rttr::registration::class_<FunctionInfo>("FunctionInfo")
        .constructor<>()
        .property("accessSpecifier", &FunctionInfo::accessSpecifier)(rttr::metadata("", ""))
        //.property("storageClass", &FunctionInfo::storageClass)
        //.property("returnType", &FunctionInfo::returnType)
        .property("name", &FunctionInfo::name)
        .property("intputParameters", &FunctionInfo::intputParameters)
        .property("outputParameters", &FunctionInfo::outputParameters)
        .property("qualifiers", &FunctionInfo::qualifiers)
        .property("scope", &FunctionInfo::scope)
        .property("isMemberFunction", &FunctionInfo::isMemberFunction)
        .property("isVirtual", &FunctionInfo::isVirtual)
        .property("isPureVirtual", &FunctionInfo::isPureVirtual)
        .property("isConst", &FunctionInfo::isConst)
        .property("isNoexcept", &FunctionInfo::isNoexcept)
        .property("isDefaulted", &FunctionInfo::isDefaulted)
        .property("isDeleted", &FunctionInfo::isDeleted)
        .property("isTemplate", &FunctionInfo::isTemplate)
        .property("templateParams", &FunctionInfo::templateParams)
        .property("functionBody", &FunctionInfo::functionBody);

    rttr::registration::class_<ClassInfo>("ClassInfo")
        .constructor<>()
        .property("className", &ClassInfo::className)
        .property("memberVariables", &ClassInfo::memberVariables)
        .property("memberFunctions", &ClassInfo::memberFunctions)
        .property("baseClasses", &ClassInfo::baseClasses)
        .property("importantInterface", &ClassInfo::importantInterface)
        .property("isAbstract", &ClassInfo::isAbstract)
        .property("isFinal", &ClassInfo::isFinal)
        .property("isTemplate", &ClassInfo::isTemplate)
        .property("templateParams", &ClassInfo::templateParams);
}
