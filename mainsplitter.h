#ifndef MAINSPLITTER_H
#define MAINSPLITTER_H
#endif

#include <QSplitter>
#include <QSettings>

class MainSplitter : public QSplitter {
    Q_OBJECT

public:
    explicit MainSplitter(QWidget *parent = nullptr);
    void setWidths();
};