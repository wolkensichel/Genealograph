#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSizePolicy>

#include "biographyeditor.h"
#include "listlabel.h"


BiographyEditor::BiographyEditor()
{
    layout = new QGridLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QLabel *label_enable_edit = new QLabel(tr("Lock Relations"));
    QCheckBox *checkbox_enable_edit = new QCheckBox;

    QLabel *label_custom_display = new QLabel(tr("Customize details displayed"));
    QCheckBox *checkbox_custom_display = new QCheckBox;

    createBio();

    layout->addWidget(label_enable_edit, 0, 0, 1, 29, Qt::AlignRight);
    layout->addWidget(checkbox_enable_edit, 0, 29, Qt::AlignRight);
    layout->addWidget(label_custom_display, 1, 0, 1, 29, Qt::AlignRight);
    layout->addWidget(checkbox_custom_display, 1, 29, Qt::AlignRight);
    layout->addWidget(area, 2, 0, 1, 30); //Qt::AlignTop
    setLayout(layout);
}


void BiographyEditor::createBio()
{
    widget_layout = new QVBoxLayout;
    widget_layout->setSizeConstraint(QLayout::SetMinAndMaxSize); // necessary to see labels
    widget_layout->setContentsMargins(2, 2, 2, 2);

    widget = new QWidget;
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
