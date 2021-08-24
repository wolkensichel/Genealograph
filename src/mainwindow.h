#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "data.h"


class WorkSheet;
class QGraphicsView;
class RelationsEditor;
class BiographyEditor;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QDockWidget *dock_biography;
    QDockWidget *dock_relations;
    RelationsEditor *relations_editor;
    BiographyEditor *biography_editor;
    ~MainWindow();

private:
    void createActions();
    void createMenu();
    void createDockWidgets();
    void createWorkSheet();

    save_data collectWorksheetData();
    void setupSheet();
    void replaceOldSheetByNewSheet(sheet);
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void print();

    void addPerson();
    void addPartnership();
    void addDescent();

    QAction *actionAddPerson;
    QAction *actionAddPartnership;
    QAction *actionAddDescent;

    QAction *actionNewFile;
    QAction *actionOpenFile;
    QAction *actionSaveFile;
    QAction *actionSaveAsFile;
    QAction *actionPrint;

    QScrollArea *scrollarea;
    WorkSheet *worksheet;
    QGraphicsView *view;

    //QMenu *menuFile;
    QMenu *menuCreate;

    QString save_file;
};


#endif // MainWindow_H
