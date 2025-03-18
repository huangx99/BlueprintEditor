#include "BPTextEditor.h"

BPTextEditor::BPTextEditor(QWidget *parent)
	: if_widget_value_editor(parent)
	, ui(new Ui::BPTextEditorClass())
{
	ui->setupUi(this);
}

BPTextEditor::~BPTextEditor()
{
	delete ui;
}

rttr::variant BPTextEditor::getValue()
{
	return rttr::variant(ui->lineEdit->text().toStdString());
}

QString BPTextEditor::getName() const
{
	return QString("BPTextEditor");
}
