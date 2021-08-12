#ifndef BIOGRAPHYEDITOR_H
#define BIOGRAPHYEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>


class BiographyEditor : public QWidget
{
    Q_OBJECT

public:
    BiographyEditor();

private:
    void createBio();

    QScrollArea *area;
    QWidget *widget;
    QGridLayout *layout;
    QVBoxLayout *widget_layout;
};

#endif // BIOGRAPHYEDITOR_H
