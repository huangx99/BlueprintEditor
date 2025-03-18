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
    for (auto prop : t.get_properties()) {
        QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
        item->setText(0, QString::fromLocal8Bit(prop.get_metadata("disc").to_string().c_str()));
        std::string name = prop.get_metadata("edit").to_string();
        QWidget* editor = createEditor(QString::fromStdString(name), item);
        if (editor) {
            treeWidget->setItemWidget(item, 1, editor);
        }
    }
}

if_widget_value_editor* BPAutoValueEditor::createEditor(const QString& EditorName, QTreeWidgetItem* item) 
{
    return BPValueEditorFactory::instance().createInstance(EditorName);
}