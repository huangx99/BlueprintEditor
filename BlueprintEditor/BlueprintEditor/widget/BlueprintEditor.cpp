#include "BlueprintEditor.h"
#include "BPTextEditor.h"
#include "factory\BPValueEditorFactory.h"

BlueprintEditor::BlueprintEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BlueprintEditorClass())
    , dockWidget(new QDockWidget("AutoEditor", this)), editor(new BPAutoValueEditor(dockWidget))
{
    ui->setupUi(this);

    VariableInfo info;
    m_classInfo.memberVariables.push_back(info);
    
    auto dockWidget1 = new QDockWidget("AutoEditor", this);
    save = new QPushButton("save", dockWidget1);
    dockWidget1->setWidget(save);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget1);
    connect(save, &QPushButton::clicked, this, [this](bool clicked) {
        VariableInfo info1 = m_classInfo.memberVariables[0];
        int i = 0;
    });
    
    editor->setObject(m_classInfo.memberVariables[0]);


    dockWidget->setWidget(editor);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);

}

BlueprintEditor::~BlueprintEditor()
{
    delete ui;
}
