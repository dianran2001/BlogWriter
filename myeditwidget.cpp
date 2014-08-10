#include "myeditwidget.h"

MyEditWidget::MyEditWidget(QWidget *parent) :
    QWidget(parent)
{
    titleLabel = new QLabel("Title");
    titleEdit = new QLineEdit();

    dateLabel = new QLabel("Data");
    dateEdit = new QLineEdit();

    categoryLabel = new QLabel("Category");
    categoryEdit = new QLineEdit();

    tagsLabel = new QLabel("Tags");
    tagsEdit = new QLineEdit();

    slugLabel = new QLabel("Slug");
    slugEdit = new QLineEdit();

    authorLabel = new QLabel("Author");
    authorEdit = new QLineEdit();

   QGridLayout *topLayout = new QGridLayout();

   topLayout->addWidget(titleLabel,0,0);
   topLayout->addWidget(titleEdit,0,1);
   topLayout->addWidget(dateLabel,0,2);
   topLayout->addWidget(dateEdit,0,3);
   topLayout->addWidget(categoryLabel,1,0);
   topLayout->addWidget(categoryEdit,1,1);
   topLayout->addWidget(tagsLabel,1,2);
   topLayout->addWidget(tagsEdit,1,3);
   topLayout->addWidget(slugLabel,2,0);
   topLayout->addWidget(slugEdit,2,1);
   topLayout->addWidget(authorLabel,2,2);
   topLayout->addWidget(authorEdit,2,3);

   summaryLabel = new QLabel("Summary");
   summaryEdit = new QLineEdit();
   contentEdit = new QTextEdit();
   //set font
   QFont editfont;
   editfont.setPixelSize(13);
   editfont.setStyleHint(QFont::AnyStyle);
   contentEdit->setCurrentFont(editfont);
   //
   QHBoxLayout *summaryLayout = new QHBoxLayout();
   summaryLayout->addWidget(summaryLabel);
   summaryLayout->addWidget(summaryEdit);

   QHBoxLayout *bottomLayout = new QHBoxLayout();
   bottomLayout->addWidget(contentEdit);

   QVBoxLayout *mainLayout = new QVBoxLayout(this);
   mainLayout->addLayout(topLayout);
   mainLayout->addLayout(summaryLayout);
   mainLayout->addLayout(bottomLayout);


}
void MyEditWidget::EditContentSet(QStringList& ContentList){
    titleEdit->setText(ContentList[0]);
    dateEdit->setText(ContentList[1]);
    categoryEdit->setText(ContentList[2]);
    tagsEdit->setText(ContentList[3]);
    slugEdit->setText(ContentList[4]);
    authorEdit->setText(ContentList[5]);
    summaryEdit->setText(ContentList[6]);
    contentEdit->setText(ContentList[7]);
}
QStringList  MyEditWidget::GetAllContent(){
    QStringList allContent;
    allContent<< titleEdit->text();
    allContent<< dateEdit->text();
    allContent<< categoryEdit->text();
    allContent<< tagsEdit->text();
    allContent<< slugEdit->text();
    allContent<< authorEdit->text();
    allContent<< summaryEdit->text();
    allContent<< contentEdit->toPlainText();
    return allContent;
}
