#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QFileDialog>

#include "os.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    QWidget w;

    w.show();

    if(!OS::isInitialized()) {
        OS::initialize();
    }

    return app.exec();
}
