#include <QtWidgets>
#include <QPrinter>

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


MainWindow::MainWindow(QWidget *parent)
{
    defineDataItems();
    createActions();
    createMenu();
    createDockWidgets();
    createWorkSheet();
    save_file = "";
    //zoom_in_factor = 1.25;
    //zoom_out_factor = 0.8;
}


void MainWindow::defineDataItems()
{
    input_cfg_persons = {
        {"First name", "QLineEdit", true},
        {"Last name", "QLineEdit", true},
        {"Birth name", "QLineEdit", false},
        {"Sex", "QComboBox", false},
        {"Date of birth", "QLineEdit", true},
        {"Place of birth", "QLineEdit", true},
        {"Date of death", "QLineEdit", false},
        {"Place of death", "QLineEdit", false}
    };

    input_cfg_partnerships = {
        {"Type", "QComboBox", true},
        {"Partner 1", "QComboBox", true},
        {"Partner 2", "QComboBox", true},
        {"Date formed", "QLineEdit", true},
        {"Formed in", "QLineEdit", false},
        {"Date ended", "QLineEdit", true}
    };

    input_cfg_descents = {
        {"Parents", "QComboBox", true},
        {"Child", "QComboBox", true}
    };
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
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcut(QKeySequence(QKeySequence::Quit));
    connect(actionQuit, &QAction::triggered, this, &MainWindow::quit);

    actionAddPerson = new QAction(tr("Add Person"), this);
    actionAddPerson->setShortcut(QKeySequence(Qt::ALT | Qt::Key_W));
    connect(actionAddPerson, &QAction::triggered, this, &MainWindow::addPerson);
    actionAddPartnership = new QAction(tr("Add Partnership"), this);
    actionAddPartnership->setShortcut(QKeySequence(Qt::ALT | Qt::Key_E));
    connect(actionAddPartnership, &QAction::triggered, this, &MainWindow::addPartnership);
    actionAddDescent = new QAction(tr("Add Descent"), this);
    actionAddDescent->setShortcut(QKeySequence(Qt::ALT | Qt::Key_R));
    connect(actionAddDescent, &QAction::triggered, this, &MainWindow::addDescent);

    actionSheetResize = new QAction(tr("Resize"), this);
    actionSheetResize->setShortcut(QKeySequence(Qt::ALT | Qt::Key_M));
    connect(actionSheetResize, &QAction::triggered, this, &MainWindow::resizeSheet);
}


void MainWindow::createMenu()
{
    menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionNewFile);
    menuFile->addAction(actionOpenFile);
    menuFile->addAction(actionSaveFile);
    menuFile->addAction(actionSaveAsFile);
    menuFile->addAction(actionPrint);
    menuFile->addAction(actionQuit);

    menuCreate = menuBar()->addMenu(tr("&Create"));
    menuCreate->addAction(actionAddPerson);
    menuCreate->addAction(actionAddPartnership);
    menuCreate->addAction(actionAddDescent);

    menuWorksheet = menuBar()->addMenu(tr("&Worksheet"));
    menuWorksheet->addAction(actionSheetResize);
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

    relations_editor = new RelationsEditor;
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
    setCentralWidget(scrollarea);

    worksheet = new WorkSheet(menuCreate, this);
    connect(worksheet, SIGNAL(selectionChanged()), this, SLOT(scrollToItem()));
    sheet size = {800, 600};
    prepareNewSheet(size);
}


void MainWindow::prepareNewSheet(sheet size)
{
    worksheet->clean();
    worksheet->setSceneRect(QRectF(0, 0, size.width, size.height));

    if (view != nullptr)
        view->destroyed();
    view = new QGraphicsView(worksheet, scrollarea);
    view->setStyleSheet("border: 1px solid lightgrey");
    view->resize(worksheet->width()+2*view->frameWidth(), worksheet->height()+2*view->frameWidth());
    //view->setRenderHints(QPainter::Antialiasing);
    scrollarea->setWidget(view);

    biography_editor->clear();
    relations_editor->clear();
}


void MainWindow::setupSheet()
{
    SetupSheetDialog worksheetSetup(worksheet, "Setup Worksheet");
    if (worksheetSetup.exec() == QDialog::Accepted)
    {
        sheet size = worksheetSetup.fetchFormInputs();
        prepareNewSheet(size);
    }
}


void MainWindow::newFile()
{
    QMessageBox msg_box;
    msg_box.setText(tr("Do you want to save the current document before opening a new one?"));
    msg_box.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msg_box.setDefaultButton(QMessageBox::Save);

    switch (msg_box.exec()) {
      case QMessageBox::Save:
          save_file = "";
          saveFile();
      case QMessageBox::Discard:
          setupSheet();
          break;
      case QMessageBox::Cancel:
          break;
    }
}


void MainWindow::openFile()
{
    IOHandler handler;

    load_data file_data;
    QList<person *> *persons = new QList<person *>();
    QList<partnership *> *partnerships = new QList<partnership *>();
    QList<descent *> *descents = new QList<descent *>();
    file_data.worksheet = {0, 0};
    file_data.persons = *persons;
    file_data.partnerships = *partnerships;
    file_data.descents = *descents;

    if (handler.openFromFile(file_data, save_file))
    {
        prepareNewSheet(file_data.worksheet);
        QList<QList<std::tuple<QString, QString, bool>>> input_cfg =
            {input_cfg_persons, input_cfg_partnerships, input_cfg_descents};
        worksheet->createTreeFromFile(file_data, input_cfg);
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


void MainWindow::quit()
{
    QMessageBox msg_box;
    msg_box.setText(tr("Do you want to save the current document before you quit?"));
    msg_box.setStandardButtons(QMessageBox::Save | QMessageBox::Close);
    QAbstractButton *close_button = msg_box.button(QMessageBox::Close);
    close_button->setText("Quit");
    msg_box.setDefaultButton(QMessageBox::Save);

    switch (msg_box.exec()) {
      case QMessageBox::Save:
          save_file = "";
          saveFile();
      case QMessageBox::Close:
          QCoreApplication::quit();
          break;
    }
}


void MainWindow::addPerson()
{
    AddPersonDialog addPerson(input_cfg_persons);
    if (addPerson.exec() == QDialog::Accepted)
        worksheet->createTreeCard(addPerson.fetchFormInputs(), input_cfg_persons);
}


void MainWindow::addPartnership()
{
    AddPartnershipDialog addPartnership(input_cfg_partnerships, worksheet->getTreeObjectList());
    if (addPartnership.exec() == QDialog::Accepted)
        worksheet->createPartnershipRelation(addPartnership.fetchFormInputs(), input_cfg_partnerships);
}


void MainWindow::addDescent()
{
    AddDescentDialog addDescent(input_cfg_descents, worksheet->getTreeObjectList(),
                                worksheet->getPartnershipRelationList());
    if (addDescent.exec() == QDialog::Accepted)
        worksheet->createDescentRelation(addDescent.fetchFormInputs(), input_cfg_descents);
}


void MainWindow::resizeSheet()
{
    SetupSheetDialog worksheetResize(worksheet, "Resize Worksheet");
    if (worksheetResize.exec() == QDialog::Accepted)
    {
        sheet size = worksheetResize.fetchFormInputs();
        worksheet->setSceneRect(0, 0, size.width, size.height);
        view->resize(worksheet->width()+2*view->frameWidth(), worksheet->height()+2*view->frameWidth());
    }
}


void MainWindow::scrollToItem()
{
    if (!worksheet->selectedItems().isEmpty()) {
        QGraphicsItem *item = worksheet->selectedItems().first();
        scrollarea->ensureVisible(item->pos().x(), item->pos().y(),
                                  item->boundingRect().width(), item->boundingRect().height());
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    event->ignore();
    // arrow-keys navigation in scrollarea, zooming
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    quit();
}
