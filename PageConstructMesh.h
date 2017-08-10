#ifndef PAGECONSTRUCTMESH_H
#define PAGECONSTRUCTMESH_H

#include <QWidget>
#include <QDebug>
namespace Ui {
class PageConstructMesh;
}

class PageConstructMesh : public QWidget
{
    Q_OBJECT

public:
    explicit PageConstructMesh(QWidget *parent = 0);
    ~PageConstructMesh();

private slots:
    void on_pushButton_clicked();

signals:
    void constructMesh();

private:
    Ui::PageConstructMesh *ui;
};

#endif // PAGECONSTRUCTMESH_H
