#ifndef STACKEDSEGMENTMESH_H
#define STACKEDSEGMENTMESH_H

#include <QWidget>
#include "QVTKWidgetRenderer.h"

namespace Ui {
	class StackedSegmentMesh;
}

class StackedSegmentMesh : public QWidget
{
	Q_OBJECT

public:
	explicit StackedSegmentMesh(QWidget *parent = 0);
	~StackedSegmentMesh();

	void segmentMesh();
	void init();
	void renderVTK(QString vtkFilename, QVTKWidget &widgetvtk, QColor &color, vtkDataSetMapper* mapper, vtkActor* actor);
private:
	Ui::StackedSegmentMesh *ui;
protected:
	QVector<QString> archivosVtk;
	QVector<QColor> colores;

	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkUnstructuredGridReader> reader;


	vtkSmartPointer<vtkDataSetMapper> mapper[7];
	vtkSmartPointer<vtkActor> actor[7];
};

#endif // STACKEDSEGMENTMESH_H
