#pragma once

#include "GhostWorldElementBase.h"

namespace Creation::Editing
{
    class NexusNode;

    class WorldElementBase
    {
    public:
        virtual ~WorldElementBase() = 0;

        void Select();
        void Deselect();

        void Show();
        void Hide();
        [[nodiscard]] bool IsShown() const;

        [[nodiscard]] std::unique_ptr<GhostWorldElementBase> CreateGhost() const;
    public:
        [[nodiscard]] virtual NexusNode& UnderlyingNexusNode() = 0;
        [[nodiscard]] virtual const NexusNode& UnderlyingNexusNode() const = 0;
    protected:
        WorldElementBase() = default;
        WorldElementBase(WorldElementBase&& arg) noexcept = default;
        WorldElementBase& operator=(WorldElementBase&& arg) noexcept = default;

        virtual void DoSelect();
        virtual void DoDeselect();

        virtual void DoShow();
        virtual void DoHide();

        [[nodiscard]] virtual std::unique_ptr<GhostWorldElementBase> CreateGhostImpl() const = 0;
    private:
        bool isShown = true;
    };
}