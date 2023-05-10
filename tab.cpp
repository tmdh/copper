#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "tab.h"
#include "testcasewidget.h"

Tab::Tab(const QString& filePath, QWidget* parent) {
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
    QVBoxLayout* testCasesLayout = new QVBoxLayout();
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
    
}
