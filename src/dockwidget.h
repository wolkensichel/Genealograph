#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    DockWidget(QString, QWidget*);

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // DOCKWIDGET_H
