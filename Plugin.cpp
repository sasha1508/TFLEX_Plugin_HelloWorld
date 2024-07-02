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

	RegisterCommand(1, "��������� ������");
	TFlex::Application::ActiveMainWindow->InsertPluginMenuItem(1,
		"������", MainWindow::InsertMenuPosition::EndOfTools, this);

	TFlex::Menu^ submenu = gcnew TFlex::Menu();
	submenu->CreatePopup();
	submenu->Append(1, "������", this);

	TFlex::Application::ActiveMainWindow->InsertPluginSubMenu("������", submenu, MainWindow::InsertMenuPosition::PluginSamples, this);

	TFlex::RibbonGroup^ ribbonGroup = TFlex::RibbonBar::ApplicationsTab->AddGroup("������");
	ribbonGroup->AddButton(1, this);

	array<int>^ cmdIDs = gcnew array<int> { 1 };
	CreateToolbar("������", cmdIDs);
	CreateMainBarPanel("������", cmdIDs, this->ID, true);

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
	DialogResult result = MessageBox::Show("����� �������� ��������� ������", "���������� ���������� �������", MessageBoxButtons::OKCancel);
	if (result == DialogResult::OK)
	{
		Document^ doc = TFlex::Application::ActiveDocument;
		if (doc != nullptr)
		{
			////���������� ��� ��������� ���������:
			//String^ FileName = doc->FileName;
			//MessageBox::Show(FileName);

			//doc->Objects;

			TFlex::Model::ObjectContainer^ points = doc->Nodes3D;   //�������� ������ ���� 3D �����
			TFlex::Model::ObjectContainer^ paths3D = doc->Paths3D;   //�������� ������ ���� 3D �����

			OnSurfacePoint^ point_0 = (OnSurfacePoint^)doc->GetObjectByName("3D ����_9");  //�������� �������� ����� �� �����
			Path3D^ Path3D_0 = (Path3D^)doc->GetObjectByName("3D ����_7");  //�������� 3D-���� �� �����
			TFlex::Model::Model3D::Geometry::ModelSurface^ surface_0 = point_0->Surface;  //�������� �����������, �� ������� ����������� �����
			

			for each (Object^ point in points)
			{
				MessageBox::Show(((TFlex::Model::Model3D::Node3D^)point)->DisplayName, "����������� �����");
			}
			MessageBox::Show(surface_0->Owner->DisplayName + " / " + Path3D_0->DisplayName, point_0->DisplayName);
			
			for each (Object ^ path3D in paths3D)
			{
				MessageBox::Show(((TFlex::Model::Model3D::Path3D^)path3D)->DisplayName, "����������� 3D ����");
			}

			
			//��������� ���� ��������� ���������
			doc->BeginChanges("�������� ������� �� �����");;

			Path3D^ path3D_0 = gcnew Path3D(doc);

			//path3D_0.
			
		//	path3D_0->Create(doc, curves, intervals);
			
			//��������� ���� ��������� ���������
			doc->EndChanges();




			//Path3D^ path3D = gcnew Path3D(doc);

			//path3D->Create(doc, , );
			


			////��������� ���� ��������� ���������
			//doc->BeginChanges("�������� ��������������� �������");
			////������� ������ ����
			//FreeNode^ newNode1 = gcnew FreeNode(doc, 100, 100);
			////������� ������ ����
			//FreeNode^ newNode2 = gcnew FreeNode(doc, 200, 100);
			////��������� ���� ������
			//ConstructionOutline^ newOutline = gcnew ConstructionOutline(doc, newNode1, newNode2);
			////��������� ���� ��������� ���������
			//doc->EndChanges();
		}
	}
}

