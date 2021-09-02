#ifndef RELATIONSLISTITEM_H
#define RELATIONSLISTITEM_H

#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>

#include "relationseditor.h"


class TreeObject;


class RelationsListItem : public QWidget
{
    Q_OBJECT

public:
    RelationsListItem(TreeObject*, TreeObject*, RelationsEditor::Relationship, bool);
    void enableRemover(bool);

private:
    QHBoxLayout *layout;
    QLabel *label;
    QLabel *remover;
};

#endif // RELATIONSLISTITEM_H
