#include <QCheckBox>
#include <QLineEdit>
#include <QSizePolicy>

#include "biographyeditor.h"
#include "listlabel.h"


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
    widget_layout->setSizeConstraint(QLayout::SetMinAndMaxSize); // necessary to see labels
    widget_layout->setContentsMargins(0, 0, 0, 0);

    QWidget *widget = new QWidget;
    widget->setLayout(widget_layout);

    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);
}


void BiographyEditor::populateGroupBox(QLayout *layout, person bio)
{
    ListLabel *label = new ListLabel(bio.first_name, QString("First Name:"));
    layout->addWidget(label);

    //ListLabel *label2 = new ListLabel(bio.last_name);
    //layout->addWidget(label2);

    QLineEdit *first_name = new QLineEdit;
    first_name->setText(bio.first_name);
    first_name->setDisabled(true);
    first_name->setStyleSheet("background: white; color: #565656; padding: 0 5 0 5");
    //first_name->setFixedHeight(20);
    //layout->addWidget(first_name);
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
    for (int i = 0; i <= 2; i++)
        cleanGroupBox(widget_layout->layout());
}


void BiographyEditor::update(person bio)
{
    populateGroupBox(widget_layout->layout(), bio);
}
