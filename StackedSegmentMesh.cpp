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


void StackedSegmentMesh::segmentMesh(){
	float p1[] = { 0.8900, 0.8100, 0.3400 };
	float p2[] = { 0.0, 0.0, 0.0 };
	float p3[] = { 0.9020, 0.9020, 0.9804 };
	float p4[] = { 0.2000, 0.6300, 0.7900 };
	float p5[] = { 0.9804, 0.5020, 0.4471 };

	QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_6.vtk", *(ui->stacked_segment_1), 1.0, p1, p2);
	QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_3.vtk", *(ui->stacked_segment_2), 1.0, p3, p2);
	QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_5.vtk", *(ui->stacked_segment_3), 1.0, p4, p2);
	QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_2.vtk", *(ui->stacked_segment_4), 1.0, p5, p2);
}
