#include "ContainerTable.h"
#include <QMenu>
#include <QContextMenuEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QHeaderView>

#include "factory\BPValueEditorFactory.h"

ContainerTable::ContainerTable(QWidget* parent)
    : QTableWidget(parent)
{
    setColumnCount(1);
    setHorizontalHeaderLabels(QStringList()
        << QString::fromLocal8Bit("值"));

    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void ContainerTable::setEditor(const QString& editor)
{
    m_editorName = editor;
}

void ContainerTable::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
    QAction* addAction = menu.addAction(QString::fromLocal8Bit("添加行"));
    QAction* delAction = menu.addAction(QString::fromLocal8Bit("删除选中行"));

    QAction* selectedAction = menu.exec(event->globalPos());
    if (selectedAction == addAction)
    {
        addRow();
    }
    else if (selectedAction == delAction)
    {
        deleteRow();
    }
}

void ContainerTable::addRow()
{
    int row = rowCount();
    insertRow(row);
    
    setItem(row, 0, new QTableWidgetItem());
   
}

void ContainerTable::deleteRow()
{
    auto selected = selectedItems();
    if (!selected.isEmpty())
    {
        int row = selected.first()->row();
        removeRow(row);
    }
}
//拖拽开始时，记录行号
void ContainerTable::startDrag(Qt::DropActions supportedActions)
{
    auto selected = selectedItems();
    if (!selected.isEmpty())
    {
        m_dragRow = selected.first()->row();

      /*  QMimeData* mimeData = new QMimeData;
        QDrag* drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->exec(Qt::MoveAction);*/
    }

    QTableWidget::startDrag(supportedActions);
}

// 拖拽释放时，获取释放行，做行移动
void ContainerTable::dropEvent(QDropEvent* event)
{
    int dropRow = indexAt(event->pos()).row();
    if (dropRow == -1) dropRow = rowCount();

    if (m_dragRow != -1 && m_dragRow != dropRow)
    {
        moveRow(m_dragRow, dropRow);
    }

    m_dragRow = -1;
    event->acceptProposedAction();
}

// 行数据移动逻辑
void ContainerTable::moveRow(int from, int to)
{
    if (from == to || from < 0 || to < 0 || from >= rowCount() || to >= rowCount())
        return;

    // 保存源行内容
    QList<QTableWidgetItem*> items;
    for (int col = 0; col < columnCount(); ++col)
        items << takeItem(from, col);

    removeRow(from);

    if (to > from) to--; // 如果向下插入，要补偿移除后的行数变化

    insertRow(to);
    for (int col = 0; col < columnCount(); ++col)
    {
        QTableWidgetItem* item = items[col];
        if (item)
            setItem(to, col, item);
    }

    setCurrentCell(to, 0);
}
