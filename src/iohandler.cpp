#include <QMessageBox>

#include "iohandler.h"
#include <QTextStream>
#include <iostream>

#include "treeobject.h"


IOHandler::IOHandler()
{

}


load_data* IOHandler::openFromFile()
{
    load_data* file_data = nullptr;
    QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home/wolkensichel/",
        tr("Generations File (*.gen);;All Files (*)"));

    if (file_name.isEmpty())
        return file_data;
    else {
        QFile file(file_name);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return file_data;
        }

        return load(file);
    }

}


void IOHandler::saveToFile(sheet sheet_size, QList<TreeObject *> data)
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

        store(file, sheet_size, data);
    }
}


void IOHandler::store(QFile &file, sheet sheet_size, QList<TreeObject *> data)
{
    //qRegisterMetaType<person>("person");
    //qRegisterMetaTypeStreamOperators<person>("person");
    QTextStream cout(stdout);

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_15);

    out << QString("Sheet") << sheet_size.width << sheet_size.height;

    QList<TreeObject *>::iterator it;
    for (it = data.begin(); it != data.end(); ++it)
    {
        out << QString("TreeObject") << it.operator*()->id << it.operator*()->pos() << it.operator*()->bio;
    }
}


load_data* IOHandler::load(QFile &file)
{
    QTextStream cout(stdout);

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_15);

    QString indicator;
    sheet worksheet = {0, 0};
    QList<object_data *> *input_data = new QList<object_data *>();

    while(in.atEnd() == false)
    {
        in >> indicator;
        if (indicator == QString("Sheet"))
        {
            in >> worksheet.width >> worksheet.height;
            if (worksheet.width == 0)
            {
                QMessageBox::information(this, tr("No contacts in file"),
                    tr("The file you are attempting to open contains no contacts."));
                break;
            }
        }
        else if (indicator == QString("TreeObject"))
        {
            object_data *set = new object_data();
            in >> set->id >> set->pos >> set->bio;
            input_data->append(set);
        }
    }

    load_data *file_data = new load_data();
    file_data->worksheet = worksheet;
    file_data->objects = *input_data;

    return file_data;
}