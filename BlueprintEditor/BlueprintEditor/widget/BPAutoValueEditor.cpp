#include "BPAutoValueEditor.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "factory\BPValueEditorFactory.h"
#include "BPArrayEditorWidget.h"
#include "struct\BlueprintConfig.h"

BPAutoValueEditor::BPAutoValueEditor(rttr::instance obj, QWidget* parent)
    : QWidget(parent), treeWidget(new QTreeWidget(this)), m_obj(obj){
    treeWidget->setColumnCount(2);
    treeWidget->setHeaderLabels({ QString::fromLocal8Bit("属性"), QString::fromLocal8Bit("值")});
    auto layout = new QVBoxLayout(this);
    layout->addWidget(treeWidget);

    setMinimumHeight(180); // 可以根据内容动态调整
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

void BPAutoValueEditor::setObject(rttr::instance obj, QTreeWidgetItem* parent)
{
    m_classLayer++;
    m_propIndex = -1;

    rttr::type t = obj.get_type();

    auto ty = t.get_wrapped_type();

    if (t.get_raw_type().get_wrapped_type().is_valid())
    {
        t = t.get_raw_type().get_wrapped_type();
    }

    for (auto& prop : t.get_properties()) {
        m_propIndex++;

        rttr::variant value = prop.get_value(obj);
        rttr::type valueType = value.get_type();

        int classLayer = m_classLayer;
        int propIndex = m_propIndex;

        QTreeWidgetItem* item = (parent) ? new QTreeWidgetItem(parent) : new QTreeWidgetItem(treeWidget);

        //不再处理数组，数组需要自定义构造器
        //if (value.is_sequential_container()) {

        //    item->setText(0, QString::fromStdString(prop.get_name().to_string()) + "[Array]");

        //    auto* arrayWidget = new BPArrayEditorWidget(obj, prop);

        //    arrayWidget->setEditorContext(this);  // 可选
        //    treeWidget->setItemWidget(item, 1, arrayWidget);
        //    connect(arrayWidget, &BPArrayEditorWidget::dataChanged, this,
        //        [this, arrayWidget, prop, obj, classLayer, propIndex]() {
        //        rttr::variant value = prop.get_value(obj);

        //        auto view = arrayWidget->getView();

        //        auto view2 = value.create_sequential_view();
        //        view2.set_size(view.get_size());
        //        for (int i = 0; i < view.get_size(); i++)
        //        {
        //            //view.get_value(i).get_type().create() 获取包装的类型，如果不这么做，会导致数组越界乱给
        //            view2.set_value(i, view.get_value(i));
        //        }
        //        int i = view2.get_size();
        //        setInnerClassValue(this->m_obj, value, classLayer, propIndex);
        //    });

        //    continue;
        //}

        // 是否为自定义结构体
        bool isCustomType = valueType.get_metadata("isCustomType").is_valid()
            && valueType.get_metadata("isCustomType").to_bool();

        if (isCustomType) {
            std::string name = valueType.get_metadata("className").to_string();
            item->setText(0, QString::fromLocal8Bit(valueType.get_metadata("className").to_string().c_str()));
            setObject(prop.get_value(obj), item);  // 递归
            continue;
        }

        // 普通类型属性
        item->setText(0, QString::fromLocal8Bit(prop.get_metadata("displayName").to_string().c_str()));
        std::string editorName = prop.get_metadata("editor").to_string();

        if_widget_value_editor* editor = createEditor(QString::fromStdString(editorName), item);
        

        if (editor) {
           // editor->setValue(value);
            connect(editor, &if_widget_value_editor::valueChanged, this,
                [this, classLayer, propIndex, prop, obj, editor]() {
                setInnerClassValue(this->m_obj, editor->getValue(), classLayer, propIndex);
            });

            treeWidget->setItemWidget(item, 1, editor);
        }
    }

    m_classLayer--;
}

if_widget_value_editor* BPAutoValueEditor::createEditor(const QString& EditorName, QTreeWidgetItem* item) 
{
    return BPValueEditorFactory::instance().createInstance(EditorName);
}

rttr::instance& BPAutoValueEditor::getObj()
{
    return m_obj;
}

void BPAutoValueEditor::setInnerClassValue(rttr::instance obj2, rttr::variant value, int c, int r)
{
    rttr::instance obj = obj2.get_type().get_raw_type().is_wrapper() ? obj2.get_wrapped_instance() : obj2;
    rttr::type t = obj.get_type();
    //当前类的层级
    m_currentClassLayer++;
    //当前变量在类中的下标
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
            }

        }
    }

    m_currentClassLayer = -1;
    m_currentPropIndex = -1;

    emit dataChanged();
}