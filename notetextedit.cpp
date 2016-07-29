#include "notetextedit.h"
#include "ui_outlinerviewer.h"

noteTextEdit::noteTextEdit(QWidget *parent):QTextBrowser(parent){
    setOpenLinks(false);
}

void noteTextEdit::focusInEvent(QFocusEvent * e){
     emit focus();
}

void noteTextEdit::setEnableButton(int enable) {
    ui->action_Copy->setEnabled(enable);
    ui->action_Paste->setEnabled(enable);
    ui->actionCu_t->setEnabled(enable);
    ui->action_Bold->setEnabled(enable);
    ui->action_Italic->setEnabled(enable);
    ui->action_Underline->setEnabled(enable);
    ui->actionInsertLink->setEnabled(enable);
    ui->actionIndent->setEnabled(enable);
    ui->actionUnindent->setEnabled(enable);
    ui->fontBox->setEnabled(enable);
    ui->sizeBox->setEnabled(enable);
    ui->actionDelete_Table->setEnabled(enable);
    ui->actionInsert_Column->setEnabled(enable);
    ui->actionInsert_Row->setEnabled(enable);
    ui->actionDelete_Column->setEnabled(enable);
    ui->actionDelete_Row->setEnabled(enable);
    ui->actionInsert_Table->setEnabled(enable);
    ui->actionRight->setEnabled(enable);
    ui->actionLeft->setEnabled(enable);
    ui->actionCenter->setEnabled(enable);
    ui->actionFill->setEnabled(enable);
    ui->styleToolBar->setVisible(enable);
    ui->styleToolBar->setVisible(enable);
    ui->tableToolBar->setVisible(enable);
}
