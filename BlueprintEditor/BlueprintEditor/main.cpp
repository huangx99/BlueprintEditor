#include "widget/BlueprintEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlueprintEditor w;
    w.show();
    return a.exec();
}
