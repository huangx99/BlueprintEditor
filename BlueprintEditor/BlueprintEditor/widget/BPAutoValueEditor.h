#pragma once
#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <rttr/registration>
#include "interface\if_widget_value_editor.h"

class BPAutoValueEditor : public QWidget {
    Q_OBJECT
public:
    explicit BPAutoValueEditor(QWidget* parent = nullptr);
    void setObject(rttr::instance obj);

private:
    QTreeWidget* treeWidget;
    if_widget_value_editor* createEditor(const QString& EditorName, QTreeWidgetItem* item);
};