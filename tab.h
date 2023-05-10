#ifndef TAB_H
#define TAB_H

#include <QSplitter>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>

class Tab : public QSplitter {
    Q_OBJECT

    KTextEditor::View* m_view;
    KTextEditor::Document* m_doc;

public:
    Tab(const QString& filePath, QWidget* parent = nullptr);
    KTextEditor::Document* document();

public slots:
    void buildAndRunFile();
};

#endif