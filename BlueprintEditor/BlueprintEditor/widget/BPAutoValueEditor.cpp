#include "BPAutoValueEditor.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "factory\BPValueEditorFactory.h"

BPAutoValueEditor::BPAutoValueEditor(rttr::instance obj, QWidget* parent)
    : QWidget(parent), treeWidget(new QTreeWidget(this)), m_obj(obj){
    treeWidget->setColumnCount(2);
    treeWidget->setHeaderLabels({ QString::fromLocal8Bit("属性"), QString::fromLocal8Bit("值")});
    auto layout = new QVBoxLayout(this);
    layout->addWidget(treeWidget);
}

void BPAutoValueEditor::setObject(rttr::instance obj, QTreeWidgetItem* parent) {

    m_classLayer++;
    m_propIndex = -1;
    rttr::type t = obj.get_type();
    for (auto & prop : t.get_properties()) {
        m_propIndex++;
        rttr::variant value = prop.get_value(obj);
        rttr::type valueType = value.get_type();

        // 读取属性是否是用户自定义结构体
        rttr::variant propIsCustomVar = valueType.get_metadata("isCustomType");
        bool isPropCustomType = propIsCustomVar.is_valid() && propIsCustomVar.to_bool();

        if (isPropCustomType)
        {
             QTreeWidgetItem* item;
             if (parent)
             {
                 item = new QTreeWidgetItem(parent);
             }
             else
             {
                 item = new QTreeWidgetItem(treeWidget);
             }
            item->setText(0, QString::fromLocal8Bit(valueType.get_metadata("className").to_string().c_str()));
            int i = 0;
            // 递归处理嵌套结构体
            setObject(prop.get_value(obj), item);
            continue;
        }

        QTreeWidgetItem* item;
        
        if (parent)
        {
            item = new QTreeWidgetItem(parent);
        }
        else
        {
            item = new QTreeWidgetItem(treeWidget);
        }
        
        item->setText(0, QString::fromLocal8Bit(prop.get_metadata("displayName").to_string().c_str()));
        std::string name = prop.get_metadata("editor").to_string();
        if_widget_value_editor* editor = createEditor(QString::fromStdString(name), item);
        int classLayer = m_classLayer;
        //变量的下标
        int propIndex = m_propIndex;
        connect(editor, &if_widget_value_editor::valueChanged, this, [this, classLayer, propIndex, prop, obj, editor]() {
            setInnerClassValue(this->m_obj, editor->getValue(), classLayer, propIndex);
        });
        if (editor) {
            treeWidget->setItemWidget(item, 1, editor);
        }
    }
}

if_widget_value_editor* BPAutoValueEditor::createEditor(const QString& EditorName, QTreeWidgetItem* item) 
{
    return BPValueEditorFactory::instance().createInstance(EditorName);
}

void BPAutoValueEditor::setInnerClassValue(rttr::instance obj2, rttr::variant value, int c, int r)
{
    rttr::instance obj = obj2.get_type().get_raw_type().is_wrapper() ? obj2.get_wrapped_instance() : obj2;
    rttr::type t = obj.get_type();
    m_currentClassLayer++;
    m_currentPropIndex = -1;
    for (auto& prop : t.get_properties())
    {
        const rttr::type value_t = prop.get_type();
        m_currentPropIndex++;

        // 读取属性是否是用户自定义结构体
        rttr::variant propIsCustomVar = value_t.get_metadata("isCustomType");
        bool isPropCustomType = propIsCustomVar.is_valid() && propIsCustomVar.to_bool();

        if (isPropCustomType)
        {

            rttr::variant var = prop.get_value(obj);
            setInnerClassValue(var, value, c, r);
            prop.set_value(obj, var);
            break;
        }
        else
        {
            rttr::variant extracted_value = value;
            if (m_currentClassLayer == c && m_currentPropIndex == r)
            {
                prop.set_value(obj, extracted_value);
                m_currentClassLayer = -1;
                m_currentPropIndex = -1;
            }

        }
    }
}