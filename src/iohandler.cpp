#include <QMessageBox>

#include "mainwindow.h"
#include "iohandler.h"
#include "treeobject.h"
#include "relation.h"


IOHandler::IOHandler()
{
    //setDefaultSuffix("gen"); // not working on Linux
    suffix = ".gen";
}


bool IOHandler::openFromFile(load_data &file_data, QString &save_file)
{
    QString file_name = getOpenFileName(this,
        tr("Open File"), "/home/wolkensichel/",
        tr("Generations File (*.gen);;All Files (*)"));

    if (file_name.isEmpty())
        return false;
    else {
        QFile file(file_name);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return false;
        }

        if(load(file, file_data))
        {
            save_file = file_name;
            return true;
        }
        else
            return false;
    }
}


void IOHandler::saveFile(QString &file_name, save_data &worksheet_data)
{
    if (file_name.length() > suffix.length()) {
        if (!file_name.endsWith(suffix, Qt::CaseInsensitive))
            file_name += suffix;
    }
    else if (file_name == suffix) {
        return;
    }
    else {
        file_name += suffix;
    }

    QFile file(file_name);
     if (!file.open(QIODevice::WriteOnly)) {
         QMessageBox::information(this, tr("Unable to open file"),
             file.errorString());
         return;
     }
     store(file, worksheet_data);
}


void IOHandler::saveToFile(save_data &worksheet_data, QString &save_file)
{
    QString file_name = getSaveFileName(this,
        tr("Save File"), "/home/wolkensichel/",
        tr("Generations File (*.gen);;All Files (*)"));

    if (!file_name.isEmpty() && !file_name.isNull()) {
        saveFile(file_name, worksheet_data);
        save_file = file_name;
    }
}


void IOHandler::store(QFile &file, save_data &worksheet_data)
{
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    QString indicator = QString("<SHT>");
    out << indicator << worksheet_data.worksheet.width << worksheet_data.worksheet.height;

    indicator = QString("<TRBJ>");
    QListIterator<TreeObject *> it_to(worksheet_data.tree_objects);
    while (it_to.hasNext())
    {
        TreeObject *current_object = it_to.next();
        current_object->individual.pos = current_object->pos();
        out << indicator << current_object->individual;
    }

    indicator = QString("<PRTN>");
    QListIterator<Relation *> it_ps(worksheet_data.partnerships);
    while (it_ps.hasNext())
    {
        Relation *current_relation = it_ps.next();
        out << indicator << current_relation->tree_objects.first()->individual.id
                         << current_relation->tree_objects.last()->individual.id;
    }

    indicator = QString("<DSCN>");
    QListIterator<Relation *> it_d(worksheet_data.descents);
    while (it_d.hasNext())
    {
        Relation *current_relation = it_d.next();
        out << indicator << current_relation->tree_objects.last()->individual.id
                         << current_relation->parents->tree_objects.first()->individual.id
                         << current_relation->parents->tree_objects.last()->individual.id;
    }
}


bool IOHandler::load(QFile &file, load_data &file_data)
{
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    QString indicator;
    in >> indicator;

    if (indicator == QString("<SHT>"))
        in >> file_data.worksheet.width >> file_data.worksheet.height;
    else
        return false;

    QList<person *> *persons = new QList<person *>();
    QList<partnership_data *> *partnerships = new QList<partnership_data *>();
    QList<descent_data *> *descents = new QList<descent_data *>();

    while(in.atEnd() == false)
    {
        in >> indicator;
        if (indicator == QString("<TRBJ>"))
        {
            person *individual = new person();
            in >> individual;
            persons->append(individual);
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

    file_data.persons = *persons;
    file_data.partnerships = *partnerships;
    file_data.descents= *descents;

    return true;
}
