#include "outlinerviewer.h"

#include "ui_outlinerviewer.h"
#include "sizedelegate.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QTextTableCell>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include "colorbox.h"
#include "AESStringCrypt.h"

#define MAGIC 2345432



QByteArray encrypt(QString pwd,QByteArray & qb){
    QByteArray  ciphertext;
    ciphertext.resize(qb.size()+100);
    unsigned long long ciphertext_length = AESStringCrypt( (unsigned char*) pwd.toLatin1().data(),
                                                           (unsigned long)pwd.length(),
                                                           (unsigned char*) qb.data(),
                                                           (unsigned long long) qb.size(),
                                                           (unsigned char*) ciphertext.data());

    return QByteArray ((const char *)ciphertext,ciphertext_length);
}

QByteArray decrypt(QString pwd,QByteArray & qb){
    QByteArray  cleartext;
    cleartext.resize(qb.size());
    unsigned long long cleartext_length = AESStringDecrypt( (unsigned char*) pwd.toLatin1().data(),
                                                            (unsigned long)pwd.length(),
                                                            (unsigned char*) qb.data(),
                                                            (unsigned long long) qb.size(),
                                                            (unsigned char*) cleartext.data());

    return QByteArray ((const char *)cleartext,cleartext_length);
}



OutLinerViewer::OutLinerViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::OutLinerViewer),config("outliner"),cryptLabel(this) {
    ui->setupUi(this);
    ui->textEdit->ui=ui;
    ui->TOC->ui=ui;

    ui->sizeBox->setItemDelegate(new sizeDelegate());
    ui->textEdit->setFontPointSize(9);

    for(int i=7;i<40;i++){
        ui->sizeBox->addItem(QString("%1").arg(i),i);
    }


    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &OutLinerViewer::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(ui->actionLeft);
        alignGroup->addAction(ui->actionCenter);
        alignGroup->addAction(ui->actionRight);
    } else {
        alignGroup->addAction(ui->actionRight);
        alignGroup->addAction(ui->actionCenter);
        alignGroup->addAction(ui->actionLeft);
    }
    alignGroup->addAction(ui->actionFill);


    filename=config.value("filename","toto.txt").toString();
    setGeometry(config.value("geometry",QRect(341,123,974,628)).toRect());
    ui->splitter->restoreState(config.value("splitterSizes").toByteArray());

    ui->fontBox->setParent(ui->styleToolBar);
    ui->styleToolBar->addWidget(ui->fontBox);
    ui->sizeBox->setParent(ui->styleToolBar);
    ui->styleToolBar->addWidget(ui->sizeBox);
    ui->colorbox->setParent(ui->styleToolBar);
    ui->styleToolBar->addWidget(ui->colorbox);

    ui->statusbar->insertPermanentWidget(0,&cryptLabel,50);

    setPassword("");

    openFile();
}

OutLinerViewer::~OutLinerViewer() { delete ui; }

void OutLinerViewer::on_actionAddItem_triggered() {
    noteItem *current = ui->TOC->currentItem();
    if (current == 0) {
        addChild(current);
    } else {
        addChild(current->parent());
    }
}

void OutLinerViewer::on_actionRemoveItem_triggered() {
    noteItem *current = ui->TOC->currentItem();
    if (current == 0)
        return;
    if (current->parent() == 0) {
        ui->TOC->invisibleRootItem()->removeChild(current);
    } else {
        noteItem* parent = dynamic_cast<noteItem*>(current->parent());
        parent->removeChild(current);
        parent->manageIcon();
    }
}


void OutLinerViewer::textAlign(QAction *a)
{
    if (a == ui->actionLeft)
        ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == ui->actionCenter)
        ui->textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == ui->actionRight)
        ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == ui->actionFill)
        ui->textEdit->setAlignment(Qt::AlignJustify);
}

void OutLinerViewer::addChild(noteItem* current, QString text) {
    noteItem *n = new noteItem();
    n->setText(0,text);
    if (current == 0) {
        ui->TOC->invisibleRootItem()->addChild(n);
    } else {
        current->addChild(n);
        current->manageIcon();
    }
    ui->TOC->setCurrentItem(n);
    ui->TOC->editItem(n);
}

void OutLinerViewer::on_actionAddChild_triggered() {
    noteItem *current = ui->TOC->currentItem();
    addChild(current);
}

void OutLinerViewer::on_actionInsertLink_triggered() {
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    if ( !(cursor.hasSelection())) {
       ui->actionInsertLink->setChecked(false);
       return;
    }

    fmt.setAnchor(ui->actionInsertLink->isChecked());

    if ( ui->actionInsertLink->isChecked() ){
        QString t = ui->textEdit->textCursor().selectedText();
        fmt.setAnchorHref(t);
    } else {
        fmt.setFontUnderline(false);
    }
    cursor.setCharFormat(fmt);
    ui->textEdit->setHtml(ui->textEdit->toHtml());
}


void OutLinerViewer::on_actionIndent_triggered() {
    qDebug() << "on_actionIndent_triggered";
}
void OutLinerViewer::on_actionUnindent_triggered() {
    qDebug() << "on_actionUnindent_triggered";
}
void OutLinerViewer::on_actionInsert_Table_triggered() {
    if ( cm==true) return;
    ui->textEdit->textCursor().insertTable(2,2);
}
void OutLinerViewer::on_actionInsert_Row_triggered() {
    if ( cm==true) return;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable * t = cursor.currentTable();
    if (t != 0) {
        QTextTableCell c = t->cellAt(cursor);
        int row = c.row();
        t->insertRows(row+1,1);
    }
}
void OutLinerViewer::on_actionDelete_Table_triggered() {
    qDebug() << "on_actionDelete_Table_triggered";
}
void OutLinerViewer::on_actionDelete_Row_triggered() {
    if ( cm==true) return;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable * t = cursor.currentTable();
    if (t != 0) {
        QTextTableCell c = t->cellAt(cursor);
        int row = c.row();
        t->removeRows(row,1);
    }
}
void OutLinerViewer::on_actionDelete_Column_triggered() {
    if ( cm==true) return;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable * t = cursor.currentTable();
    if (t != 0) {
        QTextTableCell c = t->cellAt(cursor);
        int column = c.column();
        t->removeColumns(column,1);
    }
}
void OutLinerViewer::on_actionInsert_Column_triggered() {
    if ( cm==true) return;
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable * t = cursor.currentTable();
    if (t != 0) {
        QTextTableCell c = t->cellAt(cursor);
        int column = c.column();
        t->insertColumns(column+1,1);
    }
}


void OutLinerViewer::on_colorbox_colorSelected(QColor color){
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat fmt;
    fmt.setForeground(color);
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(fmt);
    ui->textEdit->mergeCurrentCharFormat(fmt);

}


void OutLinerViewer::on_textEdit_anchorClicked(const QUrl &link){
    QList<QTreeWidgetItem *> items = ui->TOC->findItems(link.path(),Qt::MatchExactly | Qt::MatchRecursive);
    if ( items.size() == 0 ) {
        newNodeDialog newnodedialog(this);
        if (newnodedialog.exec() == QDialog::Accepted ) {
            noteItem * c = ui->TOC->currentItem();
            QString s(link.path());
            switch (newnodedialog.typeOfNode()) {
               case 0: addChild(c,s);break;
               case 1: addChild(c->parent(),s);break;
               case 2:;addChild((noteItem*)ui->TOC->invisibleRootItem(),s);break;

            }
        }

    } else {
        ui->TOC->setCurrentItem(items[0]);
    }

}

void OutLinerViewer::on_action_Save_triggered() {
    noteItem *current = ui->TOC->currentItem();
    if ( current == nullptr ) return;
    current->setHtml(ui->textEdit->toHtml());
    QByteArray qa,qb;
    QDataStream out(&qa,QIODevice::WriteOnly);
    out << (quint32)MAGIC;
    int nb = ui->TOC->invisibleRootItem()->childCount();
    out << nb;
    for (int i =0; i < nb;i++)
        out << (noteItem *) (ui->TOC->invisibleRootItem()->child(i));

    if (password.size()==0) {
        qb=qa;
    } else {
        qb=encrypt(password,qa);
    }
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(qb);
    file.close();
}

void OutLinerViewer::on_actionPass_word_triggered(){
    bool pwdok = false;
    while  (!pwdok) {
        bool ok;
        QString p1 = QInputDialog::getText(this,tr("Choose Password"),tr("Enter a password:"),QLineEdit::Password,"",&ok);
        if (!ok) return;
        QString p2 = QInputDialog::getText(this,tr("Choose Password"),tr("Enter a password again:"),QLineEdit::Password,"",&ok);
        if (!ok) return;

        if (p1!=p2) {
            QMessageBox::warning(this,tr("Error"),QString(tr("The password are diffrent.")));
        } else {
            pwdok = true;
            setPassword(p1);
        }

    }

}


void OutLinerViewer::openFile(){
    QFile file(filename);
    ui->TOC->clear();
    if (! file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this,tr("Error"),QString(tr("The file %1 doesn't exist.")).arg(filename));
        return;
    };
    QByteArray qa=file.readAll();
    file.close();
    QByteArray qb;
    if ( qa.startsWith("AES") == true) {
        bool ok;
        setPassword(QInputDialog::getText(this,tr("Password required"),tr("Enter a password:"),QLineEdit::Password,"",&ok));
        if (ok == false ) return;
        qb=decrypt(password,qa);
    } else {
        qb=qa;
    }
    QDataStream in(qb);
    quint32 magic;
    in >> magic;

    if ( magic != MAGIC ) {
        QMessageBox::warning(this,tr("Error"),QString(tr("The file %1 has a bad format.")).arg(filename));
        setPassword("");
        return;
    }
    int nb;
    in >> nb;
    for (int i = 0; i <nb ;i++) {
        noteItem *current = new noteItem();
        in >> current;
        ui->TOC->invisibleRootItem()->addChild(current);
    }
    file.close();
    ui->TOC->setCurrentItem(ui->TOC->invisibleRootItem()->child(0));
}

void OutLinerViewer::on_action_Open_triggered() {
    QString f = QFileDialog::getOpenFileName(this,tr("Open a file"),"..",QString(),nullptr,QFileDialog::DontUseNativeDialog );
    if (f != "") {
        filename=f;
        openFile();
    }
}


void OutLinerViewer::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}



void OutLinerViewer::on_action_Italic_toggled(bool t) {
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->action_Italic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
void OutLinerViewer::on_action_Underline_toggled(bool t) {
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->action_Underline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}
void OutLinerViewer::on_action_Bold_toggled(bool t) {
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->action_Bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}
void OutLinerViewer::on_fontBox_activated(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void OutLinerViewer::on_sizeBox_activated(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}


void OutLinerViewer::on_TOC_currentItemChanged(QTreeWidgetItem *current,
                                               QTreeWidgetItem *previous) {
    noteItem *p = dynamic_cast<noteItem*>(previous);
    noteItem *c = dynamic_cast<noteItem*>(current);
    if (p != 0) {
        p->setHtml(ui->textEdit->toHtml());
    }
    if (c != 0) {
        ui->textEdit->setHtml(c->html());
    } else {
        ui->textEdit->setHtml("");
        ui->textEdit->setEnabled(false);
    }
    //if ((p != 0) && (c != 0))
}

void OutLinerViewer::on_TOC_itemSelectionChanged() {
    ui->textEdit->setEnabled(true);
}
void OutLinerViewer::on_textEdit_currentCharFormatChanged(const QTextCharFormat &format) {
    QFont f = format.font();
    ui->fontBox->setCurrentIndex(ui->fontBox->findText(QFontInfo(f).family()));
    ui->sizeBox->setCurrentIndex(ui->sizeBox->findText(QString::number(f.pointSize())));
    ui->action_Bold->setChecked(f.bold());
    ui->action_Italic->setChecked(f.italic());
    ui->action_Underline->setChecked(f.underline());
    ui->actionInsertLink->setChecked(format.isAnchor());
}


void OutLinerViewer::on_textEdit_cursorPositionChanged()
{
    Qt::Alignment a = ui->textEdit->alignment();
    if (a & Qt::AlignLeft)
        ui->actionLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        ui->actionCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        ui->actionRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        ui->actionFill->setChecked(true);
}

void OutLinerViewer::on_textEdit_focus(){
    ui->textEdit->setEnableButton(true);
    ui->TOC->setEnableButton(false);
}

void OutLinerViewer::on_TOC_focus(){
    ui->textEdit->setEnableButton(false);
    ui->TOC->setEnableButton(true);
}

void OutLinerViewer::on_action_New_triggered(){
    ui->TOC->clear();
    ui->textEdit->setText("");
    setPassword("");
}


void OutLinerViewer::setPassword(QString p){
    password = p;
    if ( p == "" ){
        cryptLabel.setText(tr("Uncrypted"));
        cryptLabel.setStyleSheet("color:red");
    } else {
        cryptLabel.setText(tr("Crypted"));
        cryptLabel.setStyleSheet("color:green");
    }
}


void OutLinerViewer::saveConfig(){
    config.setValue("filename",filename);
    config.setValue("geometry",geometry());
    config.setValue("splitterSizes", ui->splitter->saveState());
}


void OutLinerViewer::closeEvent(QCloseEvent * event){
    saveConfig();
    event->accept();
}
