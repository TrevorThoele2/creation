
#include <cctype>

#include "Entity.h"

#include "CurrentWorld.h"

#include "Viewport.h"
#include "MainFrame.h"

#include <Atmos\GeneralComponent.h>

namespace Creation
{
    void CreateImagePtr(Optional<Image> &image, Build::Package<Atmos::Entity> &entity, const ::Atmos::FileName &assetName, const Atmos::Color &color)
    {
        auto &position = entity.generalComponent.position;
        image.Set(Image(assetName, color));
        image->SetPosition(position.Build());
    }

    void Selectable<Build::Package<Atmos::Entity>>::SelectImpl()
    {
        if (selectedRender)
            return;

        CreateImagePtr(selectedRender, GetWrapped(), pixelImageName, Atmos::Color(127, 255, 255, 255));
        selectedRender->SetXScaler(32);
        selectedRender->SetYScaler(32);
        PublishSprite();
    }

    void Selectable<Build::Package<Atmos::Entity>>::DeselectImpl()
    {
        selectedRender.Reset();
    }

    void Selectable<Build::Package<Atmos::Entity>>::PublishSprite()
    {
        if (selectedRender.IsValid())
            CurrentWorld::GetCurrentField()->renderFragments.Add(*selectedRender);
    }

    void Selectable<Build::Package<Atmos::Entity>>::UnpublishSprite()
    {
        if (selectedRender.IsValid())
            CurrentWorld::GetCurrentField()->renderFragments.Remove(*selectedRender);
    }

    void Selectable<Build::Package<Atmos::Entity>>::OnMove(Selectable &&arg)
    {
        arg.UnpublishSprite();
        selectedRender = std::move(arg.selectedRender);
        PublishSprite();
    }

    Selectable<Build::Package<Atmos::Entity>>::Selectable(WrappedT &wrapped) : SelectableBase(wrapped)
    {}

    Selectable<Build::Package<Atmos::Entity>>::Selectable(Selectable &&arg) : SelectableBase(std::move(arg))
    {
        OnMove(std::move(arg));
    }

    Selectable<Build::Package<Atmos::Entity>>& Selectable<Build::Package<Atmos::Entity>>::operator=(Selectable &&arg)
    {
        SelectableBase::operator=(std::move(arg));

        OnMove(std::move(arg));
        return *this;
    }

    bool Selectable<Build::Package<Atmos::Entity>>::operator==(const Selectable &arg) const
    {
        return SelectableBase::operator==(arg);
    }

    bool Selectable<Build::Package<Atmos::Entity>>::operator!=(const Selectable &arg) const
    {
        return !(*this == arg);
    }

    String GetEntityNameDuplicates(const String &name)
    {
        if(::Atmos::Ent::NameSystem::FindEntity(name) == ::Atmos::Ent::nullEntity)
            return name;

        // Figure out a new name for this entity as there is one with the same name
        String newName(name);

        // If the entity doesn't have have an underscore in the name, then it can be skipped
        {
            bool needAppend = true;
            for (auto loop = name.rbegin(); loop != name.rend(); ++loop)
            {
                if (*loop == '_')
                {
                    needAppend = false;
                    break;
                }

                if (!std::isdigit(*loop))
                {
                    needAppend = true;
                    break;
                }
            }

            if(needAppend)
                newName.append("_2");
        }

        // Scan through the entity's name. Find if the part after the _ is a number
        while (::Atmos::Ent::NameSystem::FindEntity(newName) != ::Atmos::Ent::nullEntity)
        {
            // Otherwise, add one to the ending number...
            // While the currently focused digit is 9, then we need to do carrying
            size_t focusedPosition = newName.size() - 1;
            int digit = std::stoi(newName.substr(focusedPosition, 1));
            if (digit == 9)
            {
                newName.append("0");
                while (digit == 9)
                {
                    digit = std::stoi(newName.substr(focusedPosition, 1));
                    newName[focusedPosition] = '0';
                    --focusedPosition;
                }
            }

            newName[focusedPosition] = ::Atmos::ToString(digit + 1)[0];
        }

        return newName;
    }
}