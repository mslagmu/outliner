#ifndef SIZEDELEGATE_H
#define SIZEDELEGATE_H
#include<QStyledItemDelegate>

class sizeDelegate : public QStyledItemDelegate
{
public:
    sizeDelegate();
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const;
};

#endif // SIZEDELEGATE_H
