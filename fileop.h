#ifndef FILEOP_H
#define FILEOP_H

#include<QtGui>

class FileOp
{
public:
    FileOp(QString path="content");
    ~FileOp();
    QStringList ListAllArticle();
    QString GetFilePath(const QString & fileName);
    QStringList SplitSourceArticle(const QString & fileName);
    void SaveArticle(QStringList &articleContent);
    void debug();
private:
    QDir *dir;
};

#endif // FILEOP_H
