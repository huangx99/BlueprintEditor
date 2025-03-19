#include "BPAutoValueEditor.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "factory\BPValueEditorFactory.h"

BPAutoValueEditor::BPAutoValueEditor(QWidget* parent)
    : QWidget(parent), treeWidget(new QTreeWidget(this)) {
    treeWidget->setColumnCount(2);
    treeWidget->setHeaderLabels({ QString::fromLocal8Bit("ÊôÐÔ"), QString::fromLocal8Bit("Öµ")});
    auto layout = new QVBoxLayout(this);
    layout->addWidget(treeWidget);
}

void BPAutoValueEditor::setObject(rttr::instance obj) {
    treeWidget->clear();
    rttr::type t = obj.get_type();
    for (auto & prop : t.get_properties()) {
        QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
        item->setText(0, QString::fromLocal8Bit(prop.get_metadata("displayName").to_string().c_str()));
        std::string name = prop.get_metadata("editor").to_string();
        if_widget_value_editor* editor = createEditor(QString::fromStdString(name), item);
        connect(editor, &if_widget_value_editor::valueChanged, this, [prop, obj, editor]() {
            prop.set_value(obj, editor->getValue());
            std::string str = prop.get_value(obj).to_string();
            int i = 0;
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