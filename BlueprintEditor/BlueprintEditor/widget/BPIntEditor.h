#pragma once

#include <QWidget>
#include "ui_BPIntEditor.h"
#include <interface/if_widget_value_editor.h>

#include "factory\BPValueEditorFactory.h"
QT_BEGIN_NAMESPACE
namespace Ui { class BPIntEditorClass; };
QT_END_NAMESPACE

class BPIntEditor : public if_widget_value_editor
{
	Q_OBJECT

public:
	BPIntEditor(QWidget* parent = nullptr);
	virtual ~BPIntEditor();

	virtual QString getName() const override;

	virtual rttr::variant getValue() override;
private:
	Ui::BPIntEditorClass* ui;
};

REGISTER_EDITOR(BPIntEditor);
