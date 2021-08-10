#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class WorkSheet;
class QGraphicsView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    void createMenu();
    void createWorkSheet();

    void addPerson();
    void addPartnership();
    void addDescent();

    QAction *actionAddPerson;
    QAction *actionAddPartnership;
    QAction *actionAddDescent;

    WorkSheet *worksheet;
    QGraphicsView *view;
    QDockWidget *dock_biography;
    QDockWidget *dock_relations;

    //QMenu *menuFile;
    QMenu *menuCreate;

};


#endif // MainWindow_H
