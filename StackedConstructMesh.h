#ifndef STACKEDCONSTRUCTMESH_H
#define STACKEDCONSTRUCTMESH_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class StackedConstructMesh;
}

class StackedConstructMesh : public QWidget
{
    Q_OBJECT

public:
    explicit StackedConstructMesh(QWidget *parent = 0);
    ~StackedConstructMesh();

    void constructMesh();

private:
    Ui::StackedConstructMesh *ui;
};

#endif // STACKEDCONSTRUCTMESH_H
