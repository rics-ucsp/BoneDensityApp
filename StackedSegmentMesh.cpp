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
	QVTKWidgetRenderer::renderVTK("../Resources/knee_mesh_region_1.vtk", *(ui->stacked_segmentation_widget));
}

// void StackedConstructMesh::init() {

// 	archivosVtk.push_back("../Resources/knee_mesh_region_1.vtk");
// 	archivosVtk.push_back("../Resources/knee_mesh_region_2.vtk");
// 	archivosVtk.push_back("../Resources/knee_mesh_region_3.vtk");
// 	archivosVtk.push_back("../Resources/knee_mesh_region_4.vtk");
// 	archivosVtk.push_back("../Resources/knee_mesh_region_5.vtk");
// 	archivosVtk.push_back("../Resources/knee_mesh_region_6.vtk");
// 	archivosVtk.push_back("../Resources/knee_mesh_region_7.vtk");

// 	colores.push_back(QColor(255, 255, 0));
// 	colores.push_back(QColor(0, 255, 255));
// 	colores.push_back(QColor(255, 0, 255));
// 	colores.push_back(QColor(125, 0, 255));
// 	colores.push_back(QColor(255, 125, 255));
// 	colores.push_back(QColor(0, 0, 0));
// 	colores.push_back(QColor(255,255, 255));

	
// 	renderer = vtkSmartPointer<vtkRenderer>::New();
	
// 	for (register int i = 0; i <7; ++i) {
// 		mapper[i] = vtkSmartPointer<vtkDataSetMapper>::New();
// 		actor[i] = vtkSmartPointer<vtkActor>::New();
// 	}

// 	for (register int i = 0; i < 7; ++i){
// 		renderVTK(archivosVtk[i], *(ui->stacked_segmentation), colores[i], mapper[i], actor[i]);
// 	}

// }


// void StackedConstructMesh::renderVTK(QString vtkFilename, QVTKWidget &widgetvtk, QColor &color, vtkDataSetMapper* mapper, vtkActor* actor){
	
// 	visible = true;
// 	//opacity = 0.75;
	
// 	//vtkSmartPointer<vtkUnstructuredGridReader> reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
// 	reader = vtkSmartPointer<vtkUnstructuredGridReader>::New();
// 	reader->SetFileName(vtkFilename.toStdString().c_str());
// 	reader->Update();

// 	//vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
// 	//mapper = vtkSmartPointer<vtkDataSetMapper>::New();
// 	mapper->SetInputConnection(reader->GetOutputPort());

// 	//vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
// 	//actor = vtkSmartPointer<vtkActor>::New();
// 	double r = color.red() / 255;
// 	double g = color.green() / 255;
// 	double b = color.blue() / 255;

// 	actor->GetProperty()->SetColor(r, g, b);
// 	actor->GetProperty()->SetOpacity(0.5);
// 	actor->SetMapper(mapper);
	
// 	/*QPalette pal;
// 	pal.setColor(QPalette::Button, color.rgb());
// 	ui->btn_color1->setAutoFillBackground(true);
// 	ui->btnColor_1->setPalette(pal);
// 	ui->btnColor_!->update();
// */
// 	//vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

// 	renderer->AddActor(actor);
// 	renderer->SetBackground(39 / 255, 40 / 255, 34 / 255);

// 	widgetvtk.GetRenderWindow()->AddRenderer(renderer);
// 	widgetvtk.show();

// 	/*ui->sldrOpacity->setMinimum(1);
// 	ui->sldrOpacity->setMaximum(100);
// 	ui->sldrOpacity->setValue(50);*/
// }