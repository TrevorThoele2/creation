
#include "DataBreakdownSenses.h"

#include <wx/stattext.h>

namespace Creation
{
    void DataBreakdown<Build::Package<::Atmos::Sprite>>::OnEdited(const DataBreakdownEditArgs &args)
    {
        UpdateDisplay();
    }

    void DataBreakdown<Build::Package<::Atmos::Sprite>>::SubscribeEvents()
    {
        ClearEvents();

        connections.push_back(::Atmos::EventAnyConnection(material.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(index.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(color.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(xScaler.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(yScaler.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(zScaler.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(xRotation.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(yRotation.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
        connections.push_back(::Atmos::EventAnyConnection(zRotation.edited.Subscribe(&DataBreakdown::OnEdited, *this)));
    }

    void DataBreakdown<Build::Package<::Atmos::Sprite>>::ClearEvents()
    {
        for (auto &loop : connections)
            loop.Sever();
        connections.clear();
    }

    void DataBreakdown<Build::Package<::Atmos::Sprite>>::UpdateDisplay()
    {
        /*
        display->Enable(IsEditable());

        auto &selected = *GetSelected();
        display->Set(static_cast<DataBreakdown*>(*selected.begin())->Get()->Build());
        for (auto loop = ++selected.begin(); loop != selected.end(); ++loop)
        {
            if (static_cast<DataBreakdown*>(*loop)->Get()->Build() != *display->GetSprite())
            {
                display->Set(nullptr);
                break;
            }
        }
        */
    }

    void DataBreakdown<Build::Package<::Atmos::Sprite>>::AddAllChildren()
    {
        //AddChild(display);

        AddChild(material);
        AddChild(shaderPatch);
        AddChild(index);
        AddChild(color);
        AddChild(xScaler);
        AddChild(yScaler);
        AddChild(zScaler);
        AddChild(xRotation);
        AddChild(yRotation);
        AddChild(zRotation);
    }

    void DataBreakdown<Build::Package<::Atmos::Sprite>>::SetupImpl()
    {
        material.Setup(Get()->material);
        shaderPatch.Setup(Get()->shaderPatch);
        index.Setup(Get()->index);
        color.Setup(Get()->color);
        xScaler.Setup(Get()->xScaler);
        yScaler.Setup(Get()->yScaler);
        zScaler.Setup(Get()->zScaler);
        xRotation.Setup(Get()->xRotation);
        yRotation.Setup(Get()->yRotation);
        zRotation.Setup(Get()->zRotation);
    }

    DataBreakdown<Build::Package<::Atmos::Sprite>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        material("Material", this),
        shaderPatch("Shader Patch", this),
        index("Index", this),
        color("Color", this),
        xScaler("X Scaler", this),
        yScaler("Y Scaler", this),
        zScaler("Z Scaler", this),
        xRotation("X Rotation", this),
        yRotation("Y Rotation", this),
        zRotation("Z Rotation", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Sprite>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        //display(std::move(arg.display)),
        material(std::move(arg.material), this),
        shaderPatch(std::move(arg.shaderPatch), this),
        index(std::move(arg.index), this),
        color(std::move(arg.color), this),
        xScaler(std::move(arg.xScaler), this),
        yScaler(std::move(arg.yScaler), this),
        zScaler(std::move(arg.zScaler), this),
        xRotation(std::move(arg.xRotation), this),
        yRotation(std::move(arg.yRotation), this),
        zRotation(std::move(arg.zRotation), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Sprite>>& DataBreakdown<Build::Package<::Atmos::Sprite>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        //display = std::move(arg.display);
        material = std::move(arg.material);
        shaderPatch = std::move(arg.shaderPatch);
        index = std::move(arg.index);
        color = std::move(arg.color);
        xScaler = std::move(arg.xScaler);
        yScaler = std::move(arg.yScaler);
        zScaler = std::move(arg.zScaler);
        xRotation = std::move(arg.xRotation);
        yRotation = std::move(arg.yRotation);
        zRotation = std::move(arg.zRotation);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Sound>>::AddAllChildren()
    {
        AddChild(audio);
        AddChild(position);
    }

    void DataBreakdown<Build::Package<::Atmos::Sound>>::SetupImpl()
    {
        audio.Setup(Get()->audio);
        position.Setup(Get()->position);
    }

    DataBreakdown<Build::Package<::Atmos::Sound>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        audio("Audio", this),
        position("Position", this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Sound>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        audio(std::move(arg.audio), this),
        position(std::move(arg.position), this)
    {
        AddAllChildren();
    }

    DataBreakdown<Build::Package<::Atmos::Sound>>& DataBreakdown<Build::Package<::Atmos::Sound>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        audio = std::move(arg.audio);
        position = std::move(arg.position);
        return *this;
    }
}