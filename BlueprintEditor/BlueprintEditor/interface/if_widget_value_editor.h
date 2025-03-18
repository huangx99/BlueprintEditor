#pragma once
#include <QWidget>
#include <rttr\variant.h>
class if_widget_value_editor : public QWidget
{
	Q_OBJECT
public:
	explicit if_widget_value_editor(QWidget* parent = nullptr) :QWidget(parent) {}
	virtual~ if_widget_value_editor() {}
	virtual QString getName() const = 0;
	virtual rttr::variant getValue() = 0;
signals:
	void valueChanged();
};