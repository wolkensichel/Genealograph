#ifndef DATA_H
#define DATA_H

#include <QApplication>
#include <QDate>

struct person {
    int id;
    QString firstname;
    QString lastname;
    QString birthname;
    QString birthplace;
    QDate birthdate;
};

#endif // DATA_H