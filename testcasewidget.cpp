#include <QLabel>
#include <QTextEdit>
#include <QBoxLayout>
#include <QSizePolicy>
#include <QSpacerItem>
#include "testcasewidget.h"

TestCaseWidget::TestCaseWidget(QWidget* parent) {
    QLabel* l1 = new QLabel("Input:");
    QTextEdit* inputTextEdit = new QTextEdit;
    inputTextEdit->setFixedHeight(100);
    inputTextEdit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    QLabel* l2 = new QLabel("Output:");
    QTextEdit* outputTextEdit = new QTextEdit;
    outputTextEdit->setFixedHeight(100);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom ,this);
    layout->setSpacing(0);
    layout->addWidget(l1);
    layout->addWidget(inputTextEdit);
    layout->addWidget(l2);
    layout->addWidget(outputTextEdit);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
}