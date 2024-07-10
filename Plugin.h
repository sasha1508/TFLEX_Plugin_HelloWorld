#pragma once
using namespace System;
using namespace System::Windows::Forms;

using namespace TFlex;
using namespace TFlex::Model;
using namespace TFlex::Model::Model3D;
using namespace TFlex::Model::Model2D;

ref class HelloPlugin : public Plugin
{
public:
	HelloPlugin(PluginFactory^ factory);
protected public:
	virtual void OnInitialize() override;
	virtual void OnCreateTools() override;
	virtual void OnCommand(Document^ document, int id) override;
	virtual void Start();
	virtual void Copy3DPath(Document^ doc, TFlex::Model::ObjectContainer^ paths3D);
	FreeNode^ Create2DPoint(Document^ doc, int x, int y);
	CoordinateNode3D^ Create3DPoint(Document^ doc, int x, int Y, int z);
	ConstructionOutline^ CreateLineOnTwo2DPoints(Document^ doc, FreeNode^ point_1, FreeNode^ point_2);
	void CreateLineOnTwo3DPoints(Document^ doc, CoordinateNode3D^ point_1, CoordinateNode3D^ point_2);
	StandardWorkplane^ CreatePlane(Document^ doc);
	SketchProfile^ CreateSketch(Document^ doc, StandardWorkplane^ swp);
	void Extrusion(Document^ doc, SketchProfile^ profile, Parameter^ length);
};

