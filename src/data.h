#ifndef DATA_H
#define DATA_H

#include <QApplication>
#include <QDate>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QComboBox>


class TreeObject;
class Relation;


struct container_item {
    QVariant value;
    QString form_type;
    bool show;

    friend QDataStream& operator << (QDataStream &stream, const container_item item) {
        stream << item.value;
        stream << item.form_type;
        stream << item.show;
        return stream;
    }
    friend QDataStream& operator >> (QDataStream &stream, container_item &item) {
        stream >> item.value;
        stream >> item.form_type;
        stream >> item.show;
        return stream;
    }
};


struct person {
    quint16 id;
    QPointF pos;
    bool relations_dock_lock;
    bool biography_dock_lock;
    bool placeholder;
    QMap<QString, container_item> items;

    friend QDataStream & operator << (QDataStream &stream, const person &instance) {
        stream << instance.id;
        stream << instance.pos;
        stream << instance.relations_dock_lock;
        stream << instance.biography_dock_lock;
        stream << instance.placeholder;
        stream << instance.items;
        return stream;
    }

    friend QDataStream & operator >> (QDataStream &stream, person *instance) {
        stream >> instance->id;
        stream >> instance->pos;
        stream >> instance->relations_dock_lock;
        stream >> instance->biography_dock_lock;
        stream >> instance->placeholder;
        stream >> instance->items;
        return stream;
    }
};


struct partnership
{
    quint16 id;
    QMap<QString, container_item> items;

    friend QDataStream & operator << (QDataStream &stream, const partnership &instance) {
        stream << instance.id;
        stream << instance.items;
        return stream;
    }
    friend QDataStream & operator >> (QDataStream &stream, partnership *instance) {
        stream >> instance->id;
        stream >> instance->items;
        return stream;
    }
};


struct descent
{
    quint16 id;
    QMap<QString, container_item> items;

    friend QDataStream & operator << (QDataStream &stream, const descent &instance) {
        stream << instance.id;
        stream << instance.items;
        return stream;
    }
    friend QDataStream & operator >> (QDataStream &stream, descent *instance) {
        stream >> instance->id;
        stream >> instance->items;
        return stream;
    }
};


struct sheet
{
    quint16 width;
    quint16 height;
};


struct load_data
{
    sheet worksheet;
    QList<person *> persons;
    QList<partnership *> partnerships;
    QList<descent *> descents;
};


struct save_data
{
    sheet worksheet;
    QMap<quint16, TreeObject *> tree_objects;
    QMap<quint16, Relation *> partnerships;
    QMap<quint16, Relation *> descents;
};


union input_form
{
    QLineEdit *line_edit;
    QTextEdit *text_edit;
    QDateEdit *date_edit;
    QComboBox *box_edit;
};

#endif // DATA_H
