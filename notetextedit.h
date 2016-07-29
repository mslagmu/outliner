#ifndef NOTETEXTEDIT_H
#define NOTETEXTEDIT_H
#include<QTextBrowser>

namespace Ui {
class OutLinerViewer;
}

class noteTextEdit : public QTextBrowser
{
    Q_OBJECT
public:
    noteTextEdit(QWidget *parent=0);
    Ui::OutLinerViewer *ui;
    virtual void focusInEvent(QFocusEvent * e);
    void setEnableButton(int enable);

signals:
    void focus();

};

#endif // NOTETEXTEDIT_H
