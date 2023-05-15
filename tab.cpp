#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include <QProcess>
#include <QFileInfo>
#include "tab.h"
#include "testcaseloader.h"
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
    QPushButton* addTestCaseButton = new QPushButton("Add test case");
    buttonsLayout->addWidget(addTestCaseButton);
    QPushButton* loadTestCasesButton = new QPushButton("Load test cases");
    buttonsLayout->addWidget(loadTestCasesButton);
    QPushButton* runTestCasesButton = new QPushButton("Run test cases");
    buttonsLayout->addWidget(runTestCasesButton);
    sideBarLayout->addLayout(buttonsLayout);

    connect(loadTestCasesButton, &QPushButton::clicked, [this](bool checked) {
        this->loadTestCases();
    });

    connect(runTestCasesButton, &QPushButton::clicked, [this](bool checked) {
        this->runTestCases();
    });

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

void Tab::runTestCases() {
    int count = testCasesLayout->count();
    for (int i = 0; i < count; i++) {
        QWidget* w = testCasesLayout->itemAt(i)->widget();
        TestCaseWidget* t = qobject_cast<TestCaseWidget*>(w);

        QProcess* process1 = new QProcess(this);
        process1->setProgram("/usr/bin/g++");
        process1->setArguments(QStringList() << "-o" << EXECUTABLE_PATH << m_filePath);
        QProcess* process2 = new QProcess(this);
        process2->setProgram(EXECUTABLE_PATH);
        connect(process1, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [t, process2](int exitCode, QProcess::ExitStatus exitStatus){
                if (exitStatus == QProcess::ExitStatus::NormalExit) {
                    process2->start();
                    process2->write(t->input().toUtf8());
                    process2->closeWriteChannel();
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

void Tab::loadTestCases() {
    QFileInfo fileInfo(m_filePath);
    TestCaseLoader* loader = new TestCaseLoader(fileInfo.baseName());
    connect(loader, &TestCaseLoader::loadFinished, [loader, this]() {
        int count = testCasesLayout->count();
        int i = 0;
        if (count == 1) {
            QWidget *w = testCasesLayout->itemAt(0)->widget();
            TestCaseWidget *t = qobject_cast<TestCaseWidget *>(w);
            if (t->input() == "" && t->output() == "" && t->expected() == "") {
                if (loader->testCaseObjects.size() > 0) {
                    t->setInput(loader->testCaseObjects[0].input);
                    t->setExpected(loader->testCaseObjects[0].expected);
                }
            }
            i++;
        }
        for (; i < loader->testCaseObjects.size(); ++i) {
            TestCaseWidget *t = new TestCaseWidget(loader->testCaseObjects[i].input, loader->testCaseObjects[i].expected);
            testCasesLayout->addWidget(t);
        }
    });
    loader->load();
}
