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
	void renderVTK(QString vtkFilename, QVTKWidget &widgetvtk, QColor& color);
	//void visibility(Ui::PageDensityAnalysis *);
	void visibility(bool*);

private:
    Ui::StackedDensityAnalysis *ui;

	
	QVector<QString> archivosVtk;
	QVector<QColor> colores;
	
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkUnstructuredGridReader> reader;
	vtkSmartPointer<vtkDataSetMapper> mapper;
	vtkSmartPointer<vtkActor> actor;

	bool visible;
	float opacity;

};

#endif // STACKEDDENSITYANALYSIS_H
