#include<iostream>

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



class vtkResliceCursorCallback : public vtkCommand
{
public:
	static vtkResliceCursorCallback *New()
	{
		return new vtkResliceCursorCallback;
	}

	void Execute(vtkObject *caller, unsigned long ev,
		void *callData)
	{

		if (ev == vtkResliceCursorWidget::WindowLevelEvent ||
			ev == vtkCommand::WindowLevelEvent ||
			ev == vtkResliceCursorWidget::ResliceThicknessChangedEvent)
		{
			// Render everything
			for (int i = 0; i < 3; i++)
			{
				this->RCW[i]->Render();
			}
			this->IPW[0]->GetInteractor()->GetRenderWindow()->Render();
			return;
		}

		vtkImagePlaneWidget* ipw =
			dynamic_cast< vtkImagePlaneWidget* >(caller);
		if (ipw)
		{
			double* wl = static_cast<double*>(callData);

			if (ipw == this->IPW[0])
			{
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			}
			else if (ipw == this->IPW[1])
			{
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[2]->SetWindowLevel(wl[0], wl[1], 1);
			}
			else if (ipw == this->IPW[2])
			{
				this->IPW[0]->SetWindowLevel(wl[0], wl[1], 1);
				this->IPW[1]->SetWindowLevel(wl[0], wl[1], 1);
			}
		}

		vtkResliceCursorWidget *rcw = dynamic_cast<
			vtkResliceCursorWidget * >(caller);
		if (rcw)
		{
			vtkResliceCursorLineRepresentation *rep = dynamic_cast<
				vtkResliceCursorLineRepresentation * >(rcw->GetRepresentation());
			// Although the return value is not used, we keep the get calls
			// in case they had side-effects
			rep->GetResliceCursorActor()->GetCursorAlgorithm()->GetResliceCursor();
			for (int i = 0; i < 3; i++)
			{
				vtkPlaneSource *ps = static_cast< vtkPlaneSource * >(
					this->IPW[i]->GetPolyDataAlgorithm());
				ps->SetOrigin(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetOrigin());
				ps->SetPoint1(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint1());
				ps->SetPoint2(this->RCW[i]->GetResliceCursorRepresentation()->
					GetPlaneSource()->GetPoint2());

				// If the reslice plane has modified, update it on the 3D widget
				this->IPW[i]->UpdatePlacement();
			}
		}

		// Render everything
		for (int i = 0; i < 3; i++)
		{
			this->RCW[i]->Render();
		}
		this->IPW[0]->GetInteractor()->GetRenderWindow()->Render();
	}

	vtkResliceCursorCallback() {}
	vtkImagePlaneWidget* IPW[3];
	vtkResliceCursorWidget *RCW[3];
};

StackedMultiplanarReconstruction::StackedMultiplanarReconstruction(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StackedMultiplanarReconstruction)
{
	ui->setupUi(this);

	connect(this->ui->scroll_axial, &QScrollBar::valueChanged, this, &StackedMultiplanarReconstruction::update_scroll_axial);
	connect(this->ui->scroll_sagittal, &QScrollBar::valueChanged, this, &StackedMultiplanarReconstruction::update_scroll_sagittal);
	connect(this->ui->scroll_coronal, &QScrollBar::valueChanged, this, &StackedMultiplanarReconstruction::update_scroll_coronal);
}

StackedMultiplanarReconstruction::~StackedMultiplanarReconstruction(){
	delete ui;
}

void StackedMultiplanarReconstruction::multiplanar_reconstruction(std::string filename){
	/*QMessageBox Msgbox;
	Msgbox.setText(QString::fromStdString(filename));
	Msgbox.exec();*/

	vtkSmartPointer<vtkJPEGReader> reader =		vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetDataByteOrderToLittleEndian();
	//		jpegReader->SetFilePattern("");
	//reader->SetFilePrefix("C:/Users/Fil/Desktop/jpg-knee");
	reader->SetFilePrefix("D:/knee-jpg");
	//reader->SetDataSpacing(3.2, 3.2, 20);
	//reader->SetDataSpacing(40, 40, 40);
	reader->SetFilePattern("%s/CT-Knee.379x229x305_%03d.jpg");
	reader->SetDataExtent(0, 379, 0, 229, 0, 304);

	/*vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
	reader->SetDirectoryName(filename.c_str());*/

	reader->Update();
	int imageDims[3];
	reader->GetOutput()->GetDimensions(imageDims);

	for (int i = 0; i < 3; i++) 
		riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();

	this->ui->view1->SetRenderWindow(riw[2]->GetRenderWindow());
	riw[2]->SetupInteractor(this->ui->view1->GetRenderWindow()->GetInteractor());

	this->ui->view2->SetRenderWindow(riw[0]->GetRenderWindow());
	riw[0]->SetupInteractor(this->ui->view2->GetRenderWindow()->GetInteractor());

	this->ui->view3->SetRenderWindow(riw[1]->GetRenderWindow());
	riw[1]->SetupInteractor(this->ui->view3->GetRenderWindow()->GetInteractor());

	std::vector<std::pair<int, int>> bounds(3, std::make_pair(0, 0));

	for (int i = 0; i < 3; i++) {
		vtkResliceCursorLineRepresentation *rep = vtkResliceCursorLineRepresentation::SafeDownCast(riw[i]->GetResliceCursorWidget()->GetRepresentation());
		riw[i]->SetResliceCursor(riw[i]->GetResliceCursor());
		rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(i);

		riw[i]->SetInputData(reader->GetOutput());
		riw[i]->SetSliceOrientation(i);
		riw[i]->SetResliceModeToAxisAligned();
		riw[i]->GetRenderer()->SetBackground(1, 0, 0);

		/*int axis = this->riw[i]->GetSliceOrientation();
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
		riw[i]->GetRenderer()->ResetCameraClippingRange();*/


		//this->riw[i]->Render();

		bounds[i].first = riw[i]->GetSliceMin();
		bounds[i].second = riw[i]->GetSliceMax();

		riw[i]->SetColorLevel(80);//127.5 //10
		riw[i]->SetColorWindow(240);//255 // 255

		riw[i]->GetRenderer()->ResetCamera();
		riw[i]->SliceScrollOnMouseWheelOff();
	}

	ui->scroll_axial->setMinimum(bounds[2].first);
	ui->scroll_axial->setMaximum(bounds[2].second);
	ui->scroll_sagittal->setMinimum(bounds[0].first);
	ui->scroll_sagittal->setMaximum(bounds[0].second);
	ui->scroll_coronal->setMinimum(bounds[1].first);
	ui->scroll_coronal->setMaximum(bounds[1].second);

	vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
	picker->SetTolerance(0.005);

	vtkSmartPointer<vtkProperty> ipwProp = vtkSmartPointer<vtkProperty>::New();
	ren = vtkSmartPointer< vtkRenderer >::New();

	this->ui->view4->GetRenderWindow()->AddRenderer(ren);
	vtkRenderWindowInteractor *iren = this->ui->view4->GetInteractor();

	for (int i = 0; i < 3; i++) {
		planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
		planeWidget[i]->SetInteractor(iren);
		planeWidget[i]->SetPicker(picker);
		planeWidget[i]->RestrictPlaneToVolumeOn();
		double color[3] = { 0, 0, 0 };
		color[i] = 1;
		planeWidget[i]->GetPlaneProperty()->SetColor(color);

		color[0] /= 2.0;
		color[1] /= 2.0;
		color[2] /= 2.0;
		riw[i]->GetRenderer()->SetBackground(color);

		planeWidget[i]->SetTexturePlaneProperty(ipwProp);
		planeWidget[i]->TextureInterpolateOff();
		planeWidget[i]->SetResliceInterpolateToLinear();
		planeWidget[i]->SetInputConnection(reader->GetOutputPort());
		planeWidget[i]->SetPlaneOrientation(i);

		//planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
		planeWidget[i]->SetSliceIndex(bounds[i].first);

		planeWidget[i]->DisplayTextOn();
		planeWidget[i]->SetDefaultRenderer(ren);
		planeWidget[i]->SetWindowLevel(1358, -27);
		planeWidget[i]->On();
		planeWidget[i]->InteractionOn();
	}

	vtkSmartPointer<vtkResliceCursorCallback> cbk = vtkSmartPointer<vtkResliceCursorCallback>::New();
	for (int i = 0; i < 3; i++) {
		cbk->IPW[i] = planeWidget[i];
		cbk->RCW[i] = riw[i]->GetResliceCursorWidget();
		riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent, cbk);
		riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::WindowLevelEvent, cbk);
		riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceThicknessChangedEvent, cbk);
		riw[i]->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResetCursorEvent, cbk);
		riw[i]->GetInteractorStyle()->AddObserver(vtkCommand::WindowLevelEvent, cbk);
		// Make them all share the same color map.
		riw[i]->SetLookupTable(riw[0]->GetLookupTable());
		planeWidget[i]->GetColorMap()->SetLookupTable(riw[0]->GetLookupTable());
		//planeWidget[i]->GetColorMap()->SetInput(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap()->GetInput());
		planeWidget[i]->SetColorMap(riw[i]->GetResliceCursorWidget()->GetResliceCursorRepresentation()->GetColorMap());
	}

	volume_rendering(reader);
	this->ui->view1->show();
	this->ui->view2->show();
	this->ui->view3->show();
}

void StackedMultiplanarReconstruction::update_scroll_axial() {
	int _Slice;
	_Slice = ui->scroll_axial->value();
	riw[2]->SetSlice(_Slice);
	riw[2]->Render();
	planeWidget[2]->SetSliceIndex(_Slice);
	this->ui->view4->GetInteractor()->Render();
}

void StackedMultiplanarReconstruction::update_scroll_sagittal() {
	int _Slice;
	_Slice = ui->scroll_sagittal->value();
	riw[0]->SetSlice(_Slice);
	riw[0]->Render();
	planeWidget[0]->SetSliceIndex(_Slice);
	this->ui->view4->GetInteractor()->Render();
}

void StackedMultiplanarReconstruction::update_scroll_coronal() {
	int _Slice;
	_Slice = ui->scroll_coronal->value();
	riw[1]->SetSlice(_Slice);
	riw[1]->Render();
	planeWidget[1]->SetSliceIndex(_Slice);
	this->ui->view4->GetInteractor()->Render();
}

void StackedMultiplanarReconstruction::volume_rendering(vtkSmartPointer<vtkJPEGReader> &reader) {
	vtkSmartPointer<vtkImageData> volumeData = vtkSmartPointer<vtkImageData>::New();
	volumeData->DeepCopy(reader->GetOutput());

	// Ray cast data
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	volumeMapper->SetInputData(volumeData);

	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();

	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	//compositeOpacity->AddPoint(0.0, 0.1);
	//compositeOpacity->AddPoint(80.0, 0.2);
	//compositeOpacity->AddPoint(255.0, 0.1);

	compositeOpacity->AddPoint(0.0, 0.0);
	compositeOpacity->AddPoint(255, 1.0);

	/*compositeOpacity->AddPoint(-3024, 0, 0.5, 0.0);
	compositeOpacity->AddPoint(-1000, 0, 0.5, 0.0);
	compositeOpacity->AddPoint(-500, 1.0, 0.33, 0.45);
	compositeOpacity->AddPoint(3071, 1.0, 0.5, 0.0);*/
	//compositeOpacity->AddPoint(255, 1.0);

	volumeProperty->SetScalarOpacity(compositeOpacity);

	vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
	color->AddRGBPoint(0.0, 0.0, 0.0, 1.0);
	color->AddRGBPoint(40.0, 1.0, 0.0, 0.0);
	color->AddRGBPoint(250, 1.0, 1.0, 1.0);

	/*color->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
	color->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);
	color->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
	color->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);*/
	volumeProperty->SetColor(color);



	/*volumeProperty->ShadeOn();
	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);
	volumeProperty->SetScalarOpacityUnitDistance(0.8919);*/

	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	

	// VTK Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(0.0f, 0.0f, 0.0f);

	ren->AddViewProp(volume);
	vtkCamera *camera = ren->GetActiveCamera();
	double *c = volume->GetCenter();
	camera->SetFocalPoint(c[0], c[1], c[2]);
	//camera->SetPosition(c[0], c[1] + riw[1]->GetSliceMax() / 2 + 300, c[2]);
	camera->SetPosition(c[0], c[1] + riw[1]->GetSliceMax() + 600, c[2]);


	//camera->SetPosition(c[0], c[1] + riw[1]->GetSliceMax(), c[2]);

	//camera->SetViewUp(0, 0, -1);

	camera->SetViewUp(0, 0, 1);

	this->ui->view4->GetRenderWindow()->Render();
}
