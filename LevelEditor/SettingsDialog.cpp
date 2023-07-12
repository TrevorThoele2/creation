
#include "SettingsDialog.h"

#include "Settings.h"

#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

namespace Creation
{
    SettingsDialog::SettingsDialog(wxWindow *parent, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name) : wxDialog(parent, wxID_ANY, title, pos, size, style, name)
    {
        SetSizer(new wxBoxSizer(wxVERTICAL));

        GetSizer()->Add(new wxStaticText(this, wxID_ANY, "World Path"), 0, wxEXPAND);
        worldPath = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxDirSelectorPromptStr, wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL);
        GetSizer()->Add(worldPath, 0, wxEXPAND);

        GetSizer()->Add(new wxStaticText(this, wxID_ANY, "Build Path"), 0, wxEXPAND);
        buildPath = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxDirSelectorPromptStr, wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL);
        GetSizer()->Add(buildPath, 0, wxEXPAND);

        GetSizer()->Add(new wxStaticText(this, wxID_ANY, "Audio Asset Path"), 0, wxEXPAND);
        audioAssetPath = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxDirSelectorPromptStr, wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL);
        GetSizer()->Add(audioAssetPath, 0, wxEXPAND);

        GetSizer()->Add(new wxStaticText(this, wxID_ANY, "Image Asset Path"), 0, wxEXPAND);
        imageAssetPath = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxDirSelectorPromptStr, wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL);
        GetSizer()->Add(imageAssetPath, 0, wxEXPAND);

        GetSizer()->Add(new wxStaticText(this, wxID_ANY, "Script Asset Path"), 0, wxEXPAND);
        scriptAssetPath = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxDirSelectorPromptStr, wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL);
        GetSizer()->Add(scriptAssetPath, 0, wxEXPAND);

        GetSizer()->Add(new wxStaticText(this, wxID_ANY, "Shader Asset Path"), 0, wxEXPAND);
        shaderAssetPath = new wxDirPickerCtrl(this, wxID_ANY, wxEmptyString, wxDirSelectorPromptStr, wxDefaultPosition, wxDefaultSize, wxDIRP_USE_TEXTCTRL);
        GetSizer()->Add(shaderAssetPath, 0, wxEXPAND);

        GetSizer()->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL));
        Layout();
        CentreOnScreen();

        worldPath->SetPath(Settings::GetWorldPath().GetValue());
        buildPath->SetPath(Settings::GetBuildPath().GetValue());
        audioAssetPath->SetPath(Settings::GetAudioAssetPath().GetValue());
        imageAssetPath->SetPath(Settings::GetImageAssetPath().GetValue());
        scriptAssetPath->SetPath(Settings::GetScriptAssetPath().GetValue());
        shaderAssetPath->SetPath(Settings::GetShaderAssetPath().GetValue());
    }

    String SettingsDialog::GetWorldPath() const
    {
        return worldPath->GetPath().ToStdString();
    }

    String SettingsDialog::GetBuildPath() const
    {
        return buildPath->GetPath().ToStdString();
    }

    String SettingsDialog::GetAudioAssetPath() const
    {
        return audioAssetPath->GetPath().ToStdString();
    }

    String SettingsDialog::GetImageAssetPath() const
    {
        return imageAssetPath->GetPath().ToStdString();
    }

    String SettingsDialog::GetScriptAssetPath() const
    {
        return scriptAssetPath->GetPath().ToStdString();
    }

    String SettingsDialog::GetShaderAssetPath() const
    {
        return shaderAssetPath->GetPath().ToStdString();
    }
}