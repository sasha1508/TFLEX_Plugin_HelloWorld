#pragma once
using namespace System;
using namespace System::Windows::Forms;

using namespace TFlex;
using namespace TFlex::Model;

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
	virtual void Create3DPoint(Document^ doc, int x, int Y, int z);
};

