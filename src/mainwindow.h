#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "data.h"


class WorkSheet;
class QGraphicsView;
class RelationsEditor;
class BiographyEditor;
class QGraphicsItem;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDockWidget *dock_biography;
    QDockWidget *dock_relations;
    RelationsEditor *relations_editor;
    BiographyEditor *biography_editor;
    QScrollArea *scrollarea;

private:
    void createActions();
    void createMenu();
    void createDockWidgets();
    void createWorkSheet();

    save_data collectWorksheetData();
    void setupSheet();
    void prepareNewSheet(sheet);
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void print();
    void quit();

    void addPerson();
    void addPartnership();
    void addDescent();

    void resizeSheet();

    void defineDataItems();

    QAction *actionNewFile;
    QAction *actionOpenFile;
    QAction *actionSaveFile;
    QAction *actionSaveAsFile;
    QAction *actionPrint;
    QAction *actionQuit;

    QAction *actionAddPerson;
    QAction *actionAddPartnership;
    QAction *actionAddDescent;

    QAction *actionSheetResize;

    QMenu *menuFile;
    QMenu *menuCreate;
    QMenu *menuWorksheet;

    WorkSheet *worksheet;
    QGraphicsView *view = nullptr;

    QString save_file;

    qreal zoom_in_factor;
    qreal zoom_out_factor;

    QList<std::tuple<QString, QString, bool>> input_cfg_persons;
    QList<std::tuple<QString, QString, bool>> input_cfg_partnerships;

public slots:
    void scrollToItem();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};


#endif // MainWindow_H
