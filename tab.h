#ifndef TAB_H
#define TAB_H

#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <QProcess>
#include <QSplitter>
#include <QVBoxLayout>

const QString EXECUTABLE_PATH = "/home/tareque/codeforces/bin/program";

class Tab : public QSplitter
{
    Q_OBJECT

    KTextEditor::View *m_view;
    KTextEditor::Document *m_doc;
    QVBoxLayout *testCasesLayout;
    QString m_filePath;

public:
    Tab(const QString &filePath, QWidget *parent = nullptr);
    KTextEditor::Document *document();
    void loadTestCases();
    void runTestCases();
};

#endif