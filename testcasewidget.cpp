#include "testcasewidget.h"
#include <QBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QTextEdit>

TestCaseWidget::TestCaseWidget(const QString &input, const QString &expected, QWidget *parent)
{
    QLabel *l1 = new QLabel("Input:");
    inputTextEdit = new QTextEdit;
    inputTextEdit->setText(input);
    inputTextEdit->setFixedHeight(100);
    inputTextEdit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    QLabel *l2 = new QLabel("Output:");
    outputTextEdit = new QTextEdit;
    outputTextEdit->setFixedHeight(100);
    QLabel *l3 = new QLabel("Expected:");
    expectedTextEdit = new QTextEdit;
    expectedTextEdit->setText(expected);
    expectedTextEdit->setFixedHeight(100);

    connect(outputTextEdit, &QTextEdit::textChanged, this, &TestCaseWidget::compare);
    connect(expectedTextEdit, &QTextEdit::textChanged, this, &TestCaseWidget::compare);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setSpacing(0);
    layout->addWidget(l1);
    layout->addWidget(inputTextEdit);
    layout->addWidget(l2);
    layout->addWidget(outputTextEdit);
    layout->addWidget(l3);
    layout->addWidget(expectedTextEdit);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding));
}

void TestCaseWidget::setInput(const QString &newInput)
{
    inputTextEdit->setText(newInput);
}

void TestCaseWidget::setOutput(const QString &newOutput)
{
    outputTextEdit->setText(newOutput);
}

void TestCaseWidget::setExpected(const QString &newExpected)
{
    expectedTextEdit->setText(newExpected);
}

void TestCaseWidget::compare()
{
    if (outputTextEdit->toPlainText() != expectedTextEdit->toPlainText()) {
        outputTextEdit->setStyleSheet("QTextEdit { border: 1px solid red; }");
    } else {
        outputTextEdit->setStyleSheet("");
    }
}
