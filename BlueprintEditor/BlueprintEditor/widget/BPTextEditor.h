#pragma once

#include <QWidget>
#include "ui_BPTextEditor.h"
#include <interface/if_widget_value_editor.h>
#include "factory\BPValueEditorFactory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BPTextEditorClass; };
QT_END_NAMESPACE

class BPTextEditor : public if_widget_value_editor
{
	Q_OBJECT

public:
	BPTextEditor(QWidget *parent = nullptr);
	virtual ~BPTextEditor();

	virtual QString getName() const override;

	virtual rttr::variant getValue() override;
private:
	Ui::BPTextEditorClass *ui;
};
REGISTER_EDITOR(BPTextEditor);