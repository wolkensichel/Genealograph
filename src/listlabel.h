#ifndef LISTLABEL_H
#define LISTLABEL_H

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>


class ListLabel : public QWidget// : public QLabel
{
public:
    ListLabel(QString&, QString);

private:
    QHBoxLayout *layout;
    QLabel *label;
    QLineEdit *form;
    QCheckBox *checkbox;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // LISTLABEL_H
