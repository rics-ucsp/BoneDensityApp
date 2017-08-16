

#ifndef STACKCEDMULTIPLANARRECONSTRUCTION_H
#define STACKCEDMULTIPLANARRECONSTRUCTION_H

#include "vtkSmartPointer.h"
#include "vtkDICOMImageReader.h"
#include "vtkResliceImageViewer.h"
#include "vtkImagePlaneWidget.h"

#include <QWidget>
#include <string>

namespace Ui {
	class StackedMultiplanarReconstruction;
}

class StackedMultiplanarReconstruction : public QWidget
{
	Q_OBJECT

public:
	explicit StackedMultiplanarReconstruction(QWidget *parent = 0);
	~StackedMultiplanarReconstruction();

	void multiplanar_reconstruction(std::string filename);

private slots:
	void update_scroll_axial();
	void update_scroll_sagittal();
	void update_scroll_coronal();
	void volume_rendering(vtkSmartPointer<vtkDICOMImageReader> &reader);

protected:
	vtkSmartPointer< vtkResliceImageViewer > riw[3];
	vtkSmartPointer< vtkRenderer > ren;
	vtkSmartPointer< vtkImagePlaneWidget > planeWidget[3];

private:
	Ui::StackedMultiplanarReconstruction *ui;
};


#endif