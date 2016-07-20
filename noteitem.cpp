#include "noteitem.h"
#include <QDebug>



noteItem::noteItem():QTreeWidgetItem(),m_html("")
{
    setText(0,"");
    setFlags(flags() | Qt::ItemIsEditable);
    manageIcon();
}

void noteItem::setHtml(QString h){
    m_html = h;
}

QString noteItem::html(){
    return m_html;
}

void noteItem::setText2(QString t){
    setHtml(QString("<B>html</B>:").arg(t));
}

noteItem * noteItem::parent(){
    return dynamic_cast<noteItem*>(QTreeWidgetItem::parent());
}

void noteItem::manageIcon(){
    /*QIcon folderIcon = QIcon::fromTheme("folder");
    QIcon textIcon = QIcon::fromTheme("text-x-generic");*/
    int nb = childCount();
    if (nb > 0) {
        setIcon(0,QIcon::fromTheme("folder"));
    } else {
        setIcon(0,QIcon::fromTheme("text-x-generic"));
    }

}

QDataStream & operator<<(QDataStream & out, noteItem * n){
    out << n->text(0);
    out << n->html();
    out << n->childCount();

    for(int i=0; i< n->childCount();i++){
        out << (noteItem *) (n->child(i));
    }
    return out;
}

QDataStream & operator>>(QDataStream & in, noteItem * n){
    QString a,b;
    int nb;
    in >> a >> b >> nb;
    n->setText(0,a);
    n->setHtml(b);

    for(int i = 0;i<nb;i++) {
        noteItem * current = new noteItem();
        in >> current;
        n->addChild(current);
    }
    n->manageIcon();
    return in;
}
