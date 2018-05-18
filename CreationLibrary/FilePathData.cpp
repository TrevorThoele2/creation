#include "FilePathData.h"

namespace Creation::Editing
{
    Property<std::filesystem::path>::Property(
        const String& name,
        const String& label,
        wxPGProperty* parentProperty,
        wxPropertyGrid& grid,
        const NexusHistory& nexusHistory,
        UI& ui)
        :
        TerminalProperty(
            label,
            new wxFileProperty(label, PropertyName(name, parentProperty)),
            parentProperty,
            grid,
            nexusHistory,
            ui)
    {
        property = dynamic_cast<wxFileProperty*>(WxProperty());
        SetWildcard(wildcard);
        SetDialogTitle(dialogTitle);
    }

    Property<std::filesystem::path>::Property(Property&& arg) noexcept :
        TerminalProperty(std::move(arg)),
        property(arg.property)
    {}

    void Property<std::filesystem::path>::SetWildcard(const String& wildcard)
    {
        this->wildcard = wildcard;
        property->SetAttribute(wxPG_FILE_WILDCARD, wildcard);
    }

    void Property<std::filesystem::path>::SetInitialPath(const File::Path& initialPath)
    {
        this->initialPath = initialPath;
        property->SetAttribute(wxPG_FILE_INITIAL_PATH, initialPath.c_str());
    }

    void Property<std::filesystem::path>::SetDialogTitle(const String& dialogTitle)
    {
        this->dialogTitle = dialogTitle;
        property->SetAttribute("DialogTitle", dialogTitle);
    }

    void Property<std::filesystem::path>::SetRelative(const File::Path& basePath)
    {
        this->basePath = basePath;
        property->SetAttribute(wxPG_FILE_SHOW_RELATIVE_PATH, true);
    }

    auto Property<std::filesystem::path>::ValueFromProperty() const -> DataT
    {
        const auto fullPath = std::filesystem::path(static_cast<String>(property->GetFileName().GetFullPath()));
        return fullPath;
    }

    wxVariant Property<File::Path>::VariantFromData(const DataT& data)
    {
        return data.c_str();
    }
}