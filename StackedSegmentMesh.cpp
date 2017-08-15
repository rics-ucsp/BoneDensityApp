#include "StackedSegmentMesh.h"
#include "ui_StackedSegmentMesh.h"

StackedSegmentMesh::StackedSegmentMesh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedSegmentMesh)
{
    ui->setupUi(this);
}

StackedSegmentMesh::~StackedSegmentMesh()
{
    delete ui;
}
