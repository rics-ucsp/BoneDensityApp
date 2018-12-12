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
#include <vtkImageActor.h>
#include <vtkTextActor.h>


#include <chrono> ////_sleep(00);
//glcm libs
#include <iostream>
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;
#include "glcm/AppGlcm.h"


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
	readerJPG->SetFilePrefix("D:/knee-jpg"); 
	
	readerJPG->SetFilePattern("%s/CT-Knee.379x229x305_%03d.jpg");		   
	readerJPG->SetDataExtent(0, 379, 0, 229, 0, 305);

	readerJPG->Update();
	int imageDims[3];
	readerJPG->GetOutput()->GetDimensions(imageDims);

	for (int i = 0; i < 3; i++)
		riw[i] = vtkSmartPointer< vtkResliceImageViewer >::New();

	/*this->ui->view_dicom_1->SetRenderWindow(riw[2]->GetRenderWindow());
	riw[2]->SetupInteractor(this->ui->view_dicom_1->GetRenderWindow()->GetInteractor());

	this->ui->view_dicom_2->SetRenderWindow(riw[0]->GetRenderWindow());
	riw[0]->SetupInteractor(this->ui->view_dicom_2->GetRenderWindow()->GetInteractor());

	this->ui->view_dicom_3->SetRenderWindow(riw[1]->GetRenderWindow());
	riw[1]->SetupInteractor(this->ui->view_dicom_3->GetRenderWindow()->GetInteractor());*/

	std::vector<std::pair<int, int>> bounds(3, std::make_pair(0, 0));

	/*
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
		
	*/
	//volume_rendering(reader);

	/*this->ui->view_dicom_1->show();
	this->ui->view_dicom_2->show();
	this->ui->view_dicom_3->show();
	*/

	

}

void StackedDensityAnalysis::selection2D() {

	/*

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
	(ui->view_dicom_3)->show();*/

	/*string inputFilename = "D:/prueba/BoneDensityApp/build/Debug/0.jpg";
	readerJPG2 = vtkSmartPointer<vtkJPEGReader>::New();
	readerJPG2->SetFileName(inputFilename.c_str());
	readerJPG2->Update();

	int extent[6];
	readerJPG2->GetOutput()->GetExtent(extent);

	imageActor = vtkSmartPointer<vtkImageActor>::New();
	imageActor->GetMapper()->SetInputConnection(readerJPG2->GetOutputPort());

	renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> interactor = (ui->view_dicom_2)->GetRenderWindow()->GetInteractor();
	vtkSmartPointer<vtkInteractorStyleImage> style = vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor->SetInteractorStyle(style);

	borderWidget = vtkSmartPointer<vtkBorderWidget>::New();
	//borderWidget->SetInteractor((ui->view_dicom_2)->GetRenderWindow()->GetInteractor());
	borderWidget->SetInteractor(interactor);

	static_cast<vtkBorderRepresentation*>  (borderWidget->GetRepresentation())->GetBorderProperty()->SetColor(0, 1, 0);
	static_cast<vtkBorderRepresentation*>  (borderWidget->GetRepresentation())->SetPosition(0.5, 0.5);
	static_cast<vtkBorderRepresentation*>  (borderWidget->GetRepresentation())->SetPosition2(.1, .1);

	borderWidget->SelectableOff();
	//(ui->view_dicom_2)->GetRenderWindow()->GetInteractor()->SetRenderWindow(renderWindow);
	interactor->SetRenderWindow(renderWindow);
	//this->ui->view_dicom_2->SetRenderWindow(renderWindow);

	leftRenderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(leftRenderer);
	leftRenderer->AddActor(imageActor);
	//leftRenderer->ResetCamera();

	borderCallback = vtkSmartPointer<vtkBorderCallback2>::New();
	borderCallback->SetLeftRenderer(leftRenderer);
	borderWidget->AddObserver(vtkCommand::InteractionEvent, borderCallback);

	(ui->view_dicom_2)->GetRenderWindow()->Render();
	borderWidget->On();
	(ui->view_dicom_2)->show();
	*/
	

}

void StackedDensityAnalysis::analisisTemplate(string name) {
	AppGlcm* app = getApplication();
	app->setNumClass(2);/// tipo de calsificacion: Binaria: 2 clases
	app->setNameBD(name);
	app->setNameResults("out1.txt");
	app->initProcessing(10, 12, 8);
	app->offLineProcessing();
	std::vector<double> resultVector;
	std::vector<string> resultVectorNames;
	app->endProcessing(resultVector, resultVectorNames);

	for (int i = 0; i < resultVector.size(); ++i) {
		string key = resultVectorNames[i];
		double value = resultVector[i];
		cout << key << ":";
		cout << value << endl;
	}


	double Energy_ = resultVector[0];
	double Maximun_ = resultVector[1];
	double Disimilarity_ = resultVector[2];
	double Contrast_ = resultVector[3];
	double Homogeneity_ = resultVector[4];
	double Correlation_ = resultVector[5];
	double Entropy_ = resultVector[6] / 4;

	QString Energy;				Energy += "  1:  Energy			: "; Energy += QString::number(Energy_); Energy += "\n";
	QString Maximun;			Maximun += "  2:  Maximun			: "; Maximun += QString::number(Maximun_); Maximun += "\n";
	QString Disimilarity;		Disimilarity += "  3:  Disimilarity		: "; Disimilarity += QString::number(Disimilarity_); Disimilarity += "\n";
	QString Contrast;			Contrast += "  4:  Contrast			: "; Contrast += QString::number(Contrast_); Contrast += "\n";
	QString Homog;				Homog += "  5:  Homogeneity		: "; Homog += QString::number(Homogeneity_); Homog += "\n";
	QString Correlation;		Correlation += "  6:  Correlation		: "; Correlation += QString::number(Correlation_); Correlation += "\n";
	QString Entropy;			Entropy += "  7:  Entropy			: "; Entropy += QString::number(Entropy_); Entropy += "\n";


	double final_value = (Energy_ + Maximun_ + Contrast_ + Entropy_) / 4;
	cout << "final:" << final_value << endl;
	QString diagnost;

	if (final_value < 1 && final_value > 0.55) {
		diagnost = "Densidad Mineral Osea Normal";
	}
	if (final_value < 0.55 && final_value > 0.33) {
		diagnost = "Osteopenia";
	}
	if (final_value < 0.33 && final_value > 0.22) {
		diagnost = "Osteoporosis Leve";
	}
	if (final_value < 0.22 && final_value > 0.11) {
		diagnost = "Osteoporosis Moderada ";
	}
	if (final_value < 0.11 && final_value > 0) {
		diagnost = "Osteoporosis Severa";
	}
	



	QMessageBox messageBox;
	messageBox.setText("Analisis Realizado:\n ---------------------------------------------------------\n");
	messageBox.setBaseSize(QSize(450, 120));
	messageBox.setDetailedText(Energy + Maximun + Disimilarity + Contrast + Homog + Correlation + Entropy + "\n----------------------------------\n" + "Densidad Mineral Osea	:" + QString::number(final_value) + "\n" + "Resultado		:"+diagnost);

	QAbstractButton * detailsButton = NULL;

	foreach(QAbstractButton *button, messageBox.buttons()) {
		if (messageBox.buttonRole(button) == QMessageBox::ActionRole) {
			detailsButton = button;
			break;

		}

	}
	QList<QTextEdit*> textBoxes = messageBox.findChildren<QTextEdit*>();
	if (textBoxes.size())
		textBoxes[0]->setFixedSize(600, 200);

	// If we have found the details button, then click it to expand the
	// details area.
	if (detailsButton) {
		detailsButton->click();

	}
	messageBox.exec();
}

void StackedDensityAnalysis::analisis2D() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (1).data");
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
	vtkSmartPointer<vtkTextActor> textActor =
		vtkSmartPointer<vtkTextActor>::New();
	textActor->SetInput("Criterios de Densidad Osea:");
	textActor->SetPosition(10, 670);
	textActor->GetTextProperty()->SetFontSize(14);
	textActor->GetTextProperty()->SetColor(0.6, 1.0, 0.4);
	renderer->AddActor2D(textActor);

	vtkSmartPointer<vtkTextActor> textActor2 =
		vtkSmartPointer<vtkTextActor>::New();
	textActor2->SetInput(" [1.00 -> 0.55] Densidad Normal\n [0.55 -> 0.33] Osteopenia\n [0.33 -> 0.22] Osteoporosis Leve\n [0.22 -> 0.11] Osteoporosis Moderada \n [0.11 -> 0.00] Osteoporosis Severa");
	textActor2->SetPosition(10, 590);
	textActor2->GetTextProperty()->SetFontSize(14);
	textActor2->GetTextProperty()->SetColor(1.0, 1.0, 1.0);
	renderer->AddActor2D(textActor2);

	(ui->view_volum)->GetRenderWindow()->Render();
	(ui->view_volum)->show();

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

void StackedDensityAnalysis::analisis1() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (1).data");
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
void StackedDensityAnalysis::analisis2() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (2).data");
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
void StackedDensityAnalysis::analisis3() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (3).data");
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
void StackedDensityAnalysis::analisis4() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (4).data");
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
void StackedDensityAnalysis::analisis5() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (5).data");
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
void StackedDensityAnalysis::analisis6() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (6).data");
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
void StackedDensityAnalysis::analisis7() {
	analisisTemplate("D:/prueba/BoneDensityApp/build/Debug/in (7).data");
}

