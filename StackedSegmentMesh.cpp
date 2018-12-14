#include "StackedSegmentMesh.h"
#include "ui_StackedSegmentMesh.h"
#include <string>
using namespace std;
#include "QVTKWidgetRenderer.h"


#include "StackedMultiplanarReconstruction.h"
#include "ui_StackedMultiplanarReconstruction.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include "vtkResliceImageViewer.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorThickLineRepresentation.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursor.h"

#include "vtkCellPicker.h"
#include "vtkProperty.h"
#include "vtkPlane.h"
#include "vtkImageData.h"
#include "vtkCommand.h"
#include "vtkPlaneSource.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkInteractorStyleImage.h"
#include "vtkImageSlabReslice.h"
#include "vtkBoundedPlanePointPlacer.h"
#include "vtkDistanceWidget.h"
#include "vtkDistanceRepresentation.h"
#include "vtkHandleRepresentation.h"
#include "vtkResliceImageViewerMeasurements.h"
#include "vtkDistanceRepresentation2D.h"
#include "vtkPointHandleRepresentation3D.h"
#include "vtkPointHandleRepresentation2D.h"

#include "vtkCamera.h"
#include <vtkVolumeProperty.h>
#include <vtkMatrix4x4.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkAxesActor.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>


#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkTextMapper.h>
#include <vtkTransform.h>
#include <vtkImageShiftScale.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageSlice.h>
#include <vtkImageProperty.h>
#include <vtkImageActor.h>
#include <vtkTextActor.h>


StackedSegmentMesh::StackedSegmentMesh(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StackedSegmentMesh)
{
	ui->setupUi(this);
	//init();
}

StackedSegmentMesh::~StackedSegmentMesh()
{
	delete ui;
}

void StackedSegmentMesh::init() {
	float p1[] = { 0.8900, 0.8100, 0.3400 };
	float p2[] = { 0.0, 0.0, 0.0 };
	//float p3[] = { 0.9020, 0.9020, 0.9804 };
	//float p4[] = { 0.2000, 0.6300, 0.7900 };
	float p5[] = { 0.9804, 0.5020, 0.4471 };

	float p3[] = { 0.9608, 0.8706, 0.7020 }; float p4[] = { 0.9608, 0.8706, 0.7020 };
	QVTKWidgetRenderer::renderVTK("../Resources/knees/segment_knee_mesh_region_1.vtk", *(ui->stacked_segment_2), 1.0, p3, p4);
}

void StackedSegmentMesh::segmentMesh() {

	init();

	archivosVtk.push_back("../Resources/knee_mesh_region_1.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_2.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_3.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_4.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_5.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_6.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_7.vtk");

	colores.push_back(QColor(255, 0, 0));
	colores.push_back(QColor(0, 0, 255));
	colores.push_back(QColor(0, 255, 0));
	colores.push_back(QColor(255, 0, 255));
	colores.push_back(QColor(255, 255, 0));
	colores.push_back(QColor(255, 68, 173));
	colores.push_back(QColor(246, 36, 89));

	renderer = vtkSmartPointer<vtkRenderer>::New();

	for (register int i = 0; i < 7; ++i) {
		mapper[i] = vtkSmartPointer<vtkDataSetMapper>::New();
		actor[i] = vtkSmartPointer<vtkActor>::New();
	}

	for (register int i = 0; i < 7; ++i) {
		renderVTK(archivosVtk[i], *(ui->stacked_segment_1), colores[i], mapper[i], actor[i]);
	}

	(ui->stacked_segment_1)->GetRenderWindow()->Render();
	(ui->stacked_segment_1)->show();

}


void StackedSegmentMesh::renderVTK(QString vtkFilename, QVTKWidget &widgetvtk, QColor &color, vtkDataSetMapper* mapper, vtkActor* actor) {


	//vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
	reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
	reader->SetFileName(vtkFilename.toStdString().c_str());
	reader->Update();

	mapper->SetInputConnection(reader->GetOutputPort());

	double r = color.red() / 255;
	double g = color.green() / 255;
	double b = color.blue() / 255;

	actor->GetProperty()->SetColor(r, g, b);
	actor->GetProperty()->SetOpacity(0.5);
	actor->SetMapper(mapper);


	//vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	renderer->AddActor(actor);
	renderer->SetBackground(39 / 255, 40 / 255, 34 / 255);

	widgetvtk.GetRenderWindow()->AddRenderer(renderer);
	widgetvtk.show();

	/*ui->sldrOpacity->setMinimum(1);
	ui->sldrOpacity->setMaximum(100);
	ui->sldrOpacity->setValue(50);*/
}