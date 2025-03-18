#pragma once
#include <map>
#include <memory>
#include <functional>
#include "interface\if_widget_value_editor.h"
class BPValueEditorFactory
{
public:
    using CreateFunc = std::function<if_widget_value_editor*()>;

    static BPValueEditorFactory& instance();

    void registerClass(const QString& name, CreateFunc func);
    
    if_widget_value_editor* createInstance(const QString& name);

private:
    std::map<QString, CreateFunc> factoryMap;
};

// 宏自动注册派生类
#define REGISTER_EDITOR(classname) \
    static void classname##_RegisterFunc() { \
        BPValueEditorFactory::instance().registerClass(#classname, []() { return new classname(); }); \
    } \
    static bool classname##_registered = (classname##_RegisterFunc(), true);
