#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>

#include "relationseditor.h"

RelationsEditor::RelationsEditor()
{
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QLabel *label_enable_edit = new QLabel(tr("Lock Relations"));
    QCheckBox *checkbox_enable_edit = new QCheckBox;

    groupbox_parents = new QGroupBox(tr("Parents:"));
    createGroupBox(groupbox_parents);
    groupbox_partners = new QGroupBox(tr("Partners:"));
    createGroupBox(groupbox_partners);
    groupbox_children = new QGroupBox(tr("Children:"));
    createGroupBox(groupbox_children);

    layout->addWidget(label_enable_edit, 0, 0, 1, 9, Qt::AlignRight);
    layout->addWidget(checkbox_enable_edit, 0, 9, Qt::AlignRight);
    layout->addWidget(groupbox_parents, 1, 0, 2, 10, Qt::AlignTop);
    layout->addWidget(groupbox_partners, 3, 0, 2, 10, Qt::AlignTop);
    layout->addWidget(groupbox_children, 5, 0, 10, 10, Qt::AlignTop);
    setLayout(layout);

}


void RelationsEditor::createGroupBox(QGroupBox *box)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(2, 2, 2, 2);
    box->setLayout(layout);

    QLabel *editlabel_parents[2];
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);

    for (int i = 0; i < 2; ++i) {
        editlabel_parents[i] = new QLabel(tr("Person %1").arg(i + 1));
        editlabel_parents[i]->setAutoFillBackground(true);
        editlabel_parents[i]->setPalette(palette);
        layout->addWidget(editlabel_parents[i]);
    }
}