#include "BlueprintEditor.h"
#include <rttr\registration.h>
#include "BPTextEditor.h"
#include "factory\BPValueEditorFactory.h"
using namespace rttr;
#define REGISTRATION RTTR_REGISTRATION

class MyClass {
public:
    MyClass() : x(10), y(20) {}

    int x;
    int y;
    std::string name;
};
REGISTRATION
{
    registration::class_<MyClass>("MyClass")
        .constructor<>()
        .property("x", &MyClass::x)(metadata("disc", "x��"),metadata("edit", "BPIntEditor"))
        .property("y", &MyClass::y)( metadata("disc", "y��"),metadata("edit", "BPIntEditor"))
        .property("name", &MyClass::name)(metadata("disc", "����ϵ����"), metadata("edit", "BPTextEditor"));
}
BlueprintEditor::BlueprintEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BlueprintEditorClass())
    , dockWidget(new QDockWidget("AutoEditor", this)), editor(new BPAutoValueEditor(dockWidget))
{
    ui->setupUi(this);

    MyClass mc;
    editor->setObject(mc);


    dockWidget->setWidget(editor);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);

}

BlueprintEditor::~BlueprintEditor()
{
    delete ui;
}
