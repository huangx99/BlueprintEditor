#pragma once

#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include <QPushButton>
#include "ui_BlueprintEditor.h"
#include "factory/BPValueEditorFactory.h"
#include "BPAutoValueEditor.h"
#include "BPArrayContainer.h"
#include "struct\BlueprintConfig.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BlueprintEditorClass; };
QT_END_NAMESPACE

class BlueprintEditor : public QMainWindow
{
    Q_OBJECT

public:
    BlueprintEditor(QWidget *parent = nullptr);
    ~BlueprintEditor();

private:
    Ui::BlueprintEditorClass *ui;

    QDockWidget* dockWidget;
    BPAutoValueEditor* editor;
    QPushButton* save;
    ClassInfo m_classInfo;
};
