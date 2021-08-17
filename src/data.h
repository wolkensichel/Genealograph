#ifndef DATA_H
#define DATA_H

#include <QApplication>
#include <QDate>


struct person {
    QString first_name;
    QString last_name;
    QString birth_name;
    QString birth_place;
    QDate birth_date;
    friend QDataStream & operator << (QDataStream &stream, const person& bio)
    {
        stream << bio.first_name;
        stream << bio.last_name;
        return stream;
    }

    friend QDataStream & operator >> (QDataStream &stream, person& bio)
    {
        QString id;
        stream >> bio.first_name;
        stream >> bio.last_name;
        return stream;
    }
};
//Q_DECLARE_METATYPE(person);


struct object_data
{
    quint16 id;
    QPointF pos;
    person bio;
};


struct sheet
{
    quint16 width;
    quint16 height;
};


struct load_data
{
    sheet worksheet;
    QList<object_data *> objects;
};


#endif // DATA_H
