#pragma once

#include <wx/dialog.h>
#include <wx/filepicker.h>
#include <wx/checkbox.h>

namespace Creation
{
    struct Settings;

    class SettingsDialog final : public wxDialog
    {
    public:
        SettingsDialog(
            const Settings& defaults,
            wxWindow *parent,
            const wxString &title,
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxSize(700, 600),
            long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP,
            const wxString &name = wxDialogNameStr);
        
        [[nodiscard]] Settings Settings() const;
    private:
        wxDirPickerCtrl* worldPath;
        wxDirPickerCtrl* buildPath;
        wxDirPickerCtrl* audioAssetPath;
        wxDirPickerCtrl* imageAssetPath;
        wxDirPickerCtrl* fontAssetPath;
        wxDirPickerCtrl* scriptAssetPath;
        wxDirPickerCtrl* compiledScriptAssetPath;
        wxDirPickerCtrl* shaderAssetPath;
        wxDirPickerCtrl* compiledShaderAssetPath;
    };
}