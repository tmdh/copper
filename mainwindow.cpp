#include <QDir>
#include <QFileSystemModel>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>
#include <QTabWidget>
#include <QSplitter>
#include <QShortcut>
#include <QInputDialog>
#include <QFile>

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
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    
    setCentralWidget(m_mainSplitter);
    m_mainSplitter->setWidths();
    connect(treeview, &QTreeView::clicked, this, &MainWindow::openSelectedFile);

    QShortcut *createFileShortcut = new QShortcut(QKeySequence(tr("Ctrl+N", "File|New")), this);
    connect(createFileShortcut, &QShortcut::activated, this, &MainWindow::openNewFileDialog);

    QShortcut *buildShortcut = new QShortcut(QKeySequence(tr("Ctrl+B", "File|Build")), this);
    connect(buildShortcut, &QShortcut::activated, this, &MainWindow::buildAndRunCurrentFile);

    setWindowState(Qt::WindowMaximized);
}

void MainWindow::openSelectedFile(const QModelIndex &index) {
    QString selectedFile = model->filePath(index);
    Tab* tab = new Tab(selectedFile);
    tabWidget->addTab(tab, model->fileName(index));
    tabWidget->setCurrentWidget(tab);
}

void MainWindow::openNewFileDialog() {
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("Enter file name to create or open"),
        tr("File name:"), QLineEdit::Normal,
        QDir::home().dirName(), &ok);
    if (ok && !fileName.isEmpty()) {
        QString filePath = CODE_DIRECTORY + "/" + fileName;
        QFile file(filePath);
        file.open(QIODevice::WriteOnly);
        file.close();
        Tab* tab = new Tab(filePath);
        tabWidget->addTab(tab, fileName);
        tabWidget->setCurrentWidget(tab);
    }
}

void MainWindow::buildAndRunCurrentFile() {
    Tab* currentTab = qobject_cast<Tab*>(tabWidget->currentWidget());
    currentTab->buildAndRunFile();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    int count = tabWidget->count();
    for (int i = 0; i < count; i++) {
        QWidget* w = tabWidget->widget(i);
        Tab* t = qobject_cast<Tab*>(w);
        t->document()->closeUrl();
    }
}

void MainWindow::closeTab(int index) {
    QWidget* w = tabWidget->widget(index);
    Tab* t = qobject_cast<Tab*>(w);
    t->document()->closeUrl();
    tabWidget->removeTab(index);
}
