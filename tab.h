#ifndef TAB_H
#define TAB_H
#endif

#include <QSplitter>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>

class Tab : public QSplitter {
    Q_OBJECT

    KTextEditor::View* m_view;
    bool edited = false;
public:
    Tab(const QString& filePath, QWidget* parent = nullptr);
};