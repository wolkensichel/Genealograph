#include <QtPrintSupport/QPrinter>

#include "printsheetdialog.h"


PrintSheetDialog::PrintSheetDialog(QPrinter &printer) : QPrintDialog(&printer)
{
    setOption(QAbstractPrintDialog::PrintCollateCopies, false);
    setOption(QAbstractPrintDialog::PrintSelection, false);
    setOption(QAbstractPrintDialog::PrintPageRange, false);
    setOption(QAbstractPrintDialog::PrintCurrentPage, false);
}


void PrintSheetDialog::print(QGraphicsView *view)
{
    if(exec() == QDialog::Accepted) {
        QPainter p;
        p.begin(printer());
        view->render(&p);
        p.end();
    }
}
