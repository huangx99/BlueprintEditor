#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <rttr/registration>

class BPAutoValueEditor;

class BPArrayEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BPArrayEditorWidget(rttr::instance obj, rttr::property prop, QWidget* parent = nullptr);
    void setEditorContext(BPAutoValueEditor* context); // 主编辑器上下文，可选

    void refreshUI();

    rttr::variant_sequential_view getView();

private slots:
    void onAddElement();
    void onRemoveElement(int index);

signals:
    void dataChanged();

private:
    QVBoxLayout* layout;
    rttr::instance m_obj;
    rttr::property m_prop;
    rttr::variant m_containerVar;
    rttr::variant_sequential_view m_view;
    BPAutoValueEditor* m_editorContext = nullptr;

    void rebuildUI();
    void commitBack();
};