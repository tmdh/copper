#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include <QProcess>
#include "tab.h"
#include "testcasewidget.h"

Tab::Tab(const QString& filePath, QWidget* parent) {
    m_filePath = filePath;
    // Create a KTextEditor document and add it to splitter
    auto editor = KTextEditor::Editor::instance();
    m_doc = editor->createDocument(this);
    m_view = m_doc->createView(nullptr);
    QUrl url = QUrl::fromLocalFile(filePath);
    m_view->document()->openUrl(url);
    addWidget(m_view);
    
    // Sidebar widget
    QWidget* sideBar = new QWidget;
    // Main vertical layout for sidebar
    QVBoxLayout* sideBarLayout = new QVBoxLayout();
    // Layout for buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* button = new QPushButton("Add test case");
    buttonsLayout->addWidget(button);
    sideBarLayout->addLayout(buttonsLayout);

    // Widget for test cases
    QWidget* testCases = new QWidget;
    testCasesLayout = new QVBoxLayout();
    // Single empty test case
    TestCaseWidget* testCase = new TestCaseWidget();
    testCasesLayout->addWidget(testCase);
    testCases->setLayout(testCasesLayout);

    QScrollArea* testCasesArea = new QScrollArea();
    testCasesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    testCasesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    testCasesArea->setWidgetResizable(true);
    testCasesArea->setWidget(testCases);
    sideBarLayout->addWidget(testCasesArea);

    sideBar->setLayout(sideBarLayout);
    addWidget(sideBar);
}

KTextEditor::Document *Tab::document()
{
    return m_doc;
}

void Tab::buildAndRunFile() {
    int count = testCasesLayout->count();
    for (int i = 0; i < count; i++) {
        QWidget* w = testCasesLayout->itemAt(i)->widget();
        TestCaseWidget* t = qobject_cast<TestCaseWidget*>(w);

        // Add a newline to input if there isn't any
        t->addNewLine();

        QProcess* process1 = new QProcess(this);
        process1->setProgram("/usr/bin/g++");
        process1->setArguments(QStringList() << "-o" << "/home/tareque/codeforces/bin/program" << m_filePath);
        QProcess* process2 = new QProcess(this);
        process2->setProgram("/home/tareque/codeforces/bin/program");
        connect(process1, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [t, process2](int exitCode, QProcess::ExitStatus exitStatus){
                if (exitStatus == QProcess::ExitStatus::NormalExit) {
                    process2->start();
                    process2->write(t->input().toUtf8());
                }
            }
        );
        connect(process2, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [t, process2](int exitCode, QProcess::ExitStatus exitStatus){
                if (exitStatus == QProcess::ExitStatus::NormalExit) {
                    t->setOutput(QString::fromUtf8(process2->readAllStandardOutput()));
                }
            }
        );
        process1->start();
    }
}
