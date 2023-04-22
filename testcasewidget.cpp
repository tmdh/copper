#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSizePolicy>
#include "testcasewidget.h"

TestCaseWidget::TestCaseWidget(QWidget* parent) {
    QLabel* l1 = new QLabel("Input:");
    QTextEdit* inputTextEdit = new QTextEdit;
    inputTextEdit->setFixedHeight(100);
    inputTextEdit->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    QLabel* l2 = new QLabel("Output:");
    QTextEdit* outputTextEdit = new QTextEdit;
    outputTextEdit->setFixedHeight(100);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(l1);
    layout->addWidget(inputTextEdit);
    layout->addWidget(l2);
    layout->addWidget(outputTextEdit);
}