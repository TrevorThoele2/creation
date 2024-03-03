#pragma once

#include "DataIncludes.h"
#include <Atmos/Key.h>

#include "EnumData.h"

namespace Creation::Editing
{
    namespace Data
    {
        struct ModifierKey
        {
            Atmos::Input::Key key;
        };
    }

    template<>
    struct EnumTraits<Atmos::Input::Key>
    {
        using EnumT = Atmos::Input::Key;
        static EnumDescriptors<EnumT> descriptors;
    };

    template<>
    class Property<Atmos::Input::Key> final : public EnumProperty<Atmos::Input::Key>
    {
    public:
        using EnumProperty::EnumProperty;
    };

    template<>
    class Nexus<Atmos::Input::Key> final : public NexusCommon<Atmos::Input::Key>
    {
    public:
        using NexusCommon<Atmos::Input::Key>::NexusCommon;
    };

    template<>
    class NexusBatch<Data::ModifierKey> final : public NexusBatchCommon<Data::ModifierKey>
    {
    public:
        Property<Atmos::Input::Key> key;
    public:
        NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui);
        NexusBatch(NexusBatch&& arg) noexcept;
    private:
        void SetupProperties();
    };

    template<>
    class Nexus<Data::ModifierKey> final : public EditableNexusCommon<Data::ModifierKey>
    {
    public:
        Nexus<Atmos::Input::Key> key;
    public:
        Nexus(
            DataT& data,
            NexusNode* parent,
            NexusHistory nexusHistory,
            UI& ui,
            Arca::Reliquary& reliquary);
        Nexus(Nexus&& arg, NexusNode* parent) noexcept;
        Nexus(Nexus&& arg) noexcept = default;
    private:
        void SetupChildren();

        [[nodiscard]] String CalculateLabel(Atmos::Input::Key key) const;
    };
}

namespace Inscription
{
    template<>
    class Scribe<Creation::Editing::Data::ModifierKey> final
    {
    public:
        using ObjectT = Creation::Editing::Data::ModifierKey;
    public:
        template<class Format>
        void Scriven(ObjectT& object, Format& format)
        {
            format("key", object.key);
        }
    };

    template<class Format>
    struct ScribeTraits<Creation::Editing::Data::ModifierKey, Format> final
    {
        using Category = CompositeScribeCategory<Creation::Editing::Data::ModifierKey>;
    };
}