#include <QtWidgets>
#include <iostream>

#include "mainwindow.h"
#include "iohandler.h"
#include "addpersondialog.h"
#include "addpartnershipdialog.h"
#include "adddescentdialog.h"
#include "worksheet.h"
#include "biographyeditor.h"
#include "relationseditor.h"


MainWindow::MainWindow(QWidget *parent)
{
    createActions();
    createMenu();
    createDockWidgets();
    createWorkSheet();
}


MainWindow::~MainWindow()
{
}


void MainWindow::createActions()
{
    actionOpenFile = new QAction(tr("&Open ..."), this);
    connect(actionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
    actionSaveAsFile = new QAction(tr("S&ave As ..."), this);
    connect(actionSaveAsFile, &QAction::triggered, this, &MainWindow::saveAsFile);

    actionAddPerson = new QAction(tr("Add &Person"), this);
    connect(actionAddPerson, &QAction::triggered, this, &MainWindow::addPerson);
    actionAddPartnership = new QAction(tr("Add Pa&rtnership"), this);
    connect(actionAddPartnership, &QAction::triggered, this, &MainWindow::addPartnership);
    actionAddDescent = new QAction(tr("Add &Descent"), this);
    connect(actionAddDescent, &QAction::triggered, this, &MainWindow::addDescent);
}


void MainWindow::createMenu()
{
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionOpenFile);
    menuFile->addAction(actionSaveAsFile);

    QMenu *menuCreate = menuBar()->addMenu(tr("&Create"));
    menuCreate->addAction(actionAddPerson);
    menuCreate->addAction(actionAddPartnership);
    menuCreate->addAction(actionAddDescent);
}


void MainWindow::createDockWidgets()
{
    dock_biography = new QDockWidget("Biography", this);
    dock_biography->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock_biography);

    biography_editor = new BiographyEditor;
    dock_biography->setWidget(biography_editor);

    dock_relations = new QDockWidget("Relations", this);
    dock_relations->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock_relations);

    relations_editor = new RelationsEditor(dock_relations);
    dock_relations->setWidget(relations_editor);

    tabifyDockWidget(dock_biography, dock_relations);
    dock_biography->raise();
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::North);
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);
    setDockOptions(ForceTabbedDocks);
}


void MainWindow::createWorkSheet()
{
    scrollarea = new QScrollArea;
    scrollarea->setAlignment(Qt::AlignCenter);
    scrollarea->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    //scrollarea->setBackgroundRole(QPalette::Midlight);
    //scrollarea->setWidgetResizable(true);

    worksheet = new WorkSheet(menuCreate, biography_editor, relations_editor, scrollarea);
    worksheet->setSceneRect(QRectF(0,0,800,600));

    view = new QGraphicsView(worksheet, scrollarea);
    view->setStyleSheet("border: 1px solid lightgrey");
    //view->setRenderHints(QPainter::Antialiasing);

    scrollarea->setWidget(view);
    setCentralWidget(scrollarea);
}


void MainWindow::openFile()
{
    IOHandler handler;
    load_data* input_data = handler.openFromFile();

    if (input_data->worksheet.width != 0)
    {
        worksheet->clean();

        worksheet->setSceneRect(QRectF(0,0,input_data->worksheet.width,input_data->worksheet.height));
        view->destroyed();
        view = new QGraphicsView(worksheet, scrollarea);
        scrollarea->setWidget(view);

        QList<object_data *>::iterator it;
        for (it = input_data->objects.begin(); it != input_data->objects.end(); ++it)
            worksheet->createTreeCard(it.operator*()->bio, it.operator*()->id, it.operator*()->pos);
    }
}


void MainWindow::saveAsFile()
{
    IOHandler handler;
    // fetch data to save and put in as argument to saveToFile()
    QList<TreeObject *> list = worksheet->getTreeObjectList();
    //QList<TreeObject *> list = worksheet->getPartnershipRelationList();
    //QList<TreeObject *> list = worksheet->getDescentRelationList();

    if (!list.isEmpty())
    {
        //TreeObject *first = *(list.begin());
        //QTextStream cout(stdout);
        //cout << first->pos().x() << ", " << first->pos().y() << "\n";
    }
    sheet sheet_size;
    sheet_size.width = worksheet->width();
    sheet_size.height = worksheet->height();
    handler.saveToFile(sheet_size, list);
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
