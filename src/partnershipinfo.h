#ifndef PARTNERSHIPINFO_H
#define PARTNERSHIPINFO_H

#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "data.h"


class PartnershipInfo : public QGraphicsRectItem
{
    QMap<QString, QString> dependant_labels = {
        {"Date formed", "Date ended"}
    };

public:
    PartnershipInfo(partnership, QList<std::tuple<QString, QString, bool>>);
    void connectPartnershipRelation(Relation*);
    void updatePosition(QPointF);
    void removePartnershipInfo();
    void updatePartnershipInfo(QString, QVariant);
    void changeShowStatus(QString, bool);

    QList<std::tuple<QString, QString, bool>> input_cfg;
    partnership content;
    Relation *partnership_relation;

    QWidget *widget;

private:
    void fillFields();
    QString typeSymbol(QString);
    QString generateDateString();
    QString getValue(container_item&);
    QString appendices(QString&, QString);
    void toggleShowHide(QString&);
    QString convertDateFormatForDisplay(QString);

    QGraphicsProxyWidget *proxy;
    QVBoxLayout *layout;

    QMap<QString, QLabel*> labels;
};

#endif // PARTNERSHIPINFO_H
