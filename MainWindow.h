#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ResolutionConversionSingleton.h"

#include <QMainWindow>
#include <QtQuickWidgets/QQuickWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

private slots:
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    ResolutionConversionSingleton theRCS;
};

#endif // MAINWINDOW_H
