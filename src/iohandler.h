#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QFileDialog>

#include "data.h"

class TreeObject;
class Relation;

class IOHandler : public QFileDialog
{
    Q_OBJECT

public:
    IOHandler();
    int openFromFile(load_data&);
    void saveToFile(sheet, QList<TreeObject *>, QList<Relation *>, QList<Relation *>);

private:
    void store(QFile&, sheet, QList<TreeObject *>, QList<Relation *>, QList<Relation *>);
    int load(QFile&, load_data&);
};

#endif // IOHANDLER_H
