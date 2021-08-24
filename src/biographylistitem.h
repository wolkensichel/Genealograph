#ifndef BIOGRAPHYLISTITEM_H
#define BIOGRAPHYLISTITEM_H

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>


class BiographyListItem : public QWidget// : public QLabel
{
public:
    BiographyListItem(QString&, QString);

private:
    QHBoxLayout *layout;
    QLabel *label;
    QLineEdit *form;
    QCheckBox *checkbox;
};

#endif // BIOGRAPHYLISTITEM_H
