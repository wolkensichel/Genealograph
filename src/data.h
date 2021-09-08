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


struct bio_item {
    QVariant value;
    QString form_type;
    bool show;

    friend QDataStream & operator << (QDataStream &stream, const bio_item item) {
        stream << item.value;
        stream << item.form_type;
        stream << item.show;
        return stream;
    }
    friend QDataStream & operator >> (QDataStream &stream, bio_item &item) {
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
    QMap<QString, bio_item> bio;

    friend QDataStream & operator << (QDataStream &stream, const person& individual) {
        stream << individual.id;
        stream << individual.pos;
        stream << individual.relations_dock_lock;
        stream << individual.biography_dock_lock;
        stream << individual.placeholder;
        stream << individual.bio;
        return stream;
    }

    friend QDataStream & operator >> (QDataStream &stream, person *individual) {
        stream >> individual->id;
        stream >> individual->pos;
        stream >> individual->relations_dock_lock;
        stream >> individual->biography_dock_lock;
        stream >> individual->placeholder;
        stream >> individual->bio;
        return stream;
    }
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
    QList<person *> persons;
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


union input_form
{
    QLineEdit *line_edit;
    QTextEdit *text_edit;
    QDateEdit *date_edit;
    QComboBox *box_edit;
};

#endif // DATA_H
