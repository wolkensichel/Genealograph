#include "listlabel.h"

#include <QTextStream>
#include <iostream>

ListLabel::ListLabel(QString text)
{
    setText(text);
}


void ListLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    QTextStream cout(stdout);
    cout << "this is some text\n";

}