#pragma once

#include <memory>
#include <vector>

#include "Selectable.h"

#include "BuildPackageEntities.h"
#include "Image.h"
#include "Optional.h"
#include "String.h"

namespace Creation
{
    template<>
    class Selectable<Build::Package<Atmos::Entity>> : public SelectableBase<Build::Package<Atmos::Entity>>
    {
    private:
        Optional<Image> selectedRender;

        void SelectImpl() override;
        void DeselectImpl() override;

        void PublishSprite();
        void UnpublishSprite();
        void OnMove(Selectable &&arg);
    public:
        explicit Selectable(WrappedT &wrapped);
        Selectable(const Selectable &arg) = delete;
        Selectable& operator=(const Selectable &arg) = delete;
        Selectable(Selectable &&arg);
        Selectable& operator=(Selectable &&arg);
        bool operator==(const Selectable &arg) const;
        bool operator!=(const Selectable &arg) const;
    };
}

namespace std
{
    template<>
    struct hash<Creation::Selectable<::Creation::Build::Package<Atmos::Entity>>>
    {
        typedef Creation::Selectable<::Creation::Build::Package<Atmos::Entity>> argument_type;
        typedef std::size_t result_type;

        result_type operator()(const argument_type &arg) const
        {
            const result_type first(std::hash<argument_type::WrappedT::BuildT::ValueT>()(arg.GetWrapped().id.Build()));
            return first;
        }
    };
}

namespace Creation
{
    // Will return "Entity_2" if there's an entity with name "Entity", "Entity_3" if has "Entity_2", etc.
    String GetEntityNameDuplicates(const String &name);
}