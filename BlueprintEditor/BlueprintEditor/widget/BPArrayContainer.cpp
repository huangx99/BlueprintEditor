#include "BPArrayContainer.h"

BPArrayContainer::BPArrayContainer(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::BPArrayContainerClass())
{
	ui->setupUi(this);
}

BPArrayContainer::~BPArrayContainer()
{
	delete ui;
}

void BPArrayContainer::setEditor(const QString& editor)
{
	m_editorName = editor;
	ui->tableWidget->setEditor(m_editorName);
}
