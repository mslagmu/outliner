#ifndef OUTLINERVIEWER_H
#define OUTLINERVIEWER_H

#include <QMainWindow>
#include <QObject>
#include<QTreeWidgetItem>
#include<QSettings>
#include<QLabel>
#include<QTextCharFormat>
#include"newnodedialog.h"
#include "noteitem.h"

namespace Ui {
class OutLinerViewer;
}

class OutLinerViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit OutLinerViewer(QWidget *parent = 0);
    ~OutLinerViewer();

    void closeEvent(QCloseEvent * event);
    void saveConfig();




public slots:
    void on_actionAddItem_triggered();
    void on_actionRemoveItem_triggered();
    void on_actionAddChild_triggered();
    void on_actionInsertLink_triggered();
    void on_actionIndent_triggered();
    void on_actionUnindent_triggered();
    void on_actionInsert_Table_triggered();
    void on_actionInsert_Row_triggered();
    void on_actionDelete_Table_triggered();
    void on_actionDelete_Row_triggered();
    void on_actionDelete_Column_triggered();
    void on_actionInsert_Column_triggered();
    void on_action_Save_triggered();
    void on_action_Open_triggered();
    void on_action_Italic_toggled(bool t);
    void on_action_Underline_toggled(bool t);
    void on_action_Bold_toggled(bool t);
    void on_actionPrevious_triggered();
    void on_actionNext_triggered();
    void on_fontBox_activated(const QString &f);
    void on_sizeBox_activated(const QString &f);
    void on_TOC_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void on_TOC_itemSelectionChanged();
    void on_textEdit_currentCharFormatChanged(const QTextCharFormat &format);
    void on_textEdit_cursorPositionChanged();
    void on_textEdit_focus();
    void on_TOC_focus();
    void on_action_New_triggered();
    void on_colorbox_colorSelected(QColor color);
    void on_actionPass_word_triggered();
    void textAlign(QAction *a);
    void on_textEdit_anchorClicked(const QUrl &link);

private:
    Ui::OutLinerViewer *ui;
    int cm=false;
    QString filename="toto.txt";
    QSettings config;
    QString password;
    void setPassword(QString p);
    QLabel  cryptLabel;

    void addChild(noteItem* current, QString text="");

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    void openFile();
    QList<noteItem*> history;
    bool historyManage = false;
    int historyIndex = -1;
};

#endif // OUTLINERVIEWER_H
