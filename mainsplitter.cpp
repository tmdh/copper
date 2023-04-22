#include <QGuiApplication>
#include <QScreen>

#include "mainsplitter.h"

MainSplitter::MainSplitter(QWidget* parent) {}

void MainSplitter::setWidths() {
    int largeWidth = QGuiApplication::primaryScreen()->virtualSize().width();
    setSizes(QList<int>({400, largeWidth}));
}
