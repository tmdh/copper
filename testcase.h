#include <QtCore>

class TestCase {
public:
    QString input;
    QString expected;
    TestCase(QString input, QString expected) {
        this->input = input;
        this->expected = expected;
    }
};


class TestCaseLoader : public QObject {
    Q_OBJECT
    QString contestId;
    QString index;
    QList<TestCase> testCases;
public:
    TestCaseLoader(QString problemId);
    void load();
signals:
    void loadFinished();
};
