#include <QNetworkAccessManager>
#include <QObject>
#include <QNetworkReply>
#include "testcase.h"

TestCaseLoader::TestCaseLoader(QString problemId) {
    if (problemId.back().isLetter()) {
        contestId = problemId.left(problemId.length() - 1);
        index = problemId.back();
    } else { // 1282a1
        contestId = problemId.left(problemId.length() - 2);
        index = problemId.right(2).toUpper();
    }
    testCases = QList<TestCase>();
}

void TestCaseLoader::load() {
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QUrl url("https://codeforces.com/problemset/problem/" + contestId + "/" + index);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            // TODO
            emit loadFinished();
        } else {
            // Handle the error here
        }
        reply->deleteLater();
    });
}

