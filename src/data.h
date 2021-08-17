#ifndef DATA_H
#define DATA_H

#include <QApplication>
#include <QDate>

struct person {
    int id;
    QString first_name;
    QString last_name;
    QString birth_name;
    QString birth_place;
    QDate birth_date;
};

#endif // DATA_H
