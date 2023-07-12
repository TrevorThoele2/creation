
#include "Viewport.h"

#include "ViewportStateEntities.h"

#include "CurrentWorld.h"
#include "EntityViewManager.h"
#include "MoveOperation.h"
#include "Point.h"
#include "MainFrame.h"
#include "DataViewStateEntities.h"

#include <Atmos\EntityPositionSystem.h>
#include <Atmos\EntityNameSystem.h>
#include <Atmos\AvatarSystem.h>
#include <Atmos\Camera.h>

#include <wx\treectrl.h>

namespace Creation
{
    namespace Viewport
    {
        bool IsOverlappingEntityImpl(const std::vector<Build::Package<::Atmos::GridPosition>> &positions)
        {
            for (auto &loop : positions)
            {
                auto found = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>()->Find(loop);
                if (found)
                    return true;
            }

            return false;
        };

        ::Atmos::RenderFragment* MakeFragmentImpl(const Build::Package<::Atmos::Entity> &package)
        {
            auto &senseComponent = package.senseComponent;
            if (!senseComponent.valid.Build())
                return nullptr;

            if (senseComponent.value.sprites.value.empty())
                return nullptr;

            ::Atmos::Position3D highestPosition(package.generalComponent.position.Build());
            highestPosition.IncrementX(package.senseComponent.value.sprites.value.begin()->xOffset.Build());
            highestPosition.IncrementY(package.senseComponent.value.sprites.value.begin()->yOffset.Build());
            highestPosition.IncrementZ(package.senseComponent.value.sprites.value.begin()->zOffset.Build());
            const Build::Package<::Atmos::ObjectOffsetHandle<::Atmos::Sprite, ::Atmos::Position3D>> *highestSprite = &*package.senseComponent.value.sprites.value.begin();
            for (auto &loop : package.senseComponent.value.sprites.value)
            {
                ::Atmos::Position3D position(package.generalComponent.position.Build());
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

        Build::Package<::Atmos::GridPosition> GetGridPositionImpl(const Build::Package<::Atmos::Entity> &entity)
        {
            return entity.generalComponent.position;
        };

        StateEntities::CCPOperationT* StateEntities::CreateCCP()
        {
            void(*setGridPositionImpl)(PackageT&, const Build::Package<::Atmos::GridPosition>&) = [](PackageT &package, const Build::Package<::Atmos::GridPosition> &position)
            {
                package.generalComponent.position = position;
            };

            Image defaultImage(voidEntityImageName, ::Atmos::Color(127, 255, 255, 255));
            CCPOperationT *made = new CCPOperationT(&GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>()->breakdownList,
                std::move(defaultImage),
                std::move(CCPOperationT::IsOverlappingOuterFunc(&IsOverlappingEntityImpl)),
                std::move(CCPOperationT::MakeFragmentFunc(&MakeFragmentImpl)),
                std::move(CCPOperationT::SetGridPositionFunc(setGridPositionImpl)),
                std::move(CCPOperationT::GetGridPositionFunc(&GetGridPositionImpl)));
            return made;
        }

        StateEntities::MoveOperationT* StateEntities::CreateMove()
        {
            typedef MoveOperationT::MoveCommandT MoveCommandT;

            MoveCommandT*(*createMoveCommandImpl)(PackageT&, const Build::Package<::Atmos::GridPosition>&) = [](PackageT &entity, const Build::Package<::Atmos::GridPosition> &pos) -> MoveCommandT*
            {
                return MoveCommandT::Create(&GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>()->Find(entity)->generalComponent.position, pos, "Entity");
            };

            Image defaultImage(voidEntityImageName, ::Atmos::Color(127, 255, 255, 255));
            MoveOperationT *made = new MoveOperationT(std::move(defaultImage),
                std::move(MoveOperationT::IsOverlappingOuterFunc(&IsOverlappingEntityImpl)),
                std::move(MoveOperationT::MakeFragmentFunc(&MakeFragmentImpl)),
                std::move(MoveOperationT::GetGridPositionFunc(&GetGridPositionImpl)),
                std::move(MoveOperationT::CreateMoveCommandFunc(createMoveCommandImpl)));
            return made;
        }

        std::vector<StateEntities::PackageT*> StateEntities::CreateEntityVector()
        {
            std::vector<PackageT*> entities;
            for (auto &loop : selection)
                entities.push_back(&*loop);
            return entities;
        }

        std::vector<const StateEntities::PackageT*> StateEntities::CreateConstEntityVector()
        {
            std::vector<const PackageT*> entities;
            for (auto &loop : selection)
                entities.push_back(&*loop);
            return entities;
        }

        void StateEntities::ClearSelection()
        {
            selection.Clear();
            GetMainFrame()->GetDataView()->ClearSelection();
        }

        StateEntities::StateEntities(Viewport &viewport) : ignoreTreeItem(false)
        {}

        void StateEntities::Deselect()
        {
            ClearSelection();
        }

        void StateEntities::SelectItem(wxTreeItemId id)
        {
            if (ignoreTreeItem)
                return;

            auto data = static_cast<DataBreakdownWXItemData*>(GetMainFrame()->GetDataView()->Tree()->GetItemData(id))->data;
            if (typeid(*data) != typeid(DataBreakdown<Build::Package<::Atmos::Entity>>))
                return;

            auto entity = static_cast<DataBreakdown<Build::Package<::Atmos::Entity>>*>(data)->Get();
            selection.Add(entity);
        }

        void StateEntities::DeselectItem(wxTreeItemId id)
        {
            if (ignoreTreeItem)
                return;

            auto data = static_cast<DataBreakdownWXItemData*>(GetMainFrame()->GetDataView()->Tree()->GetItemData(id))->data;
            if (typeid(*data) != typeid(DataBreakdown<Build::Package<::Atmos::Entity>>))
                return;

            auto &entity = *static_cast<DataBreakdown<Build::Package<::Atmos::Entity>>*>(data)->Get();
            for (auto loop = selection.begin(); loop != selection.end(); ++loop)
            {
                if (**loop == entity)
                {
                    selection.Remove(loop);
                    break;
                }
            }
        }

        void StateEntities::OnDelete()
        {
            typedef Command::Remove<DataViewStateEntities::BreakdownListT> RemoveCommandT;

            if (selection.Empty())
                return;

            auto dataViewState = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>();
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

        void StateEntities::OnMove()
        {
            ClearSelection();
        }

        void StateEntities::ConsumeLeftBoxSelector(BoxOperation &box)
        {
            GetMainFrame()->GetDataView()->FreezeWidgets();

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

            ignoreTreeItem = true;

            while (position.y.Build() <= bottomRight.y.Build())
            {
                while (position.x.Build() <= bottomRight.x.Build())
                {
                    auto found = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>()->Find(position);
                    if (found)
                    {
                        selection.Add(found->Get());
                        GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>()->Select(*found->Get());
                    }

                    ++position.x.value;
                }

                ++position.y.value;
                position.x = topLeft.x;
            }

            ignoreTreeItem = false;

            GetMainFrame()->GetDataView()->ThawWidgets();
        }

        void StateEntities::ConsumeRightBoxSelector(BoxOperation &box)
        {
            typedef Command::Add<DataViewStateEntities::BreakdownListT> AddCommandT;
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

            auto dataViewState = GetMainFrame()->GetDataView()->GetSpecificState<DataViewStateEntities>();

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
                    nPackage.generalComponent.position = position;
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

        bool StateEntities::UsesRightBoxOperation() const
        {
            return true;
        }

        PreviewOperation* StateEntities::CreateMoveOperation()
        {
            MoveOperationT *move = CreateMove();
            move->Setup(CreateEntityVector());
            return move;
        }

        PreviewOperation* StateEntities::Cut()
        {
            CCPOperationT *ccp = CreateCCP();
            ccp->Cut(CreateConstEntityVector());
            return ccp;
        }

        PreviewOperation* StateEntities::Copy()
        {
            CCPOperationT *ccp = CreateCCP();
            ccp->Copy(CreateConstEntityVector());
            return ccp;
        }

        bool StateEntities::IsSelectionEmpty() const
        {
            return selection.Empty();
        }

        bool StateEntities::IsMouseOverSelection(const Point &pt) const
        {
            const ::Atmos::GridPosition mouseGridPos(::Atmos::Position2D(::Atmos::Position2D::FromScreen(::Atmos::Position2D(pt), ::Atmos::Camera::GetTopLeft())), viewport->GetZView());
            for (auto &loop : selection)
            {
                if (loop->generalComponent.position.Build() == mouseGridPos)
                    return true;
            }

            return false;
        }
    }
}