#pragma once

#include <QTableWidget>
#include <QPoint>
#include "interface\if_widget_value_editor.h"

class if_widget_value_editor;

class ContainerTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit ContainerTable(QWidget* parent = nullptr);


    void setEditor(const QString& editor);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void startDrag(Qt::DropActions supportedActions) override;

private slots:
    void addRow();
    void deleteRow();

private:
    void moveRow(int from, int to);

private:
    int m_dragRow = -1; // 记录拖动起始行
    
    QString m_editorName;

    std::vector<if_widget_value_editor*> m_editors;

};
