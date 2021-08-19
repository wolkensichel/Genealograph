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
    bool openFromFile(load_data&, QString&);
    void saveFile(QString&, save_data&);
    void saveToFile(save_data&, QString&);

private:
    void store(QFile&, save_data&);
    bool load(QFile&, load_data&);

    QString suffix;
};

#endif // IOHANDLER_H
