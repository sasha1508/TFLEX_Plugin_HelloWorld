#include "Plugin.h"
#include <list>
//#include <string>
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
			

			//Перечисляем все 3D узлы и выводим их имена:
			System::String^ pointsString = "";
			for each (Object ^ point in points)
				pointsString += ((TFlex::Model::Model3D::Node3D^)point)->DisplayName + "\n";
			MessageBox::Show(pointsString, "Перечисляем 3D узлы");
			

			//Выводим имена поверхности и 3D пути найденых по имени:
			MessageBox::Show(surface_0->Owner->DisplayName + " / " + Path3D_0->DisplayName, point_0->DisplayName);
			

			//Перечисляем все 3D пути и выводим их имена:
			System::String^ paths3DString = "";
			for each (Object ^ path3D in paths3D)
				paths3DString += ((TFlex::Model::Model3D::Path3D^)path3D)->DisplayName + "\n";
			MessageBox::Show(paths3DString, "Перечисляем 3D пути");

			
			//Создаём 3D узлы:
			MessageBox::Show("Создаём 3D узлы", "Построение");
			CoordinateNode3D^ point_1 = Create3DPoint(doc, 20, 20, 550);
			CoordinateNode3D^ point_2 = Create3DPoint(doc, 30, 80, 600);


			//Создаём 3D путь копированием всех 3D путей:
			MessageBox::Show("Создаём 3D путь копированием всех 3D путей", "Построение");
			Copy3DPath(doc, paths3D);


				//ПОСТРОЕНИЕ ЗАМКНУТОГО КОНТУРА НА ПЛОСКОСТИ:

			MessageBox::Show("Строим замкнутый контур на плоскости", "Построение");

			StandardWorkplane^ plane_1 = CreatePlane(doc);        //создаём рабоччуу плоскость
			SketchProfile^ sketch = CreateSketch(doc, plane_1);   //создаём эскиз на рабочей плоскости

			//Создаём три точки:
			FreeNode^ point2D_1 = Create2DPoint(doc, 20, 20);
			FreeNode^ point2D_2 = Create2DPoint(doc, 20, 500);
			FreeNode^ point2D_3 = Create2DPoint(doc, 200, 500);

			//Создаём три линии:
			ConstructionOutline^ line_1 = CreateLineOnTwo2DPoints(doc, point2D_1, point2D_2);
			ConstructionOutline^ line_2 = CreateLineOnTwo2DPoints(doc, point2D_2, point2D_3);
			ConstructionOutline^ line_3 = CreateLineOnTwo2DPoints(doc, point2D_3, point2D_1);


			//Добавляем линии в эскиз:
			doc->BeginChanges("Добавляем линий в эскиз");    //Открываем блок изменения документа
			sketch->Outlines->Add(line_1);
			sketch->Outlines->Add(line_2);
			sketch->Outlines->Add(line_3);
			doc->EndChanges();   //Закрываем блок изменения документа


			//Создаём выдавливание
			MessageBox::Show("Создаём выдавливание", "Построение");
			Extrusion(doc, sketch, (Parameter^)100);

			//TFlex::Application::Window->StatusBar->Command = "3PA";
		//	TFlex::Application::ActiveMainWindow->StatusBar->Command = "3PA";
			//TFlex::Application::ActiveMainWindow->StatusBar->Command = "K";
		}
	}
}

/// <summary>
/// Создание 3D пути копированием других 3D путей
/// </summary>
/// <param name="doc"></param>
/// <param name="paths3D"></param>
void HelloPlugin::Copy3DPath(Document^ doc, TFlex::Model::ObjectContainer^ paths3D)
{
	
	doc->BeginChanges("Создание 3D пути копированием");    //Открываем блок изменения документа

	Path3DPath^ newPath3D = gcnew Path3DPath(doc);
	for each (Path3D^ path3D in paths3D)
		newPath3D->Wires->Add(path3D->Geometry->Curve);

	
	doc->EndChanges();   //Закрываем блок изменения документа
}

/// <summary>
/// Создание 2D узла по координатам
/// </summary>
/// <param name="doc"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
FreeNode^ HelloPlugin::Create2DPoint(Document^ doc, int x, int y) 
{
	doc->BeginChanges("Создание 2D узла по координатам");//Открытие блока изменений документа

	FreeNode^ fn1 = gcnew FreeNode(doc, x, y);

	doc->EndChanges();   //Закрываем блок изменения документа

	return fn1;
}


/// <summary>
/// Создание 3D узла по координатам
/// </summary>
/// <param name="doc"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
CoordinateNode3D^ HelloPlugin::Create3DPoint(Document^ doc, int x, int y, int z)
{
	doc->BeginChanges("Создание 3D узла по координатам");  //Открываем блок изменения документа

	//создание узлов        
	CoordinateNode3D^ fn1 = gcnew CoordinateNode3D(doc);
	fn1->X = x;
	fn1->Y = y;
	fn1->Z = z;

	
	doc->EndChanges();   //Закрываем блок изменения документа

	return fn1;
}


/// <summary>
/// Создание отрезка по двум 2D узлам
/// </summary>
/// <param name="doc"></param>
/// <param name="point_1"></param>
/// <param name="point_2"></param>
ConstructionOutline^ HelloPlugin::CreateLineOnTwo2DPoints(Document^ doc, FreeNode^ point_1, FreeNode^ point_2)
{
	doc->BeginChanges("Создание отрезка по двум 2D узлам");  //Открываем блок изменения документа


	ConstructionOutline^ l1 = gcnew ConstructionOutline(doc, point_1, point_2);

	
	doc->EndChanges();   //Закрываем блок изменения документа

	return l1;
}


/// <summary>
/// Создание отрезка по двум 3D узлам
/// </summary>
/// <param name="doc"></param>
/// <param name="point_1"></param>
/// <param name="point_2"></param>
void HelloPlugin::CreateLineOnTwo3DPoints(Document^ doc, CoordinateNode3D^ point_1, CoordinateNode3D^ point_2)
{
	doc->BeginChanges("Создание отрезка по двум 3D узлам");  //Открываем блок изменения документа

	Path3D^ path3D = gcnew Path3D(doc);

	//path3D.
	//ConstructionOutline^ l1 = gcnew ConstructionOutline(doc, point_1, point_2);


	doc->EndChanges();   //Закрываем блок изменения документа
}


/// <summary>
///Создание рабочей плоскости повторяющей начальную
/// </summary>
/// <param name="doc"></param>
/// <param name="point_1"></param>
/// <param name="point_2"></param>
StandardWorkplane^ HelloPlugin::CreatePlane(Document^ doc)
{
	doc->BeginChanges("Создание рабочей плоскости повторяющей начальную");  //Открываем блок изменения документа

	//рабочая плоскость(вид слева), на которой будет построен профиль        
	StandardWorkplane^ swp = gcnew StandardWorkplane(doc, StandardWorkplane::StandardType::Left);

	doc->EndChanges();   //Закрываем блок изменения документа

	return swp;
}


/// <summary>
/// Создание эскиза на рабочей плоскости
/// </summary>
/// <param name="doc"></param>
/// <param name="swp"></param>
/// <returns></returns>
SketchProfile^ HelloPlugin::CreateSketch(Document^ doc, StandardWorkplane^ swp)
{
	doc->BeginChanges("Создание эскиза на рабочей плоскости");  //Открываем блок изменения документа

	SketchProfile^ sp = gcnew SketchProfile(doc);
	sp->WorkSurface = swp;


	doc->EndChanges();   //Закрываем блок изменения документа

	return sp;
}


void HelloPlugin::Extrusion(Document^ doc, SketchProfile^ profile, Parameter^ length)
{
	doc->BeginChanges("Выдавливание");  //Открываем блок изменения документа

	ThickenExtrusion^ extr_1 = gcnew ThickenExtrusion(doc);       // Создаем операцию выталкивания
	extr_1->ForwardLength = length;            // Длина выталкивания для первого направления
	extr_1->Profile->Add(profile->Geometry->SheetContour);        // Профиль для выталкивания

	doc->EndChanges();   //Закрываем блок изменения документа
}