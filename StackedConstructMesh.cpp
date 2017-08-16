#include "StackedConstructMesh.h"
#include "ui_StackedConstructMesh.h"

#include "QVTKWidgetRenderer.h"

StackedConstructMesh::StackedConstructMesh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedConstructMesh)
{
    ui->setupUi(this);
}

StackedConstructMesh::~StackedConstructMesh()
{
    delete ui;
}

void StackedConstructMesh::constructMesh()
{
    QVTKWidgetRenderer::renderVTK("../Resources/knees/construction_edgeDensity.vtk", *(ui->stacked_construction_kmeshcm));
    QVTKWidgetRenderer::renderVTK("../Resources/knees/construction_edgeCoordinates.vtk", *(ui->stacked_construction_kmeshim));
}
