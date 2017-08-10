#include "PageConstructMesh.h"
#include "ui_PageConstructMesh.h"

PageConstructMesh::PageConstructMesh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PageConstructMesh)
{
    ui->setupUi(this);
}

PageConstructMesh::~PageConstructMesh()
{
    delete ui;
}

void PageConstructMesh::on_pushButton_clicked()
{
    emit constructMesh();
}
