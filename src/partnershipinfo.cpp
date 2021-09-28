#include <QGraphicsSceneMouseEvent>

#include "partnershipinfo.h"
#include "worksheet.h"


PartnershipInfo::PartnershipInfo(partnership new_partnership, QList<std::tuple<QString, QString, bool>> input_cfg_partnerships)
    : input_cfg(input_cfg_partnerships)
{
    content = new_partnership;

    layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    widget = new QWidget();
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setLayout(layout);

    proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);

    fillFields();
    widget->adjustSize();

    setZValue(-1);
    setPen(Qt::NoPen);
    setBrush(Qt::white);
    setRect(0, 0, widget->width(), widget->height());
}


void PartnershipInfo::fillFields()
{
    QString key = "Type";
    QString value = getValue(content.items[key]);
    value = typeSymbol(value);
    QLabel *label_type = new QLabel(value);
    label_type->setAlignment(Qt::AlignCenter);
    label_type->setMaximumHeight(10);

    QFont font = label_type->font();
    font.setPointSize(font.pointSize()+6);
    label_type->setFont(font);

    layout->addWidget(label_type);
    labels.insert(key, label_type);
    toggleShowHide(key);


    key = "Formed in";
    value = getValue(content.items[key]);
    QLabel *label_place = new QLabel(value);
    label_place->setAlignment(Qt::AlignCenter);

    font = label_place->font();
    font.setPointSize(font.pointSize()-2);
    label_place->setFont(font);

    layout->addWidget(label_place);
    labels.insert(key, label_place);
    toggleShowHide(key);

    key = "Date formed";
    value = generateDateString();
    QLabel *label_time = new QLabel(value);
    label_time->setAlignment(Qt::AlignCenter);

    label_time->setFont(font);

    layout->addWidget(label_time);
    labels.insert(key, label_time);
    toggleShowHide(key);
}


void PartnershipInfo::toggleShowHide(QString &key)
{
    if (content.items[key].show)
        labels[key]->show();
    else
        labels[key]->hide();
}


QString PartnershipInfo::typeSymbol(QString value)
{
    if (value == "Married")
        value = QString(QChar(0x26AD));

    return value;
}


QString PartnershipInfo::generateDateString()
{
    QString key = "Date formed";
    QString date_formed = getValue(content.items[key]);
    if (!date_formed.isEmpty()) {
        date_formed = appendices(key, date_formed);
    }

    key = "Date ended";
    QString date_ended = getValue(content.items[key]);
    if (!date_ended.isEmpty()) {
        QString key = "Date ended";
        date_ended = appendices(key, date_ended);
    }

    return date_formed + date_ended;
}


void PartnershipInfo::updatePosition(QPointF relation_center)
{
    QPointF position = relation_center - QPointF(widget->width()/2, widget->height()+5);
    setPos(position);
}


QString PartnershipInfo::getValue(container_item &item)
{
    QString value;
    if (item.form_type == "QDateEdit")
        value = convertDateFormatForDisplay(item.value.toString());
    else
        value = item.value.toString();
    return value;
}


QString PartnershipInfo::convertDateFormatForDisplay(QString value)
{
    QList<QString> value_components = value.split("-");
    value = value_components[2].remove(QRegularExpression("^[0]*")) + "." +
            value_components[1].remove(QRegularExpression("^[0]*")) + "." +
            value_components[0].remove(QRegularExpression("^[0]*"));
    return value;
}


QString PartnershipInfo::appendices(QString &key, QString value)
{
    if (key == "Date ended") {
        if (!content.items["Date formed"].value.toString().isEmpty())
            value = " " + QString(QChar(0x2013)) + " " + value;
        else
            value = "???? " + QString(QChar(0x2013)) + " " + value;
    }

    return value;
}


void PartnershipInfo::updatePartnershipInfo(QString key, QVariant datum)
{
    content.items[key].value = datum;

    if (key == "Date formed" || key == "Date ended") {
        QString value = generateDateString();
        labels["Date formed"]->setText(value);
    }
    else if (key == "Type") {
        QString value = getValue(content.items[key]);
        value = typeSymbol(value);
        labels[key]->setText(value);
    }
    else {
        QString value = getValue(content.items[key]);
        if (!value.isEmpty())
            value = appendices(key, value);
        labels[key]->setText(value);
    }

    widget->adjustSize();
    setRect(-1, -1, widget->width()+1, widget->height()+1);
}


void PartnershipInfo::changeShowStatus(QString key, bool status)
{
    content.items[key].show = status;

    if ((key == "Date ended" || key == "Date formed")) {
        if (content.items["Date ended"].show == content.items["Date formed"].show) {
            QString key = "Date formed";
            toggleShowHide(key);
        }
    }
    else
        toggleShowHide(key);

    widget->adjustSize();
    setRect(-1, -1, widget->width()+1, widget->height()+1);
    partnership_relation->updatePosition();
}


void PartnershipInfo::connectPartnershipRelation(Relation *relation)
{
    partnership_relation = relation;
}


void PartnershipInfo::removePartnershipInfo()
{
    scene()->removeItem(this);
    delete this;
}
