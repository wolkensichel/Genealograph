#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>

#include "biographyeditor.h"

BiographyEditor::BiographyEditor()
{
    layout = new QGridLayout;
    layout->setContentsMargins(4, 4, 4, 4);

    QLabel *label_enable_edit = new QLabel(tr("Lock Relations"));
    QCheckBox *checkbox_enable_edit = new QCheckBox;

    QLabel *label_custom_display = new QLabel(tr("Customize details displayed"));
    QCheckBox *checkbox_custom_display = new QCheckBox;

    createInfoPage();

    layout->addWidget(label_enable_edit, 0, 0, 1, 29, Qt::AlignRight);
    layout->addWidget(checkbox_enable_edit, 0, 29, Qt::AlignRight);
    layout->addWidget(label_custom_display, 1, 0, 1, 29, Qt::AlignRight);
    layout->addWidget(checkbox_custom_display, 1, 29, Qt::AlignRight);
    layout->addWidget(area, 2, 0, 1, 30); //Qt::AlignTop
    setLayout(layout);
}


void BiographyEditor::createInfoPage()
{
    widget_layout = new QVBoxLayout;
    widget_layout->setSizeConstraint(QLayout::SetMinimumSize);

    widget = new QWidget;
    widget->setLayout(widget_layout);

    area = new QScrollArea;
    area->setWidget(widget);

    QLabel *fields[20];
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);

    for (int i = 0; i < 20; ++i) {
        fields[i] = new QLabel(tr("Info\n %1").arg(i + 1));
        fields[i]->setAutoFillBackground(true);
        fields[i]->setPalette(palette);
        widget_layout->addWidget(fields[i]);
    }
}