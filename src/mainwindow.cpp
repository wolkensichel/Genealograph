#include <QtWidgets>
#include <iostream>

#include "mainwindow.h"
#include "addpersondialog.h"
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
}


void MainWindow::createMenu()
{
    //QMenu *menuFile = menuBar()->addMenu(tr("&File"));

    QMenu *menuCreate = menuBar()->addMenu(tr("&Create"));
    menuCreate->addAction(actionAddPerson);

}


void MainWindow::createWorkSheet()
{
    worksheet = new WorkSheet(menuCreate, this);
    worksheet->setSceneRect(QRectF(0,0,1000,1000));
    view = new QGraphicsView(worksheet);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
}


void MainWindow::addPerson()
{
    AddPersonDialog addPerson;
    if (addPerson.exec() == QDialog::Accepted)
    {
        person new_person;
        new_person = addPerson.getData();

        drawPersonCard(new_person);

    }
}


void MainWindow::drawPersonCard(person new_person)
{

}
