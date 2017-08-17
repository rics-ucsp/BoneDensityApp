#include "StackedDensityAnalysis.h"
#include "ui_StackedDensityAnalysis.h"
//#include "QVTKWidgetRenderer.h"

///

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
///
StackedDensityAnalysis::StackedDensityAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedDensityAnalysis)
{
    ui->setupUi(this);
	init();

	std::string filename = "C:/rics-ucsp-project_bmd/bmc/bmc/extremidad";
	multiplanar_reconstruction(filename);

	visible = true;
	//opacity = 0.75;

	renderer_dicom_3 = vtkSmartPointer<vtkRenderer>::New();
	//ui->view_dicom_3 ->GetRenderWindow()->AddRenderer(renderer_dicom_3);
	//ui->view_dicom_3->show();

}

StackedDensityAnalysis::~StackedDensityAnalysis(){
    delete ui;
}



void StackedDensityAnalysis::multiplanar_reconstruction(std::string filename) {
	
	vtkSmartPointer<vtkJPEGReader> readerJPG = vtkSmartPointer<vtkJPEGReader>::New();
	readerJPG->SetDataByteOrderToLittleEndian();

	readerJPG->SetFilePrefix("C:/Users/Fil/Desktop/jpg-knee");
	//reader->SetDataSpacing(3.2, 3.2, 20);
	//reader->SetDataSpacing(40, 40, 40);
	readerJPG->SetFilePattern("%s/CT-Knee.379x229x305_%03d.jpg");
	readerJPG->SetDataExtent(0, 379, 0, 229, 0, 305);

	/*vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
	reader->SetDirectoryName(filename.c_str());*/

	readerJPG->Update();
	int imageDims[3];
	readerJPG->GetOutput()->GetDimensions(imageDims);

	for (int i = 0; i < 3; i++)
		riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();

	this->ui->view_dicom_1->SetRenderWindow(riw[2]->GetRenderWindow());
	riw[2]->SetupInteractor(this->ui->view_dicom_1->GetRenderWindow()->GetInteractor());

	this->ui->view_dicom_2->SetRenderWindow(riw[0]->GetRenderWindow());
	riw[0]->SetupInteractor(this->ui->view_dicom_2->GetRenderWindow()->GetInteractor());

	this->ui->view_dicom_3->SetRenderWindow(riw[1]->GetRenderWindow());
	riw[1]->SetupInteractor(this->ui->view_dicom_3->GetRenderWindow()->GetInteractor());

	std::vector<std::pair<int, int>> bounds(3, std::make_pair(0, 0));

	for (int i = 0; i < 3; i++) {
		vtkResliceCursorLineRepresentation *rep = vtkResliceCursorLineRepresentation::SafeDownCast(riw[i]->GetResliceCursorWidget()->GetRepresentation());
		riw[i]->SetResliceCursor(riw[i]->GetResliceCursor());
		rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(i);

		riw[i]->SetInputData(readerJPG->GetOutput());
		riw[i]->SetSliceOrientation(i);
		riw[i]->SetResliceModeToAxisAligned();
		riw[i]->GetRenderer()->SetBackground(0, 0, 0);

		int axis = this->riw[i]->GetSliceOrientation();
		double vup[3];
		riw[i]->GetRenderer()->GetActiveCamera()->GetViewUp(vup);
		double cameraPosition[3];
		riw[i]->GetRenderer()->GetActiveCamera()->GetPosition(cameraPosition);
		double cameraFocalPoint[3];
		riw[i]->GetRenderer()->GetActiveCamera()->GetPosition(cameraFocalPoint);

		for (int j = 0; j < 3; ++j)
			vup[j] = -vup[j];
		cameraPosition[axis] = cameraPosition[axis] - 2 * cameraFocalPoint[axis];

		riw[i]->GetRenderer()->GetActiveCamera()->SetPosition(cameraPosition);
		riw[i]->GetRenderer()->GetActiveCamera()->SetViewUp(vup);
		riw[i]->GetRenderer()->ResetCameraClippingRange();
		this->riw[i]->Render();

		bounds[i].first = riw[i]->GetSliceMin();
		bounds[i].second = riw[i]->GetSliceMax();

		riw[i]->SetColorLevel(10);//127.5
		riw[i]->SetColorWindow(255);//255

		riw[i]->GetRenderer()->ResetCamera();
		riw[i]->SliceScrollOnMouseWheelOff();
	}

	/*ui->scroll_axial->setMinimum(bounds[2].first);
	ui->scroll_axial->setMaximum(bounds[2].second);
	ui->scroll_sagittal->setMinimum(bounds[0].first);
	ui->scroll_sagittal->setMaximum(bounds[0].second);
	ui->scroll_coronal->setMinimum(bounds[1].first);
	ui->scroll_coronal->setMaximum(bounds[1].second);*/

	/*vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp = vtkSmartPointer<vtkProperty>::New();
	ren = vtkSmartPointer< vtkRenderer >::New();

	this->ui->view4->GetRenderWindow()->AddRenderer(ren);
	vtkRenderWindowInteractor *iren = this->ui->view4->GetInteractor();*/

	/*for (int i = 0; i < 3; i++) {
		planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
		planeWidget[i]->SetInteractor(iren);
		planeWidget[i]->SetPicker(picker);
		planeWidget[i]->RestrictPlaneToVolumeOn();
		double color[3] = { 0, 0, 0 };
		color[i] = 1;
		planeWidget[i]->GetPlaneProperty()->SetColor(color);

		color[0] /= 4.0;
		color[1] /= 4.0;
		color[2] /= 4.0;
		riw[i]->GetRenderer()->SetBackground(color);

		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(reader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);
		planeWidget[i]->SetSliceIndex(imageDims[i] / 2);

		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(ren);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();
	}*/

	//vtkSmartPointer<vtkResliceCursorCallback> cbk = vtkSmartPointer<vtkResliceCursorCallback>::New();
	//for (int i = 0; i < 3; i++) {
	//	cbk->IPW[i] = planeWidget[i];
	//	cbk->RCW[i] = riw[i]->GetResliceCursorWidget();
	//	riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);
	//	riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::WindowLevelEvent, cbk);
	//	riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceThicknessChangedEvent, cbk);
	//	riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResetCursorEvent, cbk);
	//	riw[i]->GetInteractorStyle()->AddObserver(vtkCommand::WindowLevelEvent, cbk);
	//	// Make them all share the same color map.
	//	riw[i]->SetLookupTable(riw[0]->GetLookupTable());
	//	planeWidget[i]->GetColorMap()->SetLookupTable(riw[0]->GetLookupTable());
	//	//planeWidget[i]->GetColorMap()->SetInput(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap()->GetInput());
	//	planeWidget[i]->SetColorMap(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap());
	//}

	//volume_rendering(reader);
	this->ui->view_dicom_1->show();
	this->ui->view_dicom_2->show();
	this->ui->view_dicom_3->show();
}

void StackedDensityAnalysis::selection2D() {

	//(ui->view_dicom_3)->GetRenderWindow()->AddRenderer(renderer_dicom_3);

	// Create an image
	drawing = vtkSmartPointer<vtkImageCanvasSource2D>::New();
	drawing->SetScalarTypeToUnsignedChar();
	drawing->SetNumberOfScalarComponents(3);
	drawing->SetExtent(0, 100, 0, 100, 0, 0);

	// Clear the image
	drawing->SetDrawColor(255, 0, 0);
	drawing->FillBox(0, 100, 0, 100);
	drawing->SetDrawColor(0, 0, 0);
	drawing->Update();

	logoRepresentation = vtkSmartPointer<vtkLogoRepresentation>::New();
	logoRepresentation->SetImage(drawing->GetOutput());
	logoRepresentation->SetPosition(0, 0);
	logoRepresentation->SetPosition2(.4, .4);
	logoRepresentation->GetImageProperty()->SetOpacity(0.5);

	logoWidget = vtkSmartPointer<vtkLogoWidget>::New();
	logoWidget->SetInteractor((ui->view_dicom_3)->GetRenderWindow()->GetInteractor());
	logoWidget->SetRepresentation(logoRepresentation);
	logoWidget->On();

	(ui->view_dicom_3)->GetRenderWindow()->Render();
	(ui->view_dicom_3)->show();


}

void StackedDensityAnalysis::init() {

	/*archivosVtk.push_back("../Resources/brain/1file.vtk");
	archivosVtk.push_back("../Resources/brain/crane.vtk");*/

	archivosVtk.push_back("../Resources/knee_mesh_region_1.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_2.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_3.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_4.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_5.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_6.vtk");
	archivosVtk.push_back("../Resources/knee_mesh_region_7.vtk");

	colores.push_back(QColor(255, 0, 0));
	colores.push_back(QColor(0, 0, 255));
	colores.push_back(QColor(0, 255,0));
	colores.push_back(QColor(255, 0, 255));
	colores.push_back(QColor(255, 255, 0));
	colores.push_back(QColor(255, 68, 173));
	colores.push_back(QColor(246, 36, 89));

	
	renderer = vtkSmartPointer<vtkRenderer>::New();
	
	for (register int i = 0; i <7; ++i) {
		mapper[i] = vtkSmartPointer<vtkDataSetMapper>::New();
		actor[i] = vtkSmartPointer<vtkActor>::New();
	}

	for (register int i = 0; i < 7; ++i){
		renderVTK(archivosVtk[i], *(ui->view_volum), colores[i], mapper[i], actor[i]);
	}

}


void StackedDensityAnalysis::renderVTK(QString vtkFilename, QVTKWidget &widgetvtk, QColor &color, vtkDataSetMapper* mapper, vtkActor* actor){
	
	visible = true;
	//opacity = 0.75;
	
	//vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
	reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
	reader->SetFileName(vtkFilename.toStdString().c_str());
	reader->Update();

	//vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	//mapper = vtkSmartPointer<vtkDataSetMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	//vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	//actor = vtkSmartPointer<vtkActor>::New();
	double r = color.red() / 255;
	double g = color.green() / 255;
	double b = color.blue() / 255;

	actor->GetProperty()->SetColor(r, g, b);
	actor->GetProperty()->SetOpacity(0.5);
	actor->SetMapper(mapper);
	
	/*QPalette pal;
	pal.setColor(QPalette::Button, color.rgb());
	ui->btn_color1->setAutoFillBackground(true);
	ui->btnColor_1->setPalette(pal);
	ui->btnColor_!->update();
*/
	//vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

	renderer->AddActor(actor);
	renderer->SetBackground(39 / 255, 40 / 255, 34 / 255);

	widgetvtk.GetRenderWindow()->AddRenderer(renderer);
	widgetvtk.show();

	/*ui->sldrOpacity->setMinimum(1);
	ui->sldrOpacity->setMaximum(100);
	ui->sldrOpacity->setValue(50);*/
}

void StackedDensityAnalysis::visibility1(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[1]->Update();
		actor[1]->VisibilityOff();
		renderer->AddActor(actor[1]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[1]->Update();
		actor[1]->VisibilityOn();
		renderer->AddActor(actor[1]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity1(int position) {

	mapper[1]->Update();
	actor[1]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[1]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority1(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[1]->Update();
	actor[1]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[1]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}


void StackedDensityAnalysis::visibility2(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[2]->Update();
		actor[2]->VisibilityOff();
		renderer->AddActor(actor[2]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[2]->Update();
		actor[2]->VisibilityOn();
		renderer->AddActor(actor[2]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity2(int position) {

	mapper[2]->Update();
	actor[2]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[2]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority2(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[2]->Update();
	actor[2]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[2]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}


void StackedDensityAnalysis::visibility3(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[3]->Update();
		actor[3]->VisibilityOff();
		renderer->AddActor(actor[3]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[3]->Update();
		actor[3]->VisibilityOn();
		renderer->AddActor(actor[3]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity3(int position) {

	mapper[3]->Update();
	actor[3]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[3]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority3(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[3]->Update();
	actor[3]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[3]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}


void StackedDensityAnalysis::visibility4(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[4]->Update();
		actor[4]->VisibilityOff();
		renderer->AddActor(actor[4]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[4]->Update();
		actor[4]->VisibilityOn();
		renderer->AddActor(actor[4]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity4(int position) {

	mapper[4]->Update();
	actor[4]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[4]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority4(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[4]->Update();
	actor[4]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[4]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}


void StackedDensityAnalysis::visibility5(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[5]->Update();
		actor[5]->VisibilityOff();
		renderer->AddActor(actor[5]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[5]->Update();
		actor[5]->VisibilityOn();
		renderer->AddActor(actor[5]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity5(int position) {

	mapper[5]->Update();
	actor[5]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[5]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority5(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[5]->Update();
	actor[5]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[5]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}


void StackedDensityAnalysis::visibility6(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[6]->Update();
		actor[6]->VisibilityOff();
		renderer->AddActor(actor[6]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[6]->Update();
		actor[6]->VisibilityOn();
		renderer->AddActor(actor[6]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity6(int position) {

	mapper[6]->Update();
	actor[6]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[6]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority6(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[6]->Update();
	actor[6]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[6]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}


void StackedDensityAnalysis::visibility7(bool* visible) {

	if (*visible == true) {
		*visible = false;
		mapper[0]->Update();
		actor[0]->VisibilityOff();
		renderer->AddActor(actor[0]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
	else {
		*visible = true;
		mapper[0]->Update();
		actor[0]->VisibilityOn();
		renderer->AddActor(actor[0]);

		(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
		(ui->view_volum)->GetRenderWindow()->Render();
		(ui->view_volum)->show();
	}
}

void StackedDensityAnalysis::opacity7(int position) {

	mapper[0]->Update();
	actor[0]->GetProperty()->SetOpacity(double(position) / 100);
	renderer->AddActor(actor[0]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

void StackedDensityAnalysis::colority7(QColor newColor) {

	double r = newColor.red() / 255;
	double g = newColor.green() / 255;
	double b = newColor.blue() / 255;

	mapper[0]->Update();
	actor[0]->GetProperty()->SetColor(r, g, b);
	renderer->AddActor(actor[0]);

	(ui->view_volum)->GetRenderWindow()->AddRenderer(renderer);
	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();
}

