#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QFileDialog>

#include "os.h"
#include "gui.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    if(!OS::isInitialized()) {
        OS::initialize();
    }

    Gui w;
    w.show();

    return app.exec();
}
