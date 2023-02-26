#include <QDir>
#include <QFileSystemModel>
#include <QPushButton>
#include <QSplitter>
#include <QTextEdit>
#include <QTreeView>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QSplitter *splitter = new QSplitter;

    QTreeView *treeview = new QTreeView(splitter);
    QFileSystemModel *model = new QFileSystemModel();
    model->setRootPath(CODE_DIRECTORY);
    treeview->setModel(model);
    treeview->setRootIndex(model->index(CODE_DIRECTORY));
    treeview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int i = 1; i < 4; i++) {
        treeview->setColumnHidden(i, true);
    }
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
