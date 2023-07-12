#pragma once

#include <wx/dialog.h>

#include "String.h"

#include <wx/filepicker.h>

namespace Creation
{
    class SettingsDialog : public wxDialog
    {
    private:
        wxDirPickerCtrl *worldPath;
        wxDirPickerCtrl *buildPath;
        wxDirPickerCtrl *audioAssetPath;
        wxDirPickerCtrl *imageAssetPath;
        wxDirPickerCtrl *scriptAssetPath;
        wxDirPickerCtrl *shaderAssetPath;
    public:
        SettingsDialog(wxWindow *parent, const wxString &title, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(700, 600), long style = wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP, const wxString &name = wxDialogNameStr);
        
        String GetWorldPath() const;
        String GetBuildPath() const;
        String GetAudioAssetPath() const;
        String GetImageAssetPath() const;
        String GetScriptAssetPath() const;
        String GetShaderAssetPath() const;
    };
}