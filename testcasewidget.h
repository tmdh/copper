#ifndef TASECASEWIDGET_H
#define TASECASEWIDGET_H

#include <QGroupBox>
#include <QTextEdit>

class TestCaseWidget : public QWidget {
    Q_OBJECT

    QTextEdit* inputTextEdit;
    QTextEdit* outputTextEdit;
    QTextEdit* expectedTextEdit;

public:
    TestCaseWidget(const QString& input = "", const QString& expected = "", QWidget* parent = nullptr);
    QString input() { return inputTextEdit->toPlainText(); }
    QString output() { return outputTextEdit->toPlainText(); }
    QString expected() { return expectedTextEdit->toPlainText(); }
    void setOutput(const QString& newOutput);
    void addNewLine();
};

#endif
