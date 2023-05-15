#include "testcaseloader.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QMessageBox>

TestCaseLoader::TestCaseLoader(QString problemId) {
    if (problemId.back().isLetter()) {
        contestId = problemId.left(problemId.length() - 1);
        index = problemId.back();
    } else { // 1282a1
        contestId = problemId.left(problemId.length() - 2);
        index = problemId.right(2).toUpper();
    }
    testCaseObjects = QList<TestCaseObject>();
}

void TestCaseLoader::load() {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QUrl url("https://codeforces.com/problemset/problem/" + contestId + "/" + index);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            uintptr_t length = 0;
            qDebug() << data.data();
            const TestCase* testCases = parse_testcase_ffi(data.data(), &length);
            for (int i = 0; i < length; ++i) {
                TestCaseObject t;
                t.input = testCases[i].input;
                t.expected = testCases[i].expected;
                testCaseObjects << t;
            }
            emit loadFinished();
        } else {
            QMessageBox messageBox;
            messageBox.critical(nullptr, "Error", reply->errorString());
            messageBox.show();
        }
        reply->deleteLater();
    });
}
