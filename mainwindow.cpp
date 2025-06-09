
#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "inputmethod.h"

MainWindow::MainWindow(InputMethod* im, QWidget* parent)
    : QMainWindow(parent), im(im)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    QString keys = "QWERTYUIOP";

    for (auto ch : keys) {
        QPushButton* btn = new QPushButton(QString(ch), this);
        btn->setFocusPolicy(Qt::NoFocus);
        connect(btn, &QPushButton::clicked, this, [=]() {
            im->sendText(QString(ch));
        });
        layout->addWidget(btn);
    }

    central->setFocusPolicy(Qt::NoFocus);
    central->setAttribute(Qt::WA_ShowWithoutActivating);
    setCentralWidget(central);
    setFocusPolicy(Qt::NoFocus);
    setAttribute(Qt::WA_ShowWithoutActivating);
}
