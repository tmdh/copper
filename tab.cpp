#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include "tab.h"
#include "testcasewidget.h"

Tab::Tab(const QString& filePath, QWidget* parent) {
    auto editor = KTextEditor::Editor::instance();
    auto doc = editor->createDocument(this);
    m_view = doc->createView(nullptr);
    QUrl url = QUrl::fromLocalFile(filePath);
    m_view->document()->openUrl(url);
    addWidget(m_view);
    
    QWidget* sideBar = new QWidget;
    QVBoxLayout* sideBarLayout = new QVBoxLayout();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* button = new QPushButton("Add test case");
    buttonsLayout->addWidget(button);
    sideBarLayout->addLayout(buttonsLayout);

    QScrollArea* testCasesArea = new QScrollArea();
    QWidget* testCases = new QWidget;
    QVBoxLayout* testCasesLayout = new QVBoxLayout();
    for (size_t i = 0; i < 6; i++)
    {
        TestCaseWidget* testCase = new TestCaseWidget();
        testCasesLayout->addWidget(testCase);
    }
    testCases->setLayout(testCasesLayout);
    testCasesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    testCasesArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    testCasesArea->setWidgetResizable(true);
    testCasesArea->setWidget(testCases);
    sideBarLayout->addWidget(testCasesArea);

    sideBar->setLayout(sideBarLayout);
    addWidget(sideBar);
}
