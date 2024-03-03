#include "SettingsDialog.h"

#include "Settings.h"

#include "String.h"

#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

namespace Creation
{
    SettingsDialog::SettingsDialog(
        const Creation::Settings& defaults,
        wxWindow *parent,
        const wxString &title,
        const wxPoint &pos,
        const wxSize &size,
        long style,
        const wxString &name)
        :
        wxDialog(parent, wxID_ANY, title, pos, size, style, name)
    {
        SetSizer(new wxBoxSizer(wxVERTICAL));

        const auto createDirectoryPicker = [this](const String& name, wxDirPickerCtrl*& picker)
        {
            GetSizer()->Add(new wxStaticText(this, wxID_ANY, name), 0, wxEXPAND);
            picker = new wxDirPickerCtrl(
                this,
                wxID_ANY,
                wxEmptyString,
                wxDirSelectorPromptStr,
                wxDefaultPosition,
                wxDefaultSize,
                wxDIRP_USE_TEXTCTRL);
            GetSizer()->Add(picker, 0, wxEXPAND);
        };

        createDirectoryPicker("World Path", worldPath);
        createDirectoryPicker("Build Path", buildPath);
        createDirectoryPicker("Audio Asset Path", audioAssetPath);
        createDirectoryPicker("Image Asset Path", imageAssetPath);
        createDirectoryPicker("Font Asset Path", fontAssetPath);
        createDirectoryPicker("Script Asset Path", scriptAssetPath);
        createDirectoryPicker("Compiled Script Asset Path", compiledScriptAssetPath);
        createDirectoryPicker("Shader Asset Path", shaderAssetPath);
        createDirectoryPicker("Compiled Shader Asset Path", compiledShaderAssetPath);

        GetSizer()->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL));
        Layout();
        CentreOnScreen();

        worldPath->SetPath(defaults.worldPath.string());
        buildPath->SetPath(defaults.buildPath.string());
        audioAssetPath->SetPath(defaults.audioAssetPath.string());
        imageAssetPath->SetPath(defaults.imageAssetPath.string());
        fontAssetPath->SetPath(defaults.fontAssetPath.string());
        scriptAssetPath->SetPath(defaults.scriptAssetPath.string());
        compiledScriptAssetPath->SetPath(defaults.compiledScriptAssetPath.string());
        shaderAssetPath->SetPath(defaults.shaderAssetPath.string());
        compiledShaderAssetPath->SetPath(defaults.compiledShaderAssetPath.string());
    }

    Settings SettingsDialog::Settings() const
    {
        const auto extractPath = [](wxDirPickerCtrl& ctrl)
        {
            return ctrl.GetPath().ToStdString();
        };

        return Creation::Settings
        {
            extractPath(*worldPath),
            extractPath(*buildPath),
            extractPath(*audioAssetPath),
            extractPath(*imageAssetPath),
            extractPath(*fontAssetPath),
            extractPath(*scriptAssetPath),
            extractPath(*compiledScriptAssetPath),
            extractPath(*shaderAssetPath),
            extractPath(*compiledShaderAssetPath)
        };
    }
}