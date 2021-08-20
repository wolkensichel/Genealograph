#ifndef BIOGRAPHYEDITOR_H
#define BIOGRAPHYEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>

#include "data.h"


class TreeObject;


class BiographyEditor : public QWidget
{
    Q_OBJECT

public:
    BiographyEditor();
    void update(person);
    void clear();

private:
    void createBio();
    void populateGroupBox(QLayout*, person);
    void cleanGroupBox(QLayout*);

    QVBoxLayout *widget_layout;
    QScrollArea *area;
};

#endif // BIOGRAPHYEDITOR_H
