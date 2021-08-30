#ifndef PRINTSHEETDIALOG_H
#define PRINTSHEETDIALOG_H

#include <QtPrintSupport/QPrintDialog>
#include <QGraphicsView>

class PrintSheetDialog : public QPrintDialog
{
    Q_OBJECT

public:
    explicit PrintSheetDialog(QPrinter&);
    void print(QGraphicsView*);
};

#endif // PRINTSHEETDIALOG_H
