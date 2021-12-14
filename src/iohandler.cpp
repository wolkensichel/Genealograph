#include <QMessageBox>

#include "mainwindow.h"
#include "iohandler.h"
#include "treeobject.h"
#include "relation.h"


IOHandler::IOHandler()
{
    //setDefaultSuffix("gen"); // not working on Linux
    suffix = ".geg";
}


bool IOHandler::openFromFile(load_data &file_data, QString &save_file)
{
    QString file_name = getOpenFileName(this,
        tr("Open File"), "/home/wolkensichel/",
        tr("Generations File (*.geg);;All Files (*)"));

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

    QString indicator = QString("<SHT>");
    out << indicator << worksheet_data.worksheet.width << worksheet_data.worksheet.height;

    indicator = QString("<TRBJ>");
    QMapIterator<quint16, TreeObject *> it_to(worksheet_data.tree_objects);
    while (it_to.hasNext())
    {
        QMapIterator<quint16, TreeObject *>::Item current_object = it_to.next();
        current_object.value()->content.pos = current_object.value()->pos();
        out << indicator << current_object.value()->content;
    }

    indicator = QString("<PRTN>");
    QMapIterator<quint16, Relation *> it_ps(worksheet_data.partnerships);
    while (it_ps.hasNext())
        out << indicator << it_ps.next().value()->info_card->content;

    indicator = QString("<DSCN>");
    QMapIterator<quint16, Relation *> it_d(worksheet_data.descents);
    while (it_d.hasNext())
        out << indicator << it_d.next().value()->info_descent;
}


bool IOHandler::load(QFile &file, load_data &file_data)
{
    QDataStream in(&file);

    QString indicator;
    in >> indicator;

    if (indicator == QString("<SHT>"))
        in >> file_data.worksheet.width >> file_data.worksheet.height;
    else
        return false;

    QList<person *> *persons = new QList<person *>();
    QList<partnership *> *partnerships = new QList<partnership *>();
    QList<descent *> *descents = new QList<descent *>();

    while(in.atEnd() == false)
    {
        in >> indicator;
        if (indicator == QString("<TRBJ>"))
        {
            person *content = new person();
            in >> content;
            persons->append(content);
        }
        else if (indicator == QString("<PRTN>"))
        {
            partnership *content = new partnership();
            in >> content;
            partnerships->append(content);
        }
        else if (indicator == QString("<DSCN>"))
        {
            descent *content = new descent();
            in >> content;
            descents->append(content);
        }
    }

    file_data.persons = *persons;
    file_data.partnerships = *partnerships;
    file_data.descents= *descents;

    return true;
}
