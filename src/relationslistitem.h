#ifndef RELATIONSLISTITEM_H
#define RELATIONSLISTITEM_H

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

#include "relationseditor.h"


class TreeObject;


class RelationsListItem : public QWidget
{
    Q_OBJECT

public:
    RelationsListItem(TreeObject*, TreeObject*, RelationsEditor::Relationship, bool);
    void enable(bool);
    void showHidePartnershipInfo();

private:
    void populateItem(TreeObject*, TreeObject*);

    bool enable_form_editing;
    RelationsEditor::Relationship relation_type;
    TreeObject *current_owner;

    bool show_content = true;
    QVBoxLayout *vlayout;
    QHBoxLayout *relation_layout;
    QVBoxLayout *relation_info_layout;
    QWidget *relation_widget;
    QWidget *relation_info_widget;
    QWidget *content_widget;
    QLabel *name_label;
    QLabel *delete_icon;

    QLabel *newlabel;
};

#endif // RELATIONSLISTITEM_H
