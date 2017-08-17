#include "StackedSegmentMesh.h"
#include "ui_StackedSegmentMesh.h"

#include "QVTKWidgetRenderer.h"

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


void StackedSegmentMesh::segmentMesh()
{
    QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_6.vtk", *(ui->stacked_segment_1), 1.0, (float [3]){0.8900, 0.8100, 0.3400}, (float [3]){0.0, 0.0, 0.0} );
    QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_3.vtk", *(ui->stacked_segment_2), 1.0, (float [3]){0.9020, 0.9020, 0.9804}, (float [3]){0.0, 0.0, 0.0});
    QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_5.vtk", *(ui->stacked_segment_3), 1.0, (float [3]){0.2000, 0.6300, 0.7900}, (float [3]){0.0, 0.0, 0.0});
    QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_2.vtk", *(ui->stacked_segment_4), 1.0, (float [3]){0.9804, 0.5020, 0.4471}, (float [3]){0.0, 0.0, 0.0});
}
