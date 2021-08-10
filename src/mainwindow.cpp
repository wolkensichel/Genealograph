#include <QtWidgets>
#include <iostream>

#include "mainwindow.h"
#include "addpersondialog.h"
#include "addpartnershipdialog.h"
#include "adddescentdialog.h"
#include "worksheet.h"
#include "biographyeditor.h"


MainWindow::MainWindow(QWidget *parent)
{
    createActions();
    createMenu();
    createWorkSheet();
}


MainWindow::~MainWindow()
{
}


void MainWindow::createActions()
{
    actionAddPerson = new QAction(tr("&Add Person"), this);
    connect(actionAddPerson, &QAction::triggered, this, &MainWindow::addPerson);
    actionAddPartnership = new QAction(tr("&Add Partnership"), this);
    connect(actionAddPartnership, &QAction::triggered, this, &MainWindow::addPartnership);
    actionAddDescent = new QAction(tr("&Add Descent"), this);
    connect(actionAddDescent, &QAction::triggered, this, &MainWindow::addDescent);
}


void MainWindow::createMenu()
{
    //QMenu *menuFile = menuBar()->addMenu(tr("&File"));

    QMenu *menuCreate = menuBar()->addMenu(tr("&Create"));
    menuCreate->addAction(actionAddPerson);
    menuCreate->addAction(actionAddPartnership);
    menuCreate->addAction(actionAddDescent);
}


void MainWindow::createWorkSheet()
{
    worksheet = new WorkSheet(menuCreate, this);
    worksheet->setSceneRect(QRectF(0,0,500,500));
    view = new QGraphicsView(worksheet);
    view->setFrameStyle(0); // removes 2px boundary around worksheet scene
    //view->setRenderHints(QPainter::Antialiasing);
    setCentralWidget(view);

    BiographyEditor *editor_biography = new BiographyEditor;

    dock_biography = new QDockWidget("Biography", this);
    dock_biography->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    dock_biography->setWidget(editor_biography);
    addDockWidget(Qt::RightDockWidgetArea, dock_biography);

    dock_biography->raise();
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setDockOptions(ForceTabbedDocks);
}


void MainWindow::addPerson()
{
    AddPersonDialog addPerson;
    if (addPerson.exec() == QDialog::Accepted)
    {
        //worksheet->setMode(WorkSheet::AddCard);
        worksheet->createTreeCard(addPerson.fetchFormInputs());
    }
}


void MainWindow::addPartnership()
{
    AddPartnershipDialog addPartnership;
    addPartnership.populateDropDownMenus(worksheet->getTreeObjectList());

    if (addPartnership.exec() == QDialog::Accepted)
    {
        worksheet->createPartnershipRelation(addPartnership.fetchFormInputs());
    }
}


void MainWindow::addDescent()
{
    AddDescentDialog addDescent;
    addDescent.populateDropDownMenus(worksheet->getTreeObjectList(), worksheet->getPartnershipRelationList());

    if (addDescent.exec() == QDialog::Accepted)
    {
        worksheet->createDescentRelation(addDescent.fetchFormInputs());
    }
}
