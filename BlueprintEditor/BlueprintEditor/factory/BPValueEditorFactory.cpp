#include "BPValueEditorFactory.h"

BPValueEditorFactory& BPValueEditorFactory::instance()
{
    static BPValueEditorFactory factory;
    return factory;
}

void BPValueEditorFactory::registerClass(const QString& name, CreateFunc func)
{
    factoryMap[name] = std::move(func);
}

if_widget_value_editor* BPValueEditorFactory::createInstance(const QString& name)
{
    auto it = factoryMap.find(name);
    if (it != factoryMap.end())
    {
        return it->second();  // 调用存储的 `new` 函数
    }
    return nullptr;
}
