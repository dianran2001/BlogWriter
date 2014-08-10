#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ConfigMainWin();
    CreateToolBar();
    CreateFunctionArea();
    CreateStatusBar();

}

MainWindow::~MainWindow()
{
    
}

void MainWindow::CreateToolBar()
{
    //new file button
    newFileAciton = new QAction(this);
    newFileAciton->setShortcut(QKeySequence::Open);
    newFileAciton->setStatusTip(tr("New article."));
    newFileAciton->setIcon(QIcon(":/image/new_blog.png")); // Add code
    connect(newFileAciton, SIGNAL(triggered()), this, SLOT(NewFile()));

    //store button
    storeAction = new QAction(this);
    storeAction->setShortcut(QKeySequence::Save);
    storeAction->setStatusTip(tr("Save new article."));
    storeAction->setIcon(QIcon(":/image/store.png")); // Add code
    connect(storeAction, SIGNAL(triggered()), this, SLOT(SaveFile()));

    //publish button
    publishAction = new QAction(this);
    publishAction->setStatusTip(tr("Publish."));
    publishAction->setIcon(QIcon(":/image/publish.png")); // Add code
    connect(publishAction, SIGNAL(triggered()), this, SLOT(Pulish()));

    //add all button to the toolbar
    QToolBar *toolBar = addToolBar(tr("&Tool"));
    toolBar->addAction(newFileAciton);
    toolBar->addAction(storeAction);
    toolBar->addAction(publishAction);
}
void MainWindow::ConfigMainWin()
{
    //set window size and move to the “center”
    resize(550,680);
    move(390,0);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
}

void MainWindow::CreateStatusBar()
{
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(statusLabel->sizeHint());
    statusLabel->setAlignment(Qt::AlignHCenter);

    statusBar()->addWidget(statusLabel);
}

void MainWindow::CreateFunctionArea()
{
    //The function area divid into two part at present.
    //one is the tree view of all article, and second is text editor.
    //there maybe thrid part of this function to view the markdown file in the future.
   /**
    QVBoxLayout *upDownlayout = new QVBoxLayout(this);
    textEdit = new QTextEdit(this);
    upDownlayout->addWidget(textEdit);
    this->setLayout(upDownlayout);
   **/
    CreateFileView();
    QSplitter *splitter= new QSplitter;
    myEdit = new MyEditWidget(this);

    splitter->addWidget(tree);
    splitter->addWidget(myEdit);

    QList<int> resize;
    resize<< 120<<450;
    splitter->setSizes(resize);
    this->setCentralWidget(splitter);
}


void MainWindow::CreateFileView()
{
    //The parent has been set,so it's possible not to call insert()
    QString Title("All articles");
    QStringList allArticles;
    file = new FileOp();
    allArticles = file->ListAllArticle();

    tree = new QTreeWidget(this);
    tree->setColumnCount(1);
    tree->setHeaderLabel(Title);
    //itemContainer.append(new QTreeWidgetItem(QStringList(QString("Leaf 1"))));
    foreach(QString article,allArticles){
        itemContainer.append(new QTreeWidgetItem(QStringList(QString(article.split('.')[0]))));
        // qDebug() << article;
     }

    tree->insertTopLevelItems(1,itemContainer);

    connect(tree, SIGNAL(itemDoubleClicked (QTreeWidgetItem *, int)),
                    this, SLOT(FileDoubleClick(QTreeWidgetItem *, int)));
}

void MainWindow::NewFile()
{
    QStringList ContentList;
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm"); //设置显示格式


    ContentList <<""<<str<<""<<""<<""<<tr("dianran")<<""<<"";
    myEdit->EditContentSet(ContentList);
}

void MainWindow::SaveFile()
{
    QStringList allContent;
    allContent = myEdit->GetAllContent();
    file->SaveArticle(allContent);
    RefreshFileList();
}

void MainWindow::Pulish()
{
    QProcess::execute("python autodb.py rebuild");
    QMessageBox::information(NULL, tr("publish"), tr("publish success"));
}

void MainWindow::FileDoubleClick(QTreeWidgetItem * item, int column){
    QStringList ContentList;
    ContentList = file->SplitSourceArticle(item->text(0));
    myEdit->EditContentSet(ContentList);
}

void MainWindow::RefreshFileList(){
     QStringList allArticles;
     int count;
     allArticles = file->ListAllArticle();
     count = itemContainer.count();
     itemContainer.clear();
     foreach(QString article,allArticles){
         itemContainer.append(new QTreeWidgetItem(QStringList(QString(article.split('.')[0]))));
          //qDebug() << article;
      }
     while(count--){
        tree->takeTopLevelItem(0);
     }

     tree->insertTopLevelItems(0,itemContainer);
}
