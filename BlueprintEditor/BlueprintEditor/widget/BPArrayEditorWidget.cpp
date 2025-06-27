#include "BPArrayEditorWidget.h"
#include "BPAutoValueEditor.h"
#include <QHBoxLayout>
#include <QLabel>
#include "struct\BlueprintConfig.h"

BPArrayEditorWidget::BPArrayEditorWidget(rttr::instance obj, rttr::property prop, QWidget* parent)
    : QWidget(parent), m_obj(obj), m_prop(prop)
{
    setMinimumHeight(500);
    layout = new QVBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(0, 0, 0, 0);

    m_containerVar = m_prop.get_value(m_obj);
    m_view = m_containerVar.create_sequential_view();

    QPushButton* addBtn = new QPushButton(QString::fromLocal8Bit("添加元素"), this);
    layout->addWidget(addBtn);
    connect(addBtn, &QPushButton::clicked, this, &BPArrayEditorWidget::onAddElement);

    refreshUI();
}

void BPArrayEditorWidget::setEditorContext(BPAutoValueEditor* context) {
    m_editorContext = context;
}

void BPArrayEditorWidget::refreshUI() {
    rebuildUI();
}

rttr::variant_sequential_view BPArrayEditorWidget::getView()
{
    return m_view;
}

void BPArrayEditorWidget::commitBack() {
    return;
    if (m_prop.is_valid() && m_obj.is_valid()) {
        m_prop.set_value(m_obj, m_containerVar);
        m_containerVar = m_prop.get_value(m_obj);
        m_view = m_containerVar.create_sequential_view();
    }
}

void BPArrayEditorWidget::rebuildUI() {
    while (layout->count() > 1) {
        QLayoutItem* item = layout->takeAt(1);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    for (std::size_t i = 0; i < m_view.get_size(); ++i) {
        rttr::variant elem = m_view.get_value(i);

        QWidget* container = new QWidget(this);
        QHBoxLayout* rowLayout = new QHBoxLayout(container);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* label = new QLabel(QString("Item %1").arg(i), container);
        rowLayout->addWidget(label);


        rttr::type ty = elem.get_type().get_wrapped_type();

        if (ty.get_metadata("isCustomType").to_bool()) {
            BPAutoValueEditor* subEditor = new BPAutoValueEditor(elem, this);
            subEditor->setObject(elem);
            rowLayout->addWidget(subEditor);

            connect(subEditor, &BPAutoValueEditor::dataChanged, this,
                [this, i, &elem, subEditor]() {
                
                m_view.set_value(i, elem);
            });

        }
        else {
            QLabel* placeholder = new QLabel("<基础类型待实现>", this);
            rowLayout->addWidget(placeholder);
        }

        QPushButton* delBtn = new QPushButton("删除", this);
        rowLayout->addWidget(delBtn);
        connect(delBtn, &QPushButton::clicked, this, [this, i]() {
            onRemoveElement(static_cast<int>(i));
        });

        container->setLayout(rowLayout);
        layout->addWidget(container);
    }

    adjustSize();
}

void BPArrayEditorWidget::onAddElement() {
    m_view.set_size(m_view.get_size() + 1);
    m_view.set_value(m_view.get_size(), rttr::variant());
    rebuildUI();

    emit dataChanged();
}

void BPArrayEditorWidget::onRemoveElement(int index) {
    if (index >= 0 && static_cast<std::size_t>(index) < m_view.get_size()) {
        auto it = m_view.begin() + index;
        m_view.erase(it);
        rebuildUI();

        emit dataChanged();
    }
}