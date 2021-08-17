#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <QFileDialog>

#include "data.h"

class TreeObject;

class IOHandler : public QFileDialog
{
    Q_OBJECT

public:
    IOHandler();
    load_data* openFromFile();
    void saveToFile(sheet, QList<TreeObject *>);

private:
    void store(QFile&, sheet, QList<TreeObject *>);
    load_data* load(QFile&);
};

#endif // IOHANDLER_H