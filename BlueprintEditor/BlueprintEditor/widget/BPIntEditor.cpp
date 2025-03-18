#include "BPIntEditor.h"

BPIntEditor::BPIntEditor(QWidget *parent)
	: if_widget_value_editor(parent)
	, ui(new Ui::BPIntEditorClass())
{
	ui->setupUi(this);
}

BPIntEditor::~BPIntEditor()
{
	delete ui;
}


rttr::variant BPIntEditor::getValue()
{
	return rttr::variant(ui->spinBox->value());
}

QString BPIntEditor::getName() const
{
	return QString("BPIntEditor");
}
