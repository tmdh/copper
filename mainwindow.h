#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>
#include <QTreeView>

const QString CODE_DIRECTORY = "/home/tareque/codeforces";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;

private slots:
    void openSelectedFile(const QModelIndex &index);
    void openNewFileDialog();
    void buildAndRunCurrentFile();
    void closeTab(int index);

private:
    QPushButton *m_button;
    QTreeView *treeview;
    QFileSystemModel *model;
    QTabWidget *tabWidget;
};

#endif