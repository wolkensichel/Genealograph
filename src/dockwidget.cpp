#include <QCloseEvent>

#include "dockwidget.h"


DockWidget::DockWidget(QString title, QWidget *parent = nullptr)
    : QDockWidget(title, parent)
{
    setWindowTitle(title);
}


void DockWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    emit closed();
}
