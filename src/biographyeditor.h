#ifndef BIOGRAPHYEDITOR_H
#define BIOGRAPHYEDITOR_H

#include <QWidget>
#include <QGroupBox>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QCheckBox>

#include "data.h"


class TreeObject;


class BiographyEditor : public QWidget
{
    Q_OBJECT

    QList<QString> keys = {"First Name", "Last Name"};

public:
    BiographyEditor();
    void update(TreeObject*, person, QList<std::tuple<QString, QString, bool>>);
    void clear();

private:
    void createBio();
    void populateGroupBox(QLayout*, person, QList<std::tuple<QString, QString, bool>>);
    void cleanGroupBox(QLayout*);

    QWidget *widget;
    QVBoxLayout *widget_layout;
    QScrollArea *area;

    TreeObject *current_owner;
    QCheckBox *checkbox_enable_edit;
    QCheckBox *checkbox_placeholder_mode;

private slots:
    void changeLockStatus(bool);
    void changePlaceholderStatus(bool);
};

#endif // BIOGRAPHYEDITOR_H
