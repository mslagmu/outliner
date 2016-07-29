#include "newnodedialog.h"
#include "ui_newnodedialog.h"

newNodeDialog::newNodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newNodeDialog)
{
    ui->setupUi(this);
}


int newNodeDialog::typeOfNode(){
   if (ui->childButton->isChecked()) return 0;
   if (ui->brotherButton->isChecked()) return 1;
   if (ui->rootButton->isChecked()) return 2;
}

newNodeDialog::~newNodeDialog()
{
    delete ui;
}
