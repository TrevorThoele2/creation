#include "MaterialAssetData.h"

#include <Inscription/ListScribe.h>

namespace Creation::Editing
{
    namespace Data
    {
        MaterialAssetPass::MaterialAssetPass(const String& vertexShader, const String& fragmentShader) :
            vertexShader(vertexShader), fragmentShader(fragmentShader)
        {}
    }

    NexusBatch<Data::MaterialAssetPass>::NexusBatch(
        wxPropertyGrid& grid, const NexusHistory& nexusHistory, UI& ui)
        :
        NexusBatchCommon(grid),
        vertexShader("VertexShader", "Vertex Shader", nullptr, grid, nexusHistory, ui, "Shader", [&ui]() { return AllShaderAssetNames(ui); }),
        fragmentShader("FragmentShader", "Fragment Shader", nullptr, grid, nexusHistory, ui, "Shader", [&ui]() { return AllShaderAssetNames(ui); })
    {
        SetupProperties();
    }

    NexusBatch<Data::MaterialAssetPass>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        vertexShader(std::move(arg.vertexShader)),
        fragmentShader(std::move(arg.fragmentShader))
    {
        SetupProperties();
    }

    void NexusBatch<Data::MaterialAssetPass>::SetupProperties()
    {
        Auto(vertexShader, &Nexus::vertexShader);
        Auto(fragmentShader, &Nexus::fragmentShader);
    }

    Nexus<Data::MaterialAssetPass>::Nexus(
        DataT& data,
        NexusNode* parent,
        NexusHistory nexusHistory,
        UI& ui,
        Arca::Reliquary& reliquary,
        const String& label)
        :
        EditableNexusCommon(data, parent, nexusHistory, ui, reliquary, label),
        vertexShader(data.vertexShader, this, nexusHistory, ui, reliquary, "Vertex Shader"),
        fragmentShader(data.fragmentShader, this, nexusHistory, ui, reliquary, "Fragment Shader")
    {
        SetupChildren();
    }

    Nexus<Data::MaterialAssetPass>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        vertexShader(std::move(arg.vertexShader), this),
        fragmentShader(std::move(arg.fragmentShader), this)
    {
        SetupChildren();
    }

    void Nexus<Data::MaterialAssetPass>::SetupChildren()
    {
        autoHandler.Auto(*this, vertexShader, &DataT::vertexShader);
        autoHandler.Auto(*this, fragmentShader, &DataT::fragmentShader);
    }
}