#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QGraphicsScene>
#include <QMenu>

#include "data.h"

class WorkSheet : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode {AddCard, MoveCard};
    explicit WorkSheet(QMenu *menuCreate, QObject *parent = nullptr);
    void setMode(Mode mode);
    void createTreeCard(person);

private:
    Mode current_mode;
    QGraphicsLineItem *hline;
    QGraphicsLineItem *vline1;
    QGraphicsLineItem *vline2;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

};

#endif // WORKSHEET_H
