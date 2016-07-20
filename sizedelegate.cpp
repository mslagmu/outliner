#include "sizedelegate.h"

sizeDelegate::sizeDelegate()
{

}

void sizeDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const {
    int i = index.row();
    option->font.setPointSize(i+7);
    QStyledItemDelegate::initStyleOption(option,index);
}
