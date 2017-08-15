#ifndef PAGESEGMENTMESH_H
#define PAGESEGMENTMESH_H

#include <QWidget>

namespace Ui {
class PageSegmentMesh;
}

class PageSegmentMesh : public QWidget
{
    Q_OBJECT

public:
    explicit PageSegmentMesh(QWidget *parent = 0);
    ~PageSegmentMesh();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PageSegmentMesh *ui;
};

#endif // PAGESEGMENTMESH_H
