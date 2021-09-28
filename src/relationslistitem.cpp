#include <QSizePolicy>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "relationslistitem.h"
#include "clicklabel.h"
#include "treeobject.h"
#include "relation.h"
#include "partnershipinfolistitem.h"
#include "data.h"


RelationsListItem::RelationsListItem(TreeObject *person, TreeObject *referenced_person, RelationsEditor::Relationship relation_type, bool lock_status)
    : enable_form_editing(!lock_status), relation_type(relation_type), current_owner(person)
{
    vlayout = new QVBoxLayout();
    //vlayout->setSizeConstraint(QLayout::SetMaximumSize);
    vlayout->setContentsMargins(2, 2, 2, 2);

    relation_layout = new QHBoxLayout();
    relation_layout->setContentsMargins(0, 0, 0, 0);

    name_label = new ClickLabel(person, referenced_person, relation_type, true, ClickLabel::Type::Content, this);
    if (relation_type == RelationsEditor::Relationship::Partner)
        name_label->setText(QString(QChar(0x2BC8)) + " " + referenced_person->getName());
    else
        name_label->setText(referenced_person->getName());
    relation_layout->addWidget(name_label);

    delete_icon = new ClickLabel(person, referenced_person, relation_type, !lock_status, ClickLabel::Type::Delete, this);
    delete_icon->setText("x");
    delete_icon->setFixedWidth(20);
    relation_layout->addWidget(delete_icon, Qt::AlignRight);

    relation_widget = new QWidget();
    relation_widget->setLayout(relation_layout);
    vlayout->addWidget(relation_widget);

    populateItem(person, referenced_person);

    setLayout(vlayout);

    setAutoFillBackground(true);
}


void RelationsListItem::populateItem(TreeObject *person, TreeObject *referenced_person)
{
    relation_info_layout = new QVBoxLayout();
    relation_info_layout->setContentsMargins(0, 0, 0, 0);
    relation_info_layout->setSpacing(0);

    foreach (Relation *partnership, person->partnerships) {
        if (partnership->tree_objects.first() == referenced_person ||
            partnership->tree_objects.last() == referenced_person)
        {

            QList<std::tuple<QString, QString, bool>> input_cfg = partnership->info_card->input_cfg;
            QList<std::tuple<QString, QString, bool>>::iterator iter;
            for (iter = input_cfg.begin(); iter != input_cfg.end(); ++iter)
            {
                QString key = std::get<0>(*iter);

                if (key != "Partner 1" && key != "Partner 2")
                {
                    PartnershipInfoListItem *item = new PartnershipInfoListItem(key,
                                                                        enable_form_editing,
                                                                        partnership->info_card);
                    relation_info_layout->addWidget(item);
                }
            }
        }
    }

    relation_info_widget = new QWidget();
    relation_info_widget->setLayout(relation_info_layout);
    vlayout->addWidget(relation_info_widget);

    relation_info_widget->hide();
}


void RelationsListItem::enable(bool lock_status)
{
    qobject_cast<ClickLabel *>(delete_icon)->enable(!lock_status);

    foreach (PartnershipInfoListItem *item, relation_info_widget->findChildren<PartnershipInfoListItem *>())
        item->enableFormEditing(lock_status);
}


void RelationsListItem::showHidePartnershipInfo()
{
    if (show_content == true)
    {
        show_content = false;
        if (relation_type == RelationsEditor::Relationship::Partner)
            name_label->setText(name_label->text().replace(0, 1, QChar(0x2BC6)));
        relation_info_widget->show();
    }
    else
    {
        show_content = true;
        if (relation_type == RelationsEditor::Relationship::Partner)
            name_label->setText(name_label->text().replace(0, 1, QChar(0x2BC8)));
        relation_info_widget->hide();
    }
}
