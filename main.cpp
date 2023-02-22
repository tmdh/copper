#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>
#include <QTreeView>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow* window = new QMainWindow;
    
    QSplitter *splitter = new QSplitter;
    
    QTreeView *treeview = new QTreeView(splitter);
    QStandardItemModel *model = new QStandardItemModel;
    QDir directory("/home/tareque/codeforces");
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot);
    QFileInfoList list = directory.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        model->appendRow(new QStandardItem(fileInfo.fileName()));
    }
    treeview->setModel(model);
    
    QTextEdit *textedit = new QTextEdit(splitter);

    window->setCentralWidget(splitter);
    window->setWindowState(Qt::WindowMaximized);
    window->show();
    app.exec();
    return 0;
}