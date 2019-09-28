#include "library/tableitemdelegate.h"

#include <QTableView>
#include <QPainter>

#include "util/painterscope.h"


TableItemDelegate::TableItemDelegate(QTableView* pTableView)
        : QStyledItemDelegate(pTableView),
          m_pTableView(pTableView) {
}

void TableItemDelegate::paint(
        QPainter* painter,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const {
    PainterScope painterScope(painter);

    painter->setClipRect(option.rect);

    // Set the palette appropriately based on whether the row is selected or
    // not. We also have to check if it is inactive or not and use the
    // appropriate ColorGroup.
    QPalette::ColorGroup cg = option.state & QStyle::State_Enabled
            ? QPalette::Normal : QPalette::Disabled;
    if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
        cg = QPalette::Inactive;

    if (option.state & QStyle::State_Selected) {
        painter->setBrush(option.palette.color(cg, QPalette::HighlightedText));
    } else {
        painter->setBrush(option.palette.color(cg, QPalette::Text));
    }

    if (m_pTableView) {
        QStyle* style = m_pTableView->style();
        if (style) {
            style->drawControl(QStyle::CE_ItemViewItem, &option, painter,
                    m_pTableView);
        }
    }

    paintItem(painter, option, index);
}

int TableItemDelegate::columnWidth(const QModelIndex &index) const {
    return m_pTableView->columnWidth(index.column());
}
