#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QGraphicsScene>
#include <QMenu>

class WorkSheet : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit WorkSheet(QMenu *menuCreate, QObject *parent = nullptr);
};

#endif // WORKSHEET_H