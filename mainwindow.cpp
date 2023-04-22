#include <QDir>
#include <QFileSystemModel>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>
#include <QTabWidget>
#include <QSplitter>


#include "mainwindow.h"
#include "mainsplitter.h"
#include "tab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainSplitter *m_mainSplitter = new MainSplitter;

    // File Tree
    treeview = new QTreeView(m_mainSplitter);
    model = new QFileSystemModel();
    model->setRootPath(CODE_DIRECTORY);
    treeview->setModel(model);
    treeview->setRootIndex(model->index(CODE_DIRECTORY));
    treeview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int i = 1; i < 4; i++) {
        treeview->setColumnHidden(i, true);
    }
    treeview->setHeaderHidden(true);

    // Tab Widget
    tabWidget = new QTabWidget(m_mainSplitter);
    tabWidget->setTabsClosable(true);
    
    setCentralWidget(m_mainSplitter);
    m_mainSplitter->setWidths();
    connect(treeview, &QTreeView::clicked, this, &MainWindow::openSelectedFile);
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::openSelectedFile(const QModelIndex &index) {
    QString selectedFile = model->filePath(index);
    Tab* tab = new Tab(selectedFile);
    tabWidget->addTab(tab, model->fileName(index));
    tabWidget->setCurrentWidget(tab);
}
