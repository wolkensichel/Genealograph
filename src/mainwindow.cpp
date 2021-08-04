#include <QtWidgets>
#include <iostream>

#include "mainwindow.h"
#include "addpersondialog.h"
#include "addpartnershipdialog.h"
#include "worksheet.h"


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
}


void MainWindow::createMenu()
{
    //QMenu *menuFile = menuBar()->addMenu(tr("&File"));

    QMenu *menuCreate = menuBar()->addMenu(tr("&Create"));
    menuCreate->addAction(actionAddPerson);
    menuCreate->addAction(actionAddPartnership);
}


void MainWindow::createWorkSheet()
{
    worksheet = new WorkSheet(menuCreate, this);
    worksheet->setSceneRect(QRectF(0,0,500,500));
    view = new QGraphicsView(worksheet);
    view->setFrameStyle(0); // removes 2px boundary around worksheet scene
    //view->setRenderHints(QPainter::Antialiasing);

    setCentralWidget(view);

    /*QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);*/
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
