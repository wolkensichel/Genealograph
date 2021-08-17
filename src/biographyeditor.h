#ifndef BIOGRAPHYEDITOR_H
#define BIOGRAPHYEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>


class TreeObject;


class BiographyEditor : public QWidget
{
    Q_OBJECT

public:
    BiographyEditor();
    void update(TreeObject* treecard);
    void clear();

private:
    void createBio();
    void populateGroupBox(QLayout*, TreeObject*);
    void cleanGroupBox(QLayout*);

    QVBoxLayout *widget_layout;
    QScrollArea *area;
};

#endif // BIOGRAPHYEDITOR_H
