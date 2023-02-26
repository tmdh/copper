#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

const QString CODE_DIRECTORY = "/home/tareque/codeforces";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void cl();

private:
    QPushButton *m_button;
};

#endif