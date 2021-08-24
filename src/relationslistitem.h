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
public:
    RelationsListItem(TreeObject*, TreeObject*, RelationsEditor::Relationship);

private:
    QHBoxLayout *layout;
    QLabel *label;
    QLabel *remover;
};

#endif // RELATIONSLISTITEM_H
