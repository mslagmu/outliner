#ifndef NEWNODEDIALOG_H
#define NEWNODEDIALOG_H

#include <QDialog>

namespace Ui {
class newNodeDialog;
}

class newNodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newNodeDialog(QWidget *parent = 0);
    int typeOfNode();
    ~newNodeDialog();

private:
    Ui::newNodeDialog *ui;
};

#endif // NEWNODEDIALOG_H
