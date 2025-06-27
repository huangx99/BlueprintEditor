#pragma once

#include <QWidget>
#include "ui_BPArrayContainer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BPArrayContainerClass; };
QT_END_NAMESPACE

class BPArrayContainer : public QWidget
{
	Q_OBJECT

public:
	BPArrayContainer(QWidget *parent = nullptr);
	~BPArrayContainer();

	void setEditor(const QString& editor);

private:
	Ui::BPArrayContainerClass *ui;

	QString m_editorName;
};
