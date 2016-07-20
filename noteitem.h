#ifndef NOTEITEM_H
#define NOTEITEM_H
#include<QTreeWidgetItem>
#include<QDataStream>

class noteItem : public QTreeWidgetItem
{
public:
    noteItem();
    void setHtml(QString h);
    QString html();
    void setText2(QString t);
    void manageIcon();
    noteItem * parent();

private :
    QString m_html;
};

QDataStream & operator<<(QDataStream & out, noteItem * n);
QDataStream & operator>>(QDataStream & out, noteItem * n);

#endif // NOTEITEM_H
