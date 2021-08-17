#include <QCheckBox>
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
    widget_layout->setContentsMargins(2, 2, 2, 2);

    QWidget *widget = new QWidget;
    widget->setLayout(widget_layout);

    area = new QScrollArea;
    area->setWidget(widget);
    area->setWidgetResizable(true);

    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);

    QLabel *field = new QLabel("some\ntext");
    field->setContentsMargins(10,4,4,4);
    field->setAutoFillBackground(true);
    field->setPalette(palette);
    field->setFixedHeight(40);
    widget_layout->addWidget(field);

    QLabel *field2 = new QLabel("some text");
    field2->setAutoFillBackground(true);
    field2->setPalette(palette);
    field2->setFixedHeight(40);
    widget_layout->addWidget(field2);

    //QCheckBox *checkbox_field = new QCheckBox;
    //widget_layout->addWidget(checkbox_field, 0, 30, 1, 1, Qt::AlignRight);

    //for (int i = 0; i < 25; ++i) {
        /*fields[i] = new QLabel(tr("Info %1").arg(i + 1));
        fields[i]->setFixedWidth(200);
        fields[i]->setAutoFillBackground(true);
        fields[i]->setPalette(palette);
        checkbox_fields[i] = new QCheckBox;
        widget_layout->addWidget(fields[i], i, 0, 1, 9, Qt::AlignLeft);
        widget_layout->addWidget(checkbox_fields[i], i, 10, 1, 1, Qt::AlignRight);*/
    //}
}


void BiographyEditor::populateGroupBox(QLayout*, TreeObject*)
{

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


void BiographyEditor::update(TreeObject* treecard)
{

}
