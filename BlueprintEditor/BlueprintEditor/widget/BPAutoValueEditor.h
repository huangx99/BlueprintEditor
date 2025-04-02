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

    //ͨ�����������Զ�λǶ����ı����ڵڼ���Ƕ��
    //��Ĳ㼶
    int m_classLayer = -1;
    //�������±�
    int m_propIndex = -1;
    //��ǰ��Ĳ㼶
    int m_currentClassLayer = -1;
    //��ǰ�������±�
    int m_currentPropIndex = -1;


    rttr::instance m_obj;
};