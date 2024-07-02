#include "Plugin.h"
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

			doc->Objects;
			TFlex::Model::ObjectContainer^ point = doc->Nodes3D;

			Object^ obj = point->Count;

			//Получение объекта по имени
			OnSurfacePoint^ point_0 = (OnSurfacePoint^)doc->GetObjectByName("3D Узел_9");

		
			
			//TFlex::Model::Model3D::OnSurfacePoint^ num = point[8];

			

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

