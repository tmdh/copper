#ifndef TAB_H
#define TAB_H

#include <QSplitter>
#include <QVBoxLayout>
#include <QProcess>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>

class Tab : public QSplitter {
    Q_OBJECT

    KTextEditor::View* m_view;
    KTextEditor::Document* m_doc;
    QVBoxLayout* testCasesLayout;
    QString m_filePath;

public:
    Tab(const QString& filePath, QWidget* parent = nullptr);
    KTextEditor::Document* document();
    void buildAndRunFile();

private slots:
    void buildFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif