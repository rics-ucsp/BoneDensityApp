#include "PageSegmentMesh.h"
#include "ui_PageSegmentMesh.h"

PageSegmentMesh::PageSegmentMesh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageSegmentMesh)
{
    ui->setupUi(this);
}

PageSegmentMesh::~PageSegmentMesh()
{
    delete ui;
}

void PageSegmentMesh::on_pushButton_clicked()
{
    emit segmentMesh();
}
