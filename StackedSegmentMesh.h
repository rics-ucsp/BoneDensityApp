#ifndef STACKEDSEGMENTMESH_H
#define STACKEDSEGMENTMESH_H

#include <QWidget>

namespace Ui {
class StackedSegmentMesh;
}

class StackedSegmentMesh : public QWidget
{
    Q_OBJECT

public:
    explicit StackedSegmentMesh(QWidget *parent = 0);
    ~StackedSegmentMesh();

    void segmentMesh();
private:
    Ui::StackedSegmentMesh *ui;
};

#endif // STACKEDSEGMENTMESH_H
