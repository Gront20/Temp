
#pragma once
#include <QMainWindow>
class InputMethod;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(InputMethod* im, QWidget* parent = nullptr);
private:
    InputMethod* im;
};
