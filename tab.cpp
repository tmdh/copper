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
    QWidget* w = new QWidget;
    QVBoxLayout* l = new QVBoxLayout(w);
    w->setLayout(l);
    TestCaseWidget* b = new TestCaseWidget();
    l->addWidget(b);
    addWidget(w);
}
