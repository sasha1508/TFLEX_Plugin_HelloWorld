#include "Plugin.h"
#include <list>
using namespace TFlex::Model::Model3D;
using namespace TFlex::Model::Model2D;


HelloPlugin::HelloPlugin(PluginFactory^ factory) : Plugin(factory)
{}

void HelloPlugin::OnInitialize()
{
	Plugin::OnInitialize();
}

void HelloPlugin::OnCreateTools()
{
	Plugin::OnCreateTools();

	RegisterCommand(1, "Построить контур");
	TFlex::Application::ActiveMainWindow->InsertPluginMenuItem(1,
		"Плагин", MainWindow::InsertMenuPosition::EndOfTools, this);

	TFlex::Menu^ submenu = gcnew TFlex::Menu();
	submenu->CreatePopup();
	submenu->Append(1, "Плагин", this);

	TFlex::Application::ActiveMainWindow->InsertPluginSubMenu("Плагин", submenu, MainWindow::InsertMenuPosition::PluginSamples, this);

	TFlex::RibbonGroup^ ribbonGroup = TFlex::RibbonBar::ApplicationsTab->AddGroup("Плагин");
	ribbonGroup->AddButton(1, this);

	array<int>^ cmdIDs = gcnew array<int> { 1 };
	CreateToolbar("Плагин", cmdIDs);
	CreateMainBarPanel("Плагин", cmdIDs, this->ID, true);

	if (TFlex::Application::ActiveDocument != nullptr)
		TFlex::Application::ActiveDocument->AttachPlugin(this);
}

void HelloPlugin::OnCommand(Document^ document, int id)
{
	switch (id)
	{
	case 1:
		//MessageBox::Show("Hello World.");
		Start();
		break;
	}
}

void HelloPlugin::Start()
{
	DialogResult result = MessageBox::Show("Будет построен замкнутый контур", "Построение замкнутого контура", MessageBoxButtons::OKCancel);
	if (result == DialogResult::OK)
	{
		Document^ doc = TFlex::Application::ActiveDocument;
		if (doc != nullptr)
		{
			////Отображаем имя открытого документа:
			//String^ FileName = doc->FileName;
			//MessageBox::Show(FileName);

			//doc->Objects;

			TFlex::Model::ObjectContainer^ points = doc->Nodes3D;   //получаем список всех 3D узлов
			TFlex::Model::ObjectContainer^ paths3D = doc->Paths3D;   //получаем список всех 3D путей

			OnSurfacePoint^ point_0 = (OnSurfacePoint^)doc->GetObjectByName("3D Узел_9");  //получаем исходную точку по имени
			Path3D^ Path3D_0 = (Path3D^)doc->GetObjectByName("3D Путь_7");  //получаем 3D-Путь по имени
			TFlex::Model::Model3D::Geometry::ModelSurface^ surface_0 = point_0->Surface;  //получаем поверхность, на которой расположена точка
			

			for each (Object^ point in points)
				MessageBox::Show(((TFlex::Model::Model3D::Node3D^)point)->DisplayName, "Перечисляем точки");
			

			MessageBox::Show(surface_0->Owner->DisplayName + " / " + Path3D_0->DisplayName, point_0->DisplayName);
			

			for each (Object ^ path3D in paths3D)
				MessageBox::Show(((TFlex::Model::Model3D::Path3D^)path3D)->DisplayName, "Перечисляем 3D пути");
			
			//TFlex::StatusBar::Command = "";
			


			doc->BeginChanges("Профиль по штриховке");//Открытие блока изменений документа

			//создание узлов        
			CoordinateNode3D^ fn1 = gcnew CoordinateNode3D(doc);
			fn1->X = 10;
			fn1->Y = 10;
			fn1->Z = 10;
			FreeNode^ fn2 = gcnew FreeNode(doc, 40, 30);
			FreeNode^ fn3 = gcnew FreeNode(doc, 70, 10);

			//создание линий, проходящих через эти узлы        
		//	ConstructionOutline^ l1 = gcnew ConstructionOutline(doc, fn1, fn2);
			ConstructionOutline^ l2 = gcnew ConstructionOutline(doc, fn2, fn3);
		//	ConstructionOutline^ l3 = gcnew ConstructionOutline(doc, fn3, fn1);

			//рабочая плоскость(вид слева), на которой будет построен профиль        
			StandardWorkplane^ swp = gcnew StandardWorkplane(doc, StandardWorkplane::StandardType::Left);
			SketchProfile^ sp = gcnew SketchProfile(doc);
			sp->WorkSurface = swp;

			doc->EndChanges();//Закрытие блока изменений документа

			Copy3DPath(doc, paths3D);



			//Открываем блок изменения документа
			doc->BeginChanges("Создание отрезка из точки");

			//Path3DPath^ newPath3D = gcnew Path3DPath(doc);
			//for each (Object ^ path3D in paths3D)
			//	newPath3D->Wires->Add(((Path3D^)path3D)->Geometry->Curve);

			//TFlex::Application::Window->StatusBar->Command = "3PA";
		//	TFlex::Application::ActiveMainWindow->StatusBar->Command = "3PA";
			//TFlex::Application::ActiveMainWindow->StatusBar->Command = "K";
			
		//	path3D_0->Create(doc, curves, intervals);
			
			//Закрываем блок изменения документа
			doc->EndChanges();




			//Path3D^ path3D = gcnew Path3D(doc);

			//path3D->Create(doc, , );
			


			////Открываем блок изменения документа
			//doc->BeginChanges("Создание горизонтального отрезка");
			////Создаем первый узел
			//FreeNode^ newNode1 = gcnew FreeNode(doc, 100, 100);
			////Создаем второй узел
			//FreeNode^ newNode2 = gcnew FreeNode(doc, 200, 100);
			////Соединяем узлы прямой
			//ConstructionOutline^ newOutline = gcnew ConstructionOutline(doc, newNode1, newNode2);
			////Закрываем блок изменения документа
			//doc->EndChanges();
		}


	}
}

void HelloPlugin::Copy3DPath(Document^ doc, TFlex::Model::ObjectContainer^ paths3D)
{
	//Открываем блок изменения документа
	doc->BeginChanges("Создание 3D пути копированием");

	Path3DPath^ newPath3D = gcnew Path3DPath(doc);
	for each (Object ^ path3D in paths3D)
		newPath3D->Wires->Add(((Path3D^)path3D)->Geometry->Curve);

	//Закрываем блок изменения документа
	doc->EndChanges();
}

