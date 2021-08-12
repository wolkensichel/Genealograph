#ifndef LISTLABEL_H
#define LISTLABEL_H

#include <QLabel>

class ListLabel : public QLabel
{
public:
    ListLabel(QString text);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // LISTLABEL_H