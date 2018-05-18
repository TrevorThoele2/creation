#pragma once

#include "DataIncludes.h"
#include "FilePath.h"

#include <wx/propgrid/props.h>

namespace Creation::Editing
{
    template<>
    class Property<File::Path> final : public TerminalProperty<File::Path>
    {
    public:
        Property(
            const String& name,
            const String& label,
            wxPGProperty* parentProperty,
            wxPropertyGrid& grid,
            const NexusHistory& nexusHistory,
            UI& ui);
        Property(Property&& arg) noexcept;

        void SetWildcard(const String& wildcard);
        void SetInitialPath(const File::Path& initialPath);
        void SetDialogTitle(const String& dialogTitle);
        void SetRelative(const File::Path& basePath);
    protected:
        [[nodiscard]] DataT ValueFromProperty() const override;
        [[nodiscard]] wxVariant VariantFromData(const DataT& data) override;
    private:
        wxFileProperty* property = nullptr;

        String wildcard;
        std::optional<File::Path> initialPath;
        String dialogTitle;

        std::optional<File::Path> basePath;
    };

    template<>
    class Nexus<File::Path> final : public NexusCommon<File::Path>
    {
    public:
        using NexusCommon<File::Path>::NexusCommon;
    };
}