#ifndef RELATIONSEDITOR_H
#define RELATIONSEDITOR_H

#include <QWidget>
#include <QGroupBox>

class RelationsEditor : public QWidget
{
    Q_OBJECT

public:
    RelationsEditor();

private:
    void createGroupBox(QGroupBox*);

    QGroupBox *groupbox_parents;
    QGroupBox *groupbox_partners;
    QGroupBox *groupbox_children;
};

#endif // RELATIONSEDITOR_H