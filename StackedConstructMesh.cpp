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
	float p1[] = { 1.0, 1.0, 1.0 }; float p2[] = { 0.0, 0.0, 0.0 };
    QVTKWidgetRenderer::renderVTK("../Resources/knees/construction_edgeCoordinates.vtk", *(ui->stacked_construction_edge), 0.05, p1, p2);
    QVTKWidgetRenderer::renderColoredVTK("../Resources/knees/construction_edgeDensity.vtk", *(ui->stacked_construction_skeleton) );
    QVTKWidgetRenderer::renderVTK("../Resources/knees/kmeshcm.vtk", *(ui->stacked_construction_kmeshcm), 2.0, p2, p1);
	float p3[] = { 0.9608, 0.8706, 0.7020 }; float p4[] = { 0.9608, 0.8706, 0.7020 };
    QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_1.vtk", *(ui->stacked_construction_kmeshim), 1.0, p3,p4 );
    
}
