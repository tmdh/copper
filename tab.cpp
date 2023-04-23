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

    QScrollArea* s = new QScrollArea();
    QWidget* w = new QWidget;
    QVBoxLayout* l = new QVBoxLayout();
    w->setLayout(l);
    for (size_t i = 0; i < 6; i++)
    {
        TestCaseWidget* b = new TestCaseWidget();
        l->addWidget(b);
    }
    w->setLayout(l);
    s->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    s->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    s->setWidgetResizable(true);
    s->setWidget(w);

    addWidget(s);
}
