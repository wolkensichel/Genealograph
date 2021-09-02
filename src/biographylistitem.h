#ifndef BIOGRAPHYLISTITEM_H
#define BIOGRAPHYLISTITEM_H

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>


class BiographyListItem : public QWidget// : public QLabel
{
    Q_OBJECT

public:
    BiographyListItem(QString&, QString, bool);
    void enableEditing(bool);

private:
    void adjustStyle();
    bool enabled;
    QHBoxLayout *layout;
    QLabel *label;
    QLineEdit *form;
    QCheckBox *checkbox;
};

#endif // BIOGRAPHYLISTITEM_H
