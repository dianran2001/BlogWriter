#include "fileop.h"

FileOp::FileOp(QString path)
{
    dir = new QDir(path);
    QStringList filters;
    filters << "*.md" << "*.md.marked";
    dir->setNameFilters(filters);
    dir->setSorting(QDir::Time);
   // dir->setSorting(QDir::Reversed);
}

FileOp::~FileOp()
{
    delete dir;
}

QStringList FileOp::ListAllArticle()
{
    dir->setPath("content");
    return dir->entryList();
}

QString FileOp::GetFilePath(const QString & fileName)
{
    return dir->absoluteFilePath(fileName);
}

void FileOp::debug()
{
    qDebug() << this->ListAllArticle();
    qDebug() << this->GetFilePath("language-lua.md");

}

QStringList FileOp::SplitSourceArticle(const QString & fileName)
{
    QFile file;
    QStringList splitedContent;

    file.setFileName("content/"+fileName+".md");
    if(!file.exists()){
        file.setFileName("content/"+fileName+".md.marked");
    }
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString line;
    QString content;

    for  (int count=0; count <7; count++) {
         line = stream.readLine(); // 不包括“\n”的一行文本
         if(line.split(':')[0].trimmed() == "Date"){
             line = line.mid(5);
         }else{
             line = line.split(':')[1];
         }
         splitedContent << line.trimmed();
     }


     while ( !stream.atEnd() ) {
         line = stream.readLine();
         content += line.trimmed()+"\n";
     }
     splitedContent << content;


//test
     /**
    foreach(QString line,splitedContent){
        qDebug()<< line;
    }
    **/


    file.close();
    return splitedContent;
}

void  FileOp::SaveArticle(QStringList &articleContent)
{
    QFile file( "content/"+articleContent[4]+".md.marked" );
    QMessageBox::StandardButton okOrNo=QMessageBox::Yes;
    if(file.exists()){
        okOrNo = QMessageBox::question(NULL, "File name exists", "Do you want to overwrite this file? if not click no and channge your slug",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    }else{
        file.setFileName("content/"+articleContent[4]+".md" );
        if(file.exists()){
            okOrNo = QMessageBox::question(NULL, "File name exists", "Do you want to overwrite this file? if not click no and channge your slug",
                                  QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        }
    }
    if(okOrNo == QMessageBox::No){
        return;
    }

    file.open( QIODevice::WriteOnly );
    QTextStream stream( &file );
    stream << "Title: "+ articleContent[0]+"\n";
    stream << "Date: "+ articleContent[1]+"\n";
    stream << "Category: "+ articleContent[2]+"\n";
    stream << "Tags: "+ articleContent[3]+"\n";
    stream << "Slug: "+ articleContent[4]+"\n";
    stream << "Author: "+ articleContent[5]+"\n";
    stream << "Summary: "+ articleContent[6]+"\n";
    stream << articleContent[7]+"\n";
    QMessageBox::information(NULL, "Save", "Success");
    file.close();
}
