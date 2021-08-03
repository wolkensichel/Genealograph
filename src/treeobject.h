#ifndef TREEOBJECT_H
#define TREEOBJECT_H

#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"

class TreeObject : public QGraphicsRectItem
{
public:
    TreeObject(person);
    QString getName();

private:
    void fillFields(person);

    QGraphicsProxyWidget* proxy;
    QVBoxLayout *layout;

    QLabel* first_name;
    QLabel* last_name;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TREEOBJECT_H
