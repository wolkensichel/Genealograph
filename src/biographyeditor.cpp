#include <QCheckBox>
#include <QLineEdit>
#include <QSizePolicy>

#include "biographyeditor.h"
#include "biographylistitem.h"


BiographyEditor::BiographyEditor()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setContentsMargins(0, 0, 0, 0);

    QWidget *enable_edit = new QWidget;
    enable_edit->setFixedHeight(20);
    QLabel *label_enable_edit = new QLabel(tr("Lock Biography"));
    QCheckBox *checkbox_enable_edit = new QCheckBox;

    hlayout->addStretch();
    hlayout->addWidget(label_enable_edit);
    hlayout->addWidget(checkbox_enable_edit);
    hlayout->setAlignment(label_enable_edit, Qt::AlignRight);
    hlayout->setAlignment(checkbox_enable_edit, Qt::AlignRight);
    enable_edit->setLayout(hlayout);

    createBio();

    layout->addWidget(enable_edit);
    layout->addWidget(area);
    setLayout(layout);
}


void BiographyEditor::createBio()
{
    widget_layout = new QVBoxLayout;
    widget_layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    widget_layout->setContentsMargins(0, 0, 0, 0);

    QWidget *widget = new QWidget;
    widget->setLayout(widget_layout);

    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);
}


void BiographyEditor::populateGroupBox(QLayout *layout, person bio)
{
    BiographyListItem *label = new BiographyListItem(bio.first_name, QString("First Name:"));
    layout->addWidget(label);

    //ListLabel *label2 = new ListLabel(bio.last_name);
    //layout->addWidget(label2);
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
}


void BiographyEditor::update(person bio)
{
    populateGroupBox(widget_layout, bio);
}
