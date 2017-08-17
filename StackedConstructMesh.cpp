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
    QVTKWidgetRenderer::renderVTK("../Resources/knees/construction_edgeCoordinates.vtk", *(ui->stacked_construction_edge), 0.05, (float [3]){1.0, 1.0, 1.0}, (float [3]){0.0, 0.0, 0.0});
    QVTKWidgetRenderer::renderColoredVTK("../Resources/knees/construction_edgeDensity.vtk", *(ui->stacked_construction_skeleton) );
    QVTKWidgetRenderer::renderVTK("../Resources/knees/kmeshcm.vtk", *(ui->stacked_construction_kmeshcm), 2.0, (float [3]){0, 0, 0}, (float [3]){1.0, 1.0, 1.0});
    QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_1.vtk", *(ui->stacked_construction_kmeshim), 1.0, (float [3]){0.9608, 0.8706, 0.7020}, (float [3]){0.0, 0.0, 0.0} );
    
}
