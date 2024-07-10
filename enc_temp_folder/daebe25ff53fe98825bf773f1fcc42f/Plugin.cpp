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
				MessageBox::Show(((TFlex::Model::Model3D::Node3D^)point)->DisplayName, "����������� �����");
			

			MessageBox::Show(surface_0->Owner->DisplayName + " / " + Path3D_0->DisplayName, point_0->DisplayName);
			

			for each (Object ^ path3D in paths3D)
				MessageBox::Show(((TFlex::Model::Model3D::Path3D^)path3D)->DisplayName, "����������� 3D ����");
			
			//TFlex::StatusBar::Command = "";
			
			CoordinateNode3D^ point_1 = Create3DPoint(doc, 20, 20, 20);
			CoordinateNode3D^ point_2 = Create3DPoint(doc, 20, 20, 200);
			Copy3DPath(doc, paths3D);

			FreeNode^ point2D_1 = Create2DPoint(doc, 20, 20);
			FreeNode^ point2D_2 = Create2DPoint(doc, 20, 500);
			FreeNode^ point2D_3 = Create2DPoint(doc, 200, 500);

			//

			StandardWorkplane^ plane_1 = CreatePlane(doc);        //������ �������� ���������
			SketchProfile^ sketch = CreateSketch(doc, plane_1);   //������ ����� �� ������� ���������

			ConstructionOutline^ line_1 = CreateLineOnTwo2DPoints(doc, point2D_1, point2D_2);
			ConstructionOutline^ line_2 = CreateLineOnTwo2DPoints(doc, point2D_2, point2D_3);
			ConstructionOutline^ line_3 = CreateLineOnTwo2DPoints(doc, point2D_3, point2D_1);

			sketch->Outlines->Add(line_1);
			sketch->Outlines->Add(line_2);
			sketch->Outlines->Add(line_3);


		//	doc->EndChanges();//�������� ����� ��������� ���������

			



			//��������� ���� ��������� ���������
			doc->BeginChanges("�������� ������� �� �����");


			//TFlex::Application::Window->StatusBar->Command = "3PA";
		//	TFlex::Application::ActiveMainWindow->StatusBar->Command = "3PA";
			//TFlex::Application::ActiveMainWindow->StatusBar->Command = "K";
			
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

/// <summary>
/// �������� 3D ���� ������������ ������ 3D �����
/// </summary>
/// <param name="doc"></param>
/// <param name="paths3D"></param>
void HelloPlugin::Copy3DPath(Document^ doc, TFlex::Model::ObjectContainer^ paths3D)
{
	//��������� ���� ��������� ���������
	doc->BeginChanges("�������� 3D ���� ������������");

	Path3DPath^ newPath3D = gcnew Path3DPath(doc);
	for each (Object ^ path3D in paths3D)
		newPath3D->Wires->Add(((Path3D^)path3D)->Geometry->Curve);

	//��������� ���� ��������� ���������
	doc->EndChanges();
}

/// <summary>
/// �������� 2D ���� �� �����������
/// </summary>
/// <param name="doc"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
FreeNode^ HelloPlugin::Create2DPoint(Document^ doc, int x, int y) 
{
	doc->BeginChanges("�������� 2D ���� �� �����������");//�������� ����� ��������� ���������

	FreeNode^ fn1 = gcnew FreeNode(doc, x, y);

	doc->EndChanges();   //��������� ���� ��������� ���������

	return fn1;
}


/// <summary>
/// �������� 3D ���� �� �����������
/// </summary>
/// <param name="doc"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
/// <returns></returns>
CoordinateNode3D^ HelloPlugin::Create3DPoint(Document^ doc, int x, int y, int z)
{
	doc->BeginChanges("�������� 3D ���� �� �����������");  //��������� ���� ��������� ���������

	//�������� �����        
	CoordinateNode3D^ fn1 = gcnew CoordinateNode3D(doc);
	fn1->X = x;
	fn1->Y = y;
	fn1->Z = z;

	//��������� ���� ��������� ���������
	doc->EndChanges();

	return fn1;
}


/// <summary>
/// �������� ������� �� ���� 2D �����
/// </summary>
/// <param name="doc"></param>
/// <param name="point_1"></param>
/// <param name="point_2"></param>
ConstructionOutline^ HelloPlugin::CreateLineOnTwo2DPoints(Document^ doc, FreeNode^ point_1, FreeNode^ point_2)
{
	doc->BeginChanges("�������� ������� �� ���� 2D �����");  //��������� ���� ��������� ���������

	ConstructionOutline^ l1 = gcnew ConstructionOutline(doc, point_1, point_2);

	//������� ���������(��� �����), �� ������� ����� �������� �������        
			/*StandardWorkplane^ swp = gcnew StandardWorkplane(doc, StandardWorkplane::StandardType::Left);
			SketchProfile^ sp = gcnew SketchProfile(doc);
			sp->WorkSurface = swp;
			sp->Outlines->Add(l1);*/
	
	doc->EndChanges();   //��������� ���� ��������� ���������

	return l1;
}


/// <summary>
/// �������� ������� �� ���� 3D �����
/// </summary>
/// <param name="doc"></param>
/// <param name="point_1"></param>
/// <param name="point_2"></param>
void HelloPlugin::CreateLineOnTwo3DPoints(Document^ doc, CoordinateNode3D^ point_1, CoordinateNode3D^ point_2)
{
	doc->BeginChanges("�������� ������� �� ���� 3D �����");  //��������� ���� ��������� ���������

	Path3D^ path3D = gcnew Path3D(doc);

	//path3D.
	//ConstructionOutline^ l1 = gcnew ConstructionOutline(doc, point_1, point_2);


	doc->EndChanges();   //��������� ���� ��������� ���������
}


/// <summary>
///�������� ������� ��������� ����������� ���������
/// </summary>
/// <param name="doc"></param>
/// <param name="point_1"></param>
/// <param name="point_2"></param>
StandardWorkplane^ HelloPlugin::CreatePlane(Document^ doc)
{
	doc->BeginChanges("�������� ������� ��������� ����������� ���������");  //��������� ���� ��������� ���������

	//������� ���������(��� �����), �� ������� ����� �������� �������        
	StandardWorkplane^ swp = gcnew StandardWorkplane(doc, StandardWorkplane::StandardType::Left);

	doc->EndChanges();   //��������� ���� ��������� ���������

	return swp;
}


/// <summary>
/// �������� ������ �� ������� ���������
/// </summary>
/// <param name="doc"></param>
/// <param name="swp"></param>
/// <returns></returns>
SketchProfile^ HelloPlugin::CreateSketch(Document^ doc, StandardWorkplane^ swp)
{
	doc->BeginChanges("�������� ������ �� ������� ���������");  //��������� ���� ��������� ���������

	SketchProfile^ sp = gcnew SketchProfile(doc);
	sp->WorkSurface = swp;


	doc->EndChanges();   //��������� ���� ��������� ���������

	return sp;
}

