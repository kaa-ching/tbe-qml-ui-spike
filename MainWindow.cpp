#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Popup.h"

#include "AbstractObject.h"
#include "ResolutionConversionSingleton.h"
#include "ViewItem.h"
#include "World.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qmlRegisterType<ViewItem>("TBEView", 1, 0, "ViewItem");
    ui->quickWidget->setSource(QStringLiteral("qrc:/main.qml"));

    // load our objects into the view
    World myWorld(4,6);
    ResolutionConversionSingleton myRCS(nullptr, this);

    AbstractObject myObject1("BowlingPin", Position(2, 3, 0.2), 0.12, 0.34);
    myWorld.addObject(&myObject1);
    AbstractObject myObject2("used_wood_bar", Position(2, 2.5, 0.0), 1.0, 0.1);
    myWorld.addObject(&myObject2);
    AbstractObject myObject3("used_wood_bar", Position(1, 2.0, 0.0), 2.0, 0.5);
    myWorld.addObject(&myObject3);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    //: translators: <b> and <br> are statements for bold and newline, respectively
    Popup::Info(tr("<b>The Butterfly Effect</b><br>version: xxx<br>git commit: xxx<br>"
                   "An open source game that uses realistic physics"
                   " simulations to combine lots of simple mechanical elements"
                   " to achieve a simple goal in the most complex way possible.<br><br>"
                   "(C) 2009,2010,2011,2012,2013,2015,2016 Klaas van Gend and many others<br><br>"
                   "Code licensed under GPL version 2 - <i>only</i>.<br>Levels and graphics may have different open/free licenses.<br><br>"
                   "See <a href=\"http://xxx/\">http://xxx/</a> for more info on this project."), this);
}
