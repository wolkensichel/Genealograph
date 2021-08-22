#include <QtWidgets>
#include <QtPrintSupport/QPrinter>
//#include <QtPrintSupport/QtPrintSupport>
//#include <QtPrintSupport/QPrintDialog>

#include "mainwindow.h"
#include "iohandler.h"
#include "setupsheetdialog.h"
#include "addpersondialog.h"
#include "addpartnershipdialog.h"
#include "adddescentdialog.h"
#include "printsheetdialog.h"
#include "worksheet.h"
#include "biographyeditor.h"
#include "relationseditor.h"
#include "data.h"


MainWindow::MainWindow(QWidget *parent)
{
    createActions();
    createMenu();
    createDockWidgets();
    createWorkSheet();
    save_file = "";
}


MainWindow::~MainWindow()
{
}


void MainWindow::createActions()
{
    actionNewFile = new QAction(tr("&New"), this);
    actionNewFile->setShortcut(QKeySequence(QKeySequence::New));
    connect(actionNewFile, &QAction::triggered, this, &MainWindow::newFile);
    actionOpenFile = new QAction(tr("&Open ..."), this);
    actionOpenFile->setShortcut(QKeySequence(QKeySequence::Open));
    connect(actionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
    actionSaveFile = new QAction(tr("&Save"), this);
    actionSaveFile->setShortcut(QKeySequence(QKeySequence::Save));
    connect(actionSaveFile, &QAction::triggered, this, &MainWindow::saveFile);
    actionSaveAsFile = new QAction(tr("Save As ..."), this);
    actionSaveAsFile->setShortcut(QKeySequence(QKeySequence::SaveAs));
    connect(actionSaveAsFile, &QAction::triggered, this, &MainWindow::saveAsFile);
    actionPrint = new QAction(tr("&Print"), this);
    actionPrint->setShortcut(QKeySequence(QKeySequence::Print));
    connect(actionPrint, &QAction::triggered, this, &MainWindow::print);

    actionAddPerson = new QAction(tr("Add Person"), this);
    actionAddPerson->setShortcut(QKeySequence(Qt::ALT | Qt::Key_W));
    connect(actionAddPerson, &QAction::triggered, this, &MainWindow::addPerson);
    actionAddPartnership = new QAction(tr("Add Partnership"), this);
    actionAddPartnership->setShortcut(QKeySequence(Qt::ALT | Qt::Key_E));
    connect(actionAddPartnership, &QAction::triggered, this, &MainWindow::addPartnership);
    actionAddDescent = new QAction(tr("Add Descent"), this);
    actionAddDescent->setShortcut(QKeySequence(Qt::ALT | Qt::Key_R));
    connect(actionAddDescent, &QAction::triggered, this, &MainWindow::addDescent);
}


void MainWindow::createMenu()
{
    QMenu *menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionNewFile);
    menuFile->addAction(actionOpenFile);
    menuFile->addAction(actionSaveFile);
    menuFile->addAction(actionSaveAsFile);
    menuFile->addAction(actionPrint);

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


void MainWindow::replaceOldSheetByNewSheet(sheet size)
{
    worksheet->clean();
    worksheet->setSceneRect(QRectF(0, 0, size.width, size.height));
    view->destroyed();
    view = new QGraphicsView(worksheet, scrollarea);
    view->setFixedSize(size.width+2*view->frameWidth(), size.height+2*view->frameWidth());
    scrollarea->setWidget(view);
}


void MainWindow::setupSheet()
{
    SetupSheetDialog worksheetSetup;
    if (worksheetSetup.exec() == QDialog::Accepted)
    {
        sheet size = worksheetSetup.fetchFormInputs();
        replaceOldSheetByNewSheet(size);
    }
}


void MainWindow::newFile()
{
    QMessageBox msg_box;
    msg_box.setText(tr("Save current document"));
    msg_box.setInformativeText(tr("Do you want to save the current document before opening a new one?"));
    msg_box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msg_box.setDefaultButton(QMessageBox::Save);

    switch (msg_box.exec()) {
      case QMessageBox::Save:
          save_file = "";
          saveFile();
          setupSheet();
          break;
      case QMessageBox::Discard:
          save_file = "";
          setupSheet();
          break;
      case QMessageBox::Cancel:
          break;
      default:
          break;
    }
}


void MainWindow::openFile()
{
    IOHandler handler;

    load_data file_data;
    QList<object_data *> *objects = new QList<object_data *>();
    QList<partnership_data *> *partnerships = new QList<partnership_data *>();
    QList<descent_data *> *descents = new QList<descent_data *>();
    file_data.worksheet = {0, 0};
    file_data.objects = *objects;
    file_data.partnerships = *partnerships;
    file_data.descents = *descents;

    if (handler.openFromFile(file_data, save_file))
    {
        replaceOldSheetByNewSheet(file_data.worksheet);
        worksheet->createTreeFromFile(file_data);
    }
}


save_data MainWindow::collectWorksheetData()
{
    save_data worksheet_data;
    worksheet_data.tree_objects = worksheet->getTreeObjectList();
    worksheet_data.partnerships = worksheet->getPartnershipRelationList();
    worksheet_data.descents = worksheet->getDescentRelationList();

    sheet sheet_size;
    sheet_size.width = worksheet->width();
    sheet_size.height = worksheet->height();
    worksheet_data.worksheet = sheet_size;

    return worksheet_data;
}


void MainWindow::saveFile()
{
    QTextStream cout(stdout);
    cout << save_file << "\n";
    if (save_file.isEmpty())
        saveAsFile();
    else
    {
        IOHandler handler;
        save_data worksheet_data = collectWorksheetData();
        handler.saveFile(save_file, worksheet_data);
    }
}


void MainWindow::saveAsFile()
{
    IOHandler handler;
    save_data worksheet_data = collectWorksheetData();
    handler.saveToFile(worksheet_data, save_file);
}


void MainWindow::print()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPrintRange(QPrinter::CurrentPage);

    PrintSheetDialog printDialog(printer);
    printDialog.print(view);
}


void MainWindow::addPerson()
{
    AddPersonDialog addPerson;
    if (addPerson.exec() == QDialog::Accepted)
        worksheet->createTreeCard(addPerson.fetchFormInputs());
}


void MainWindow::addPartnership()
{
    AddPartnershipDialog addPartnership;
    addPartnership.populateDropDownMenus(worksheet->getTreeObjectList());

    if (addPartnership.exec() == QDialog::Accepted)
        worksheet->createPartnershipRelation(addPartnership.fetchFormInputs());
}


void MainWindow::addDescent()
{
    AddDescentDialog addDescent;
    addDescent.populateDropDownMenus(worksheet->getTreeObjectList(), worksheet->getPartnershipRelationList());

    if (addDescent.exec() == QDialog::Accepted)
        worksheet->createDescentRelation(addDescent.fetchFormInputs());
}
