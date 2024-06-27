#include "Plugin.h"

HelloPlugin::HelloPlugin(PluginFactory^ factory) : Plugin(factory)
{}

void HelloPlugin::OnInitialize()
{
	Plugin::OnInitialize();
}

void HelloPlugin::OnCreateTools()
{
	Plugin::OnCreateTools();

	RegisterCommand(1, "�������� ����");
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
		MessageBox::Show("Hello World.+++");
		break;
	}
}
