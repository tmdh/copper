#ifndef TESTCASE_H
#define TESTCASE_H
#include <QtCore>

struct TestCase {
    const char *input;
    const char *expected;
};

class TestCaseObject {
public:
    QString input, expected;
};

extern "C" {
    const TestCase *parse_testcase_ffi(const char *source, uintptr_t *length);
};

class TestCaseLoader : public QObject {
    Q_OBJECT
    QString contestId;
    QString index;
public:
    TestCaseLoader(QString problemId);
    void load();
    QList<TestCaseObject> testCaseObjects;
signals:
    void loadFinished();
};
#endif
