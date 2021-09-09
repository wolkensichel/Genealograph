#include "partnershipinfo.h"


PartnershipInfo::PartnershipInfo(partnership new_partnership)
    : relation_type(new_partnership.type), from(new_partnership.from), until(new_partnership.until), place(new_partnership.place)
{
    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    widget = new QWidget();
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setLayout(layout);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);

    fillFields();

    setZValue(-1);
}


void PartnershipInfo::fillFields()
{
    QString type = (relation_type == 1) ? QString(QChar(0x26AD)) : "";
    QLabel *label_type = new QLabel(type);
    label_type->setAlignment(Qt::AlignCenter);
    QFont font = label_type->font();
    font.setPointSize(font.pointSize()-2);
    label_type->setFont(font);

    layout->addWidget(label_type);
    label_type->show();

    QString time = from + " (" + place + ") " + QString(QChar(0x2013)) + " " + until;
    QLabel *label_time = new QLabel(time);
    label_time->setAlignment(Qt::AlignCenter);
    label_time->setFont(font);

    layout->addWidget(label_time);
    label_time->show();
}


void PartnershipInfo::updatePosition(QPointF relation_center)
{
    QPointF position = relation_center - QPointF(widget->width()/2, widget->height()+5);
    setPos(position);
}
