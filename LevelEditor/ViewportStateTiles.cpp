
#include "Viewport.h"

#include "ViewportStateTiles.h"

#include "MoveOperation.h"
#include "CommandStack.h"
#include "TileViewManager.h"

#include "MainFrame.h"
#include "DataViewStateTiles.h"
#include "CurrentWorld.h"

#include <Atmos\GridSize.h>
#include <Atmos\Camera.h>

#include <wx\treectrl.h>

namespace Creation
{
    namespace Viewport
    {
        bool IsOverlappingTileImpl(const std::vector<Build::Package<::Atmos::GridPosition>> &positions)
        {
            for (auto &loop : positions)
            {
                auto found = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateTiles>()->Find(loop);
                if (found)
                    return true;
            }

            return false;
        };

        ::Atmos::RenderFragment* MakeFragmentImpl(const Build::Package<::Atmos::Tile> &package)
        {
            if (package.sprites.value.empty())
                return nullptr;

            ::Atmos::Position3D highestPosition(package.position.Build());
            highestPosition.IncrementX(package.sprites.value.begin()->xOffset.Build());
            highestPosition.IncrementY(package.sprites.value.begin()->yOffset.Build());
            highestPosition.IncrementZ(package.sprites.value.begin()->zOffset.Build());
            const Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>> *highestSprite = &*package.sprites.value.begin();
            for (auto &loop : package.sprites.value)
            {
                ::Atmos::Position3D position(package.position.Build());
                position.IncrementX(loop.xOffset.Build());
                position.IncrementY(loop.yOffset.Build());
                position.IncrementZ(loop.zOffset.Build());
                if (position.GetZ() > highestPosition.GetZ())
                {
                    highestPosition = position;
                    highestSprite = &loop;
                }
            }

            return new ::Atmos::Sprite(highestSprite->wrapped.Build());
        };

        Build::Package<::Atmos::GridPosition> GetGridPositionImpl(const Build::Package<::Atmos::Tile> &tile)
        {
            return tile.position;
        };

        StateTiles::CCPOperationT* StateTiles::CreateCCP()
        {
            void(*setGridPositionImpl)(PackageT&, const Build::Package<::Atmos::GridPosition>&) = [](PackageT &package, const Build::Package<::Atmos::GridPosition> &position)
            {
                package.position = position;
            };

            Image defaultImage(voidTileImageName, ::Atmos::Color(127, 255, 255, 255));
            CCPOperationT *made = new CCPOperationT(&GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateTiles>()->breakdownList,
                std::move(defaultImage),
                std::move(CCPOperationT::IsOverlappingOuterFunc(&IsOverlappingTileImpl)),
                std::move(CCPOperationT::MakeFragmentFunc(&MakeFragmentImpl)),
                std::move(CCPOperationT::SetGridPositionFunc(setGridPositionImpl)),
                std::move(CCPOperationT::GetGridPositionFunc(&GetGridPositionImpl)));
            return made;
        }

        StateTiles::MoveOperationT* StateTiles::CreateMove()
        {
            typedef MoveOperationT::MoveCommandT MoveCommandT;

            MoveCommandT*(*createMoveCommandImpl)(PackageT&, const Build::Package<::Atmos::GridPosition>&) = [](PackageT &tile, const Build::Package<::Atmos::GridPosition> &pos) -> MoveCommandT*
            {
                return MoveCommandT::Create(&GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateTiles>()->Find(tile)->position, pos, "Tile");
            };

            Image defaultImage(voidTileImageName, ::Atmos::Color(127, 255, 255, 255));
            MoveOperationT *made = new MoveOperationT(std::move(defaultImage),
                std::move(MoveOperationT::IsOverlappingOuterFunc(&IsOverlappingTileImpl)),
                std::move(MoveOperationT::MakeFragmentFunc(&MakeFragmentImpl)),
                std::move(MoveOperationT::GetGridPositionFunc(&GetGridPositionImpl)),
                std::move(MoveOperationT::CreateMoveCommandFunc(createMoveCommandImpl)));
            return made;
        }

        std::vector<StateTiles::PackageT*> StateTiles::CreateTileVector()
        {
            std::vector<PackageT*> tiles;
            for (auto &loop : selection)
                tiles.push_back(&*loop);
            return tiles;
        }

        std::vector<const StateTiles::PackageT*> StateTiles::CreateConstTileVector() const
        {
            std::vector<const PackageT*> tiles;
            for (auto &loop : selection)
                tiles.push_back(&*loop);
            return tiles;
        }

        void StateTiles::ClearSelection()
        {
            selection.Clear();
            GetMainFrame()->GetDataView()->ClearSelection();
        }

        StateTiles::StateTiles(Viewport &viewport) : ignoreTreeItem(false)
        {}

        void StateTiles::Deselect()
        {
            ClearSelection();
        }

        void StateTiles::SelectItem(wxTreeItemId id)
        {
            if (ignoreTreeItem)
                return;

            auto data = static_cast<DataBreakdownWXItemData*>(GetMainFrame()->GetDataView()->Tree()->GetItemData(id))->data;
            if (typeid(*data) != typeid(DataBreakdown<::Atmos::Tile>))
                return;

            auto tile = static_cast<DataBreakdown<Build::Package<::Atmos::Tile>>*>(data)->Get();
            selection.Add(tile);
        }

        void StateTiles::DeselectItem(wxTreeItemId id)
        {
            if (ignoreTreeItem)
                return;

            auto data = static_cast<DataBreakdownWXItemData*>(GetMainFrame()->GetDataView()->Tree()->GetItemData(id))->data;
            if (typeid(*data) != typeid(DataBreakdown<Build::Package<::Atmos::Tile>>))
                return;

            auto &tile = *static_cast<DataBreakdown<Build::Package<::Atmos::Tile>>*>(data)->Get();
            for (auto loop = selection.begin(); loop != selection.end(); ++loop)
            {
                if (**loop == tile)
                {
                    selection.Remove(loop);
                    break;
                }
            }
        }

        void StateTiles::OnDelete()
        {
            typedef Command::Remove<DataViewStateTiles::BreakdownListT> RemoveCommandT;

            if (selection.Empty())
                return;

            auto dataViewState = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateTiles>();
            if (selection.size() == 1)
            {
                for (auto loop = dataViewState->breakdownList.begin(); loop != dataViewState->breakdownList.end(); ++loop)
                {
                    if (&*loop->Get() == &**selection.begin())
                    {
                        RemoveCommandT::Create(&dataViewState->breakdownList, loop)->Commit();
                        return;
                    }
                }
            }

            auto groupCommand = Command::Group<RemoveCommandT>::Create();
            for (auto selLoop = selection.begin(); selLoop != selection.end(); ++selLoop)
            {
                for (auto loop = dataViewState->breakdownList.begin(); loop != dataViewState->breakdownList.end(); ++loop)
                {
                    if (&*loop->Get() == &**selLoop)
                        groupCommand->Add(RemoveCommandT::Create(&dataViewState->breakdownList, loop));
                }
            }

            groupCommand->Commit();
            ClearSelection();
        }

        void StateTiles::OnMove()
        {
            ClearSelection();
        }

        void StateTiles::ConsumeLeftBoxSelector(BoxOperation &box)
        {
            if (!wxGetKeyState(wxKeyCode::WXK_CONTROL))
                ClearSelection();

            typedef Build::Package<::Atmos::GridPosition> PositionPackageT;

            auto &bounds = box.GetBounds();
            PositionPackageT topLeft;
            topLeft.x.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.left);
            topLeft.y.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.top);
            topLeft.z.value = viewport->GetZView();
            PositionPackageT bottomRight;
            bottomRight.x.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.right);
            bottomRight.y.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.bottom);
            bottomRight.z.value = viewport->GetZView();
            PositionPackageT position(topLeft);

            std::vector<Build::Package<::Atmos::GridPosition>> positions;

            ignoreTreeItem = true;
            while (position.y.Build() <= bottomRight.y.Build())
            {
                while (position.x.Build() <= bottomRight.x.Build())
                {
                    auto found = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateTiles>()->Find(position);
                    if (found)
                    {
                        selection.Add(found->Get());
                        positions.push_back(position);
                    }

                    ++position.x.value;
                }

                ++position.y.value;
                position.x = topLeft.x;
            }
            GetMainFrame()->GetDataView()->GetCurrentState<DataViewStateTiles>()->Select(positions);
            ignoreTreeItem = false;
        }

        void StateTiles::ConsumeRightBoxSelector(BoxOperation &box)
        {
            typedef Command::Add<DataViewStateTiles::BreakdownListT> AddCommandT;
            typedef Build::Package<::Atmos::GridPosition> PositionPackageT;

            GetMainFrame()->GetDataView()->FreezeWidgets();

            auto &bounds = box.GetBounds();
            PositionPackageT topLeft;
            topLeft.x.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.left);
            topLeft.y.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.top);
            topLeft.z.value = viewport->GetZView();
            PositionPackageT bottomRight;
            bottomRight.x.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.right);
            bottomRight.y.value = ::Atmos::GridPosition::DimensionFromPosition(bounds.bottom);
            bottomRight.z.value = viewport->GetZView();
            PositionPackageT position(topLeft);

            auto dataViewState = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateTiles>();

            ignoreTreeItem = true;
            std::vector<PackageT> makePackages;
            while (position.y.value <= bottomRight.y.value)
            {
                while (position.x.value <= bottomRight.x.value)
                {
                    if (dataViewState->Find(position))
                    {
                        ++position.x.value;
                        continue;
                    }

                    PackageT nPackage;
                    nPackage.position = position;
                    makePackages.push_back(std::move(nPackage));
                    ++position.x.value;
                }

                ++position.y.value;
                position.x = topLeft.x;
            }
            ignoreTreeItem = false;

            if (makePackages.empty())
            {
                GetMainFrame()->GetDataView()->ThawWidgets();
                return;
            }

            if (makePackages.size() == 1)
                AddCommandT::Create(&dataViewState->breakdownList, *makePackages.begin())->Commit();
            else
            {
                auto groupCommand = Command::Group<AddCommandT>::Create();
                for (auto &loop : makePackages)
                    groupCommand->Add(AddCommandT::Create(&dataViewState->breakdownList, loop));
                groupCommand->Commit();
            }

            GetMainFrame()->GetDataView()->ThawWidgets();
        }

        bool StateTiles::UsesRightBoxOperation() const
        {
            return true;
        }

        PreviewOperation* StateTiles::CreateMoveOperation()
        {
            MoveOperationT *move = CreateMove();
            move->Setup(CreateTileVector());
            return move;
        }

        PreviewOperation* StateTiles::Cut()
        {
            CCPOperationT *ccp = CreateCCP();
            ccp->Cut(CreateConstTileVector());
            return ccp;
        }

        PreviewOperation* StateTiles::Copy()
        {
            CCPOperationT *ccp = CreateCCP();
            ccp->Copy(CreateConstTileVector());
            return ccp;
        }

        bool StateTiles::IsSelectionEmpty() const
        {
            return selection.Empty();
        }

        bool StateTiles::IsMouseOverSelection(const Point &pt) const
        {
            const ::Atmos::GridPosition mouseGridPos(::Atmos::Position2D(::Atmos::Position2D::FromScreen(::Atmos::Position2D(pt), ::Atmos::Camera::GetTopLeft())), viewport->GetZView());
            for (auto &loop : selection)
            {
                if (loop->position.Build() == mouseGridPos)
                    return true;
            }

            return false;
        }
    }
}