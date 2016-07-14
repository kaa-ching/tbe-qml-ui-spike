#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Popup.h"

#include "AbstractObject.h"
#include "ResizingQuickWidget.h"
#include "ViewItem.h"
#include "ViewItemFactory.h"
#include "World.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // load our objects into the view
    World* myWorldPtr = new World(5,2);
    ResolutionConversionSingleton::me()->adjustToWorldSize(*myWorldPtr);
    qmlRegisterType<ViewItem>("TBEView", 1, 0, "ViewItem");
    ui->quickWidget->setSource(QStringLiteral("qrc:/main.qml"));

    ViewItemFactory* myFactoryPtr = new ViewItemFactory(ui->quickWidget);

    AbstractObject* myObject1 = new AbstractObject("BowlingPin", Position(0.60, 0.20, -PI/2.), 0.20, 0.60);
    myWorldPtr->addObject(myObject1);
    ViewItem* myVIPtr1 = myFactoryPtr->createViewItem(myObject1);

    AbstractObject* myObject2 = new AbstractObject("used_wood_bar", Position(2, 1.5, 0.0), 1.0, 0.1);
    myWorldPtr->addObject(myObject2);
    ViewItem* myVIPtr2 = myFactoryPtr->createViewItem(myObject2);

    AbstractObject* myObject3 = new AbstractObject("used_wood_bar", Position(3.9, 1.0, 0.0), 2.0, 0.5);
    myWorldPtr->addObject(myObject3);
    ViewItem* myVIPtr3 = myFactoryPtr->createViewItem(myObject3);
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
