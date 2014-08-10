#ifndef MYEDITWIDGET_H
#define MYEDITWIDGET_H

#include <QWidget>
#include <QtGui>
//#include "Python.h"
#include <QProcess>

class MyEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyEditWidget(QWidget *parent = 0);
    void EditContentSet(QStringList& ContentList);
    QStringList GetAllContent();
    
signals:
    
public slots:
private:
    QLineEdit *titleEdit;
    QLineEdit *dateEdit;
    QLineEdit *categoryEdit;
    QLineEdit *tagsEdit;
    QLineEdit *slugEdit;
    QLineEdit *authorEdit;
    QLineEdit *summaryEdit;
    QTextEdit *contentEdit;


    QLabel *titleLabel;
    QLabel *dateLabel;
    QLabel *categoryLabel;
    QLabel *tagsLabel;
    QLabel *slugLabel;
    QLabel *authorLabel;
    QLabel *summaryLabel;

};

#endif // MYEDITWIDGET_H
