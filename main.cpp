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
    model->appendRow(new QStandardItem(QString("item")));
    treeview->setModel(model);
    
    QTextEdit *textedit = new QTextEdit(splitter);

    window->setCentralWidget(splitter);
    window->setWindowState(Qt::WindowMaximized);
    window->show();
    app.exec();
    return 0;
}