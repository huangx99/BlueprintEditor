#pragma once
#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <rttr/registration>
#include "interface\if_widget_value_editor.h"

class BPAutoValueEditor : public QWidget {
    Q_OBJECT
public:
    
    explicit BPAutoValueEditor(rttr::instance obj, QWidget* parent = nullptr);
    void setObject(rttr::instance obj, QTreeWidgetItem* parent = nullptr);

private:
    QTreeWidget* treeWidget;
    void setInnerClassValue(rttr::instance obj2, rttr::variant json_object, int c, int r);
    if_widget_value_editor* createEditor(const QString& EditorName, QTreeWidgetItem* item);

private:

    //通过这两个可以定位嵌套类的变量在第几层嵌套
    //类的层级
    int m_classLayer = -1;
    //变量的下标
    int m_propIndex = -1;
    //当前类的层级
    int m_currentClassLayer = -1;
    //当前变量的下标
    int m_currentPropIndex = -1;


    rttr::instance m_obj;
};