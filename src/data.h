#ifndef DATA_H
#define DATA_H

#include <QApplication>
#include <QDate>
#include <QLabel>


class TreeObject;
class Relation;


struct person {
    QMap<QString, QVariant> bio;
    friend QDataStream & operator << (QDataStream &stream, const person& individual) {
        stream << individual.bio;
        return stream;
    }

    friend QDataStream & operator >> (QDataStream &stream, person& individual) {
        stream >> individual.bio;
        return stream;
    }
};


struct object_data
{
    quint16 id;
    QPointF pos;
    person individual;
};


struct partnership_data
{
    quint16 id_partner1;
    quint16 id_partner2;
};


struct descent_data
{
    quint16 id_child;
    quint16 id_parent1;
    quint16 id_parent2;
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
    QList<partnership_data *> partnerships;
    QList<descent_data *> descents;
};


struct save_data
{
    sheet worksheet;
    QList<TreeObject *> tree_objects;
    QList<Relation *> partnerships;
    QList<Relation *> descents;
};


struct label_config
{
    QLabel *object;
    bool show;
};

#endif // DATA_H
