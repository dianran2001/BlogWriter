#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <fileop.h>
#include <myeditwidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void NewFile();
    void SaveFile();
    void Pulish();
    void FileDoubleClick(QTreeWidgetItem *, int );
private:
    void ConfigMainWin();
    void CreateToolBar();
    void CreateStatusBar();
    void CreateFileView();
    void CreateFunctionArea();
    void RefreshFileList();
private:
    QAction *newFileAciton;
    QAction *storeAction;
    QAction *publishAction;
    QLabel  *statusLabel;
    //QTextEdit *textEdit;
    MyEditWidget *myEdit;
    QTreeWidget *tree;
    QList <QTreeWidgetItem *> itemContainer;
    FileOp *file;
};

#endif // MAINWINDOW_H
