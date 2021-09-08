#include <QCheckBox>
#include <QLineEdit>
#include <QSizePolicy>

#include "biographyeditor.h"
#include "biographylistitem.h"
#include "treeobject.h"


BiographyEditor::BiographyEditor()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QWidget *placeholder_mode = new QWidget;
    placeholder_mode->setFixedHeight(20);
    QLabel *label_placeholder_mode = new QLabel(tr("Placeholder"));
    checkbox_placeholder_mode = new QCheckBox;
    checkbox_placeholder_mode->setChecked(false);
    checkbox_placeholder_mode->setEnabled(false);
    connect(checkbox_placeholder_mode, SIGNAL(clicked(bool)), this, SLOT(changePlaceholderStatus(bool)));

    QHBoxLayout *hlayout_placeholder = new QHBoxLayout;
    hlayout_placeholder->setContentsMargins(0, 0, 0, 0);
    hlayout_placeholder->addStretch();
    hlayout_placeholder->addWidget(label_placeholder_mode);
    hlayout_placeholder->addWidget(checkbox_placeholder_mode);
    hlayout_placeholder->setAlignment(label_placeholder_mode, Qt::AlignRight);
    hlayout_placeholder->setAlignment(checkbox_enable_edit, Qt::AlignRight);
    placeholder_mode->setLayout(hlayout_placeholder);

    QWidget *enable_edit = new QWidget;
    enable_edit->setFixedHeight(20);
    QLabel *label_enable_edit = new QLabel(tr("Lock Biography"));
    checkbox_enable_edit = new QCheckBox;
    checkbox_enable_edit->setChecked(false);
    checkbox_enable_edit->setEnabled(false);
    connect(checkbox_enable_edit, SIGNAL(clicked(bool)), this, SLOT(changeLockStatus(bool)));

    QHBoxLayout *hlayout_edit = new QHBoxLayout;
    hlayout_edit->setContentsMargins(0, 0, 0, 0);
    hlayout_edit->addStretch();
    hlayout_edit->addWidget(label_enable_edit);
    hlayout_edit->addWidget(checkbox_enable_edit);
    hlayout_edit->setAlignment(label_enable_edit, Qt::AlignRight);
    hlayout_edit->setAlignment(checkbox_enable_edit, Qt::AlignRight);
    enable_edit->setLayout(hlayout_edit);

    createBio();

    layout->addWidget(placeholder_mode);
    layout->addWidget(enable_edit);
    layout->addWidget(area);
    setLayout(layout);
}


void BiographyEditor::createBio()
{
    widget_layout = new QVBoxLayout;
    widget_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    widget_layout->setContentsMargins(0, 0, 0, 0);

    widget = new QWidget;
    widget->setLayout(widget_layout);

    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);
}


void BiographyEditor::populateGroupBox(QLayout *layout, person individual)
{
    foreach (QString key, keys) {
        bool show_status = true; //individual.bio[key].show;
        BiographyListItem *label = new BiographyListItem(individual.bio[key], key,
                                                         checkbox_enable_edit->isChecked(), show_status,
                                                         checkbox_placeholder_mode->isChecked(), current_owner);
        layout->addWidget(label);
    }
}


void BiographyEditor::cleanGroupBox(QLayout* layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
}


void BiographyEditor::clear()
{
    cleanGroupBox(widget_layout);
    checkbox_enable_edit->setEnabled(false);
    checkbox_enable_edit->setChecked(false);
    checkbox_placeholder_mode->setEnabled(false);
    checkbox_placeholder_mode->setChecked(false);
}


void BiographyEditor::update(TreeObject* treecard, person individual)
{
    current_owner = treecard;
    checkbox_enable_edit->setEnabled(true);
    checkbox_enable_edit->setChecked(individual.biography_dock_lock);
    checkbox_placeholder_mode->setEnabled(true);
    checkbox_placeholder_mode->setChecked(individual.placeholder);

    populateGroupBox(widget_layout, individual);
}


void BiographyEditor::changeLockStatus(bool status)
{
    foreach (BiographyListItem *item, widget->findChildren<BiographyListItem *>())
        item->enableTextEditing(status);

    current_owner->updateBiographyLockStatus(status);
}


void BiographyEditor::changePlaceholderStatus(bool status)
{
    foreach (BiographyListItem *item, widget->findChildren<BiographyListItem *>())
        item->enableEditing(status);

    current_owner->updateBiographyPlaceholderStatus(status);
}
