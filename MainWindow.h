#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UndoSingleton.h"

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
    void setupView();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
