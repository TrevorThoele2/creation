#pragma once

#include "DataRoot.h"

#include "ListData.h"
#include "StaticImageData.h"

namespace Creation::Editing::Data
{
    class TerrainRoot final : public Root
    {
    public:
        struct Input
        {
            std::list<StaticImage>* terrain;
            Arca::Reliquary* reliquary;
            bool visible;
            const NexusHistory* nexusHistory;
            UI* ui;
        };
    public:
        Nexus<std::list<StaticImage>> terrain;
    public:
        TerrainRoot(Input& input);
        TerrainRoot(const TerrainRoot& arg) = delete;
        TerrainRoot(TerrainRoot&& arg) noexcept = default;
    protected:
        [[nodiscard]] std::vector<SequenceNexusBase*> TopNexi() override;
    };
}