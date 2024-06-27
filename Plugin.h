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
};

