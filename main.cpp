
#include <QApplication>
#include "mainwindow.h"
#include "inputmethod.h"

int main(int argc, char* argv[])
{
    wl_display* display = wl_display_connect(nullptr);
    if (!display) {
        qCritical("Can't connect to Wayland display");
        return 1;
    }

    InputMethod im(display);

    QApplication a(argc, argv);
    MainWindow w(&im);
    w.show();

    return a.exec();
}
