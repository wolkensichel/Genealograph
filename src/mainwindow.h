#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "addpersondialog.h"

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

    QAction *actionAddPerson;
    QAction *actionAddPartnership;

    AddPersonDialog *addPersonDialog;

    WorkSheet *worksheet;
    QGraphicsView *view;

    //QMenu *menuFile;
    QMenu *menuCreate;

};


#endif // MainWindow_H
