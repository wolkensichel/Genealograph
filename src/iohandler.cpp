#include <QMessageBox>

#include "iohandler.h"
#include <QTextStream>
#include <iostream>

#include "treeobject.h"
#include "relation.h"


IOHandler::IOHandler()
{

}


int IOHandler::openFromFile(load_data &file_data)
{
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home/wolkensichel/",
        tr("Generations File (*.gen);;All Files (*)"));

    if (file_name.isEmpty())
        return -1;
    else {
        QFile file(file_name);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return -1;
        }

        return load(file, file_data);
    }
}


void IOHandler::saveToFile(sheet sheet_size, QList<TreeObject *> tree_objects, QList<Relation *> partnerships, QList<Relation *> descents)
{
    QString file_name = getSaveFileName(this,
        tr("Save File"), "/home/wolkensichel/",
        tr("Generations File (*.gen);;All Files (*)"));

    if (file_name.isEmpty())
        return;
    else {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        store(file, sheet_size, tree_objects, partnerships, descents);
    }
}


void IOHandler::store(QFile &file, sheet sheet_size, QList<TreeObject *> tree_objects, QList<Relation *> partnerships, QList<Relation *> descents)
{
    //qRegisterMetaType<person>("person");
    //qRegisterMetaTypeStreamOperators<person>("person");
    QTextStream cout(stdout);

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    QString indicator = QString("<SHT>");
    out << indicator << sheet_size.width << sheet_size.height;

    indicator = QString("<TRBJ>");
    QListIterator<TreeObject *> it_to(tree_objects);
    while (it_to.hasNext()) {
        TreeObject *current_object = it_to.next();
        out << indicator << current_object->id << current_object->pos() << current_object->bio;
        cout << indicator << QString::number(current_object->id) << "\n";
    }
    cout << "\n";
    indicator = QString("<PRTN>");
    QListIterator<Relation *> it_ps(partnerships);
    while (it_ps.hasNext())
    {
        Relation *current_relation = it_ps.next();
        out << indicator << current_relation->tree_objects.first()->id
                         << current_relation->tree_objects.last()->id;
        cout << indicator << ", " << current_relation->tree_objects.first()->id << ", "
                                  << current_relation->tree_objects.last()->id << "\n";
    }
    cout << "\n";
    indicator = QString("<DSCN>");
    QListIterator<Relation *> it_d(descents);
    while (it_d.hasNext())
    {
        Relation *current_relation = it_d.next();
        out << indicator << current_relation->tree_objects.last()->id
                         << current_relation->parents->tree_objects.first()->id
                         << current_relation->parents->tree_objects.last()->id;
        cout << indicator << ", " << current_relation->tree_objects.last()->id << ", "
             << current_relation->parents->tree_objects.first()->id << ", "
             << current_relation->parents->tree_objects.last()->id << "\n";
    }
    cout << "\n";
}


int IOHandler::load(QFile &file, load_data &file_data)
{
    QTextStream cout(stdout);

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    QString indicator;
    in >> indicator;

    if (indicator == QString("<SHT>"))
        in >> file_data.worksheet.width >> file_data.worksheet.height;
    else
    {
        QMessageBox::information(this, tr("No valid Generations file"),
                     tr("The file you are attempting to open is not a valid file."));
        return -1;
    }

    QList<object_data *> *objects = new QList<object_data *>();
    QList<partnership_data *> *partnerships = new QList<partnership_data *>();
    QList<descent_data *> *descents = new QList<descent_data *>();

    while(in.atEnd() == false)
    {
        in >> indicator;
        cout << indicator << "\n";
        if (indicator == QString("<TRBJ>"))
        {
            object_data *set = new object_data();
            in >> set->id >> set->pos >> set->bio;
            objects->append(set);
        }
        else if (indicator == QString("<PRTN>"))
        {
            partnership_data *set = new partnership_data();
            in >> set->id_partner1 >> set->id_partner2;
            partnerships->append(set);
        }
        else if (indicator == QString("<DSCN>"))
        {
            descent_data *set = new descent_data();
            in >> set->id_child >> set->id_parent1 >> set->id_parent2;
            descents->append(set);
        }
    }

    file_data.objects = *objects;
    file_data.partnerships = *partnerships;
    file_data.descents= *descents;

    return 0;
}
