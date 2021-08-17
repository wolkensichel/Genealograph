#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>


class WorkSheet;
class QGraphicsView;
class RelationsEditor;
class BiographyEditor;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    void createMenu();
    void createDockWidgets();
    void createWorkSheet();

    void saveFile();
    void saveAsFile();
    void openFile();

    void addPerson();
    void addPartnership();
    void addDescent();

    QAction *actionAddPerson;
    QAction *actionAddPartnership;
    QAction *actionAddDescent;
    QAction *actionSaveAsFile;
    QAction *actionOpenFile;

    QScrollArea *scrollarea;
    WorkSheet *worksheet;
    QGraphicsView *view;
    QDockWidget *dock_biography;
    QDockWidget *dock_relations;
    RelationsEditor *relations_editor;
    BiographyEditor *biography_editor;

    //QMenu *menuFile;
    QMenu *menuCreate;

};


#endif // MainWindow_H
