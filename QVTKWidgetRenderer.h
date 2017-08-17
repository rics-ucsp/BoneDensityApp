#ifndef QVTKWIDGETRENDERER_H
#define QVTKWIDGETRENDERER_H

#include <QVTKWidget.h>

#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>

#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkLookupTable.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>

class QVTKWidgetRenderer{
public:
    static void renderVTK(std::string vtkFilename, QVTKWidget & widget, float opacity, const float color[3], const float background[3] ){
        vtkSmartPointer<vtkUnstructuredGridReader> reader   = vtkSmartPointer<vtkUnstructuredGridReader>::New();
        reader->SetFileName(vtkFilename.c_str());
        reader->Update();
    
        vtkSmartPointer<vtkDataSetMapper> mapper    =	vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputConnection(reader->GetOutputPort());
      
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->GetProperty()->SetColor(color[0],color[1], color[2]);
        actor->GetProperty()->SetOpacity(opacity);
        actor->SetMapper(mapper);
        
        vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(actor);
        renderer->SetBackground(background[0], background[1], background[2]);
    
        widget.GetRenderWindow()->AddRenderer(renderer);
        widget.show();
    }

    static void renderColoredVTK(std::string vtkFilename, QVTKWidget & widget ){
        vtkSmartPointer<vtkUnstructuredGridReader> reader   = vtkSmartPointer<vtkUnstructuredGridReader>::New();
        reader->SetFileName(vtkFilename.c_str());
        reader->Update();
    
        vtkSmartPointer<vtkDataSetMapper> mapper    =	vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputConnection(reader->GetOutputPort());
		
		double bounds[6];
		reader->GetOutput()->GetBounds(bounds);

		double minBoxPoint[3];
		double maxBoxPoint[3];
		minBoxPoint[0] = (bounds[1] - bounds[0]) / 2.0 + bounds[0];
		minBoxPoint[1] = (bounds[3] - bounds[2]) / 2.0 + bounds[2];
		minBoxPoint[2] = (bounds[5] - bounds[4]) / 2.0 + bounds[4];
		maxBoxPoint[0] = bounds[1];
		maxBoxPoint[1] = bounds[3];
		maxBoxPoint[2] = bounds[5];

		vtkSmartPointer<vtkLookupTable> lut1 = vtkSmartPointer<vtkLookupTable>::New();
		lut1->SetHueRange(0, .667);

		mapper->SetScalarRange(reader->GetOutput()->GetScalarRange());
		mapper->SetLookupTable(lut1);
        mapper->SetColorModeToMapScalars();
              
        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->GetProperty()->SetColor(1, 1, 1);
        actor->GetProperty()->SetOpacity(0.05);
        actor->SetMapper(mapper);
        
        vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(actor);
        renderer->SetBackground(0, 0,0);
    
        widget.GetRenderWindow()->AddRenderer(renderer);
		renderer->Render();
        widget.show();
    }

    static void renderCube(QVTKWidget & widget){
        vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
        cubeSource->Update();

        vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
        
        vtkSmartPointer<vtkActor> cubeActor =  vtkSmartPointer<vtkActor>::New();
        cubeActor->SetMapper(cubeMapper);
        
        vtkSmartPointer<vtkRenderer> rightRenderer = vtkSmartPointer<vtkRenderer>::New();
        rightRenderer->AddActor(cubeActor);
        
        widget.GetRenderWindow()->AddRenderer(rightRenderer);
        widget.show();
    }

};

#endif // QVTKWIDGETRENDERER_H
