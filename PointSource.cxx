#include "vtkPointSource.h"
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include "vtkPLYReaderLocal.h"

int main ( int argc, char *argv[] )
{
  if(argc != 2)
  {
    std::cout << "Usage: " << argv[0] << "  Filename(.ply)" << std::endl;
    return EXIT_FAILURE;
  }
  vtkSmartPointer<vtkPointSource> pointSource =
  vtkSmartPointer<vtkPointSource>::New();
  pointSource->SetCenter(0.0, 0.0, 0.0);
  pointSource->SetNumberOfPoints(50);
  pointSource->SetRadius(5.0);
  pointSource->Update();
  
  std::string inputFilename = argv[1];
  
  vtkSmartPointer<vtkPLYReaderLocal> reader =
  vtkSmartPointer<vtkPLYReaderLocal>::New();
  
  if (reader->CanReadFile(inputFilename.c_str()))
  {
    reader->SetFileName ( inputFilename.c_str() );
    reader->Update();
    //vtkPolyData* polyData = reader->GetPolyData();
    
    vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(reader->GetOutputPort());
    mapper->Update();
    vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    
    vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    
    renderer->AddActor(actor);
    renderer->SetBackground(0.1804,0.5451,0.3412); // Sea green
    
    renderWindow->Render();
    renderWindowInteractor->Start();
    
  }
    
  return EXIT_SUCCESS;
}
