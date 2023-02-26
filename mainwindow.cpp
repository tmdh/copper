#include <QDir>
#include <QPushButton>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTextEdit>
#include <QTreeView>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    treeview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    treeview->setHeaderHidden(true);

    QTextEdit *textedit = new QTextEdit(splitter);
    m_button = new QPushButton(splitter);
    connect(m_button, &QPushButton::released, this, &MainWindow::cl);

    setCentralWidget(splitter);
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::cl()
{
}
