#ifndef STACKEDDENSITYANALYSIS_H
#define STACKEDDENSITYANALYSIS_H

#include <QWidget>
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <QVTKWidget.h>
#include "PageDensityAnalysis.h"
#include <QColorDialog>

#include <vtkJPEGReader.h>
#include "vtkResliceImageViewer.h"
#include "vtkImagePlaneWidget.h"

//para 2d selection

#include <vtkImageCanvasSource2D.h>
#include <vtkLogoRepresentation.h>
#include <vtkLogoWidget.h>
#include <vtkProperty2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>


namespace Ui {
class StackedDensityAnalysis;
}

class StackedDensityAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit StackedDensityAnalysis(QWidget *parent = 0);
    ~StackedDensityAnalysis();
	void init();
	void renderVTK(QString vtkFilename, QVTKWidget &widgetvtk, QColor& color, vtkDataSetMapper* mapper, vtkActor* actor);
	//void visibility(Ui::PageDensityAnalysis *);
	void multiplanar_reconstruction(std::string filename);

	void selection2D();

	void visibility1(bool*);
	void opacity1(int);
	void colority1(QColor);

	void visibility2(bool*);
	void opacity2(int);
	void colority2(QColor);

	void visibility3(bool*);
	void opacity3(int);
	void colority3(QColor);

	void visibility4(bool*);
	void opacity4(int);
	void colority4(QColor);

	void visibility5(bool*);
	void opacity5(int);
	void colority5(QColor);

	void visibility6(bool*);
	void opacity6(int);
	void colority6(QColor);

	void visibility7(bool*);
	void opacity7(int);
	void colority7(QColor);

private:
    Ui::StackedDensityAnalysis *ui;

protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[3];
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[3];
	
	QVector<QString> archivosVtk;
	QVector<QColor> colores;
	
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkUnstructuredGridReader> reader;
	
	
	vtkSmartPointer<vtkDataSetMapper> mapper[7];
	vtkSmartPointer<vtkActor> actor[7];

	
	vtkSmartPointer<vtkRenderer> renderer_dicom_3;
	vtkSmartPointer<vtkImageCanvasSource2D> drawing;
	vtkSmartPointer<vtkLogoRepresentation> logoRepresentation;
	vtkSmartPointer<vtkLogoWidget> logoWidget;


/*
	vtkSmartPointer<vtkDataSetMapper> mapper2;
	vtkSmartPointer<vtkActor> actor2;

	vtkSmartPointer<vtkDataSetMapper> mapper3;
	vtkSmartPointer<vtkActor> actor3;

	vtkSmartPointer<vtkDataSetMapper> mapper4;
	vtkSmartPointer<vtkActor> actor4;

	vtkSmartPointer<vtkDataSetMapper> mapper5;
	vtkSmartPointer<vtkActor> actor5;

	vtkSmartPointer<vtkDataSetMapper> mapper6;
	vtkSmartPointer<vtkActor> actor6;

	vtkSmartPointer<vtkDataSetMapper> mapper7;
	vtkSmartPointer<vtkActor> actor7;*/

	bool visible;
	

};

#endif // STACKEDDENSITYANALYSIS_H
