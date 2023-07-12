
#include "DataBreakdownModulators.h"

#include <Function/Variant.h>

namespace Creation
{
    struct ModulatorGeneralStrategies
    {
        enum class StrategyType
        {
            CREATE_EDITOR_PROPERTIES,
            UPDATE_EDITOR_PROPERTIES,
            DESTROY_EDITOR_PROPERTIES,
            SET_EDITABLE,
            CREATE_TREE_PIECE,
            DESELECT,
            SELECT_SECONDARY,
            IS_PRIMARY
        };

        template<StrategyType strategy>
        using Selector = ::function::StrategySelector<StrategyType, strategy>;

        template<class T>
        static void Do(T &breakdown, const DataBreakdownCommon::ChildReference &afterThis, Selector<StrategyType::CREATE_EDITOR_PROPERTIES>)
        {
            breakdown.CreateEditorProperties(afterThis);
        }

        template<class T>
        static void Do(T &breakdown, Selector<StrategyType::UPDATE_EDITOR_PROPERTIES>)
        {
            breakdown.UpdateEditorProperties();
        }

        template<class T>
        static void Do(T &breakdown, bool destroyTreeItem, Selector<StrategyType::DESTROY_EDITOR_PROPERTIES>)
        {
            breakdown.DestroyEditorProperties(destroyTreeItem);
        }

        template<class T>
        static void Do(T &breakdown, wxTreeItemId parentTreeID, const DataBreakdownCommon::ChildReference &afterThis, Selector<StrategyType::CREATE_TREE_PIECE>)
        {
            breakdown.CreateTreePiece(parentTreeID, afterThis);
        }

        template<class T>
        static void Do(T &breakdown, bool set, Selector<StrategyType::SET_EDITABLE>)
        {
            breakdown.SetEditable(set);
        }

        template<class T>
        static void Do(T &breakdown, Selector<StrategyType::DESELECT>)
        {
            breakdown.DeselectThis();
        }

        template<class T>
        static void Do(T &breakdown, Selector<StrategyType::SELECT_SECONDARY>)
        {
            breakdown.SelectThisSecondary();
        }

        template<class T>
        static bool DoReturn(T &breakdown, Selector<StrategyType::IS_PRIMARY>)
        {
            return breakdown.IsSelectedPrimary();
        }
    };

    template<ModulatorGeneralStrategies::StrategyType strategy>
    using StrategySelector = ::function::StrategySelector<ModulatorGeneralStrategies::StrategyType, strategy>;

    struct ValueSetupStrategies
    {
        static void Do(DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::IntBreakdownT &breakdown, Build::Package<::Atmos::Modulator::Value> &package)
        {
            breakdown.Setup(*package.variant.GetAsRaw<Build::Package<::Atmos::Modulator::Value>::IntPackage>());
        }

        static void Do(DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::FloatBreakdownT &breakdown, Build::Package<::Atmos::Modulator::Value> &package)
        {
            breakdown.Setup(*package.variant.GetAsRaw<Build::Package<::Atmos::Modulator::Value>::FloatPackage>());
        }

        static DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::ChildVariantT DoReturn(DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::IntBreakdownT &variantBreakdown, DataBreakdown<Build::Package<::Atmos::Modulator::Value>> *breakdown)
        {
            typedef DataBreakdown<Build::Package<::Atmos::Modulator::Value>> UnderlyingBreakdownT;
            return UnderlyingBreakdownT::ChildVariantT(UnderlyingBreakdownT::IntBreakdownT(std::move(variantBreakdown), breakdown));
        }

        static DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::ChildVariantT DoReturn(DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::FloatBreakdownT &variantBreakdown, DataBreakdown<Build::Package<::Atmos::Modulator::Value>> *breakdown)
        {
            typedef DataBreakdown<Build::Package<::Atmos::Modulator::Value>> UnderlyingBreakdownT;
            return UnderlyingBreakdownT::ChildVariantT(UnderlyingBreakdownT::FloatBreakdownT(std::move(variantBreakdown), breakdown));
        }
    };

    struct NodeEntrySetupStrategies
    {
        // Setup
        static void Do(Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal &package, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> &breakdown)
        {
            breakdown.endStateVariant.Set(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal("End State", &breakdown));
            breakdown.endStateVariant.Get<DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal>().Setup(package);
        }

        // Setup
        static void Do(Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom &package, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> &breakdown)
        {
            breakdown.endStateVariant.Set(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom("End State", &breakdown));
            breakdown.endStateVariant.Get<DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom>().Setup(package);
        }

        // Setup
        static void Do(Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear &package, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> &breakdown)
        {
            breakdown.interpolationVariant.Set(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear("Interpolation", &breakdown));
            breakdown.interpolationVariant.Get<DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear>().Setup(package);
        }

        // Setup
        static void Do(Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation &package, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> &breakdown)
        {
            breakdown.interpolationVariant.Set(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation("Interpolation", &breakdown));
            breakdown.interpolationVariant.Get<DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation>().Setup(package);
        }

        // Create package variant from breakdown
        static DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateVariantT DoReturn(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal &variantBreakdown, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> *breakdown)
        {
            typedef DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> UnderlyingBreakdownT;
            return UnderlyingBreakdownT::EndStateVariantT(UnderlyingBreakdownT::EndStateNormal(std::move(variantBreakdown), breakdown));
        }

        // Create package variant from breakdown
        static DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateVariantT DoReturn(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom &variantBreakdown, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> *breakdown)
        {
            typedef DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> UnderlyingBreakdownT;
            return UnderlyingBreakdownT::EndStateVariantT(UnderlyingBreakdownT::EndStateRandom(std::move(variantBreakdown), breakdown));
        }

        // Create package variant from breakdown
        static DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationVariantT DoReturn(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear &variantBreakdown, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> *breakdown)
        {
            typedef DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> UnderlyingBreakdownT;
            return UnderlyingBreakdownT::InterpolationVariantT(UnderlyingBreakdownT::InterpolationLinear(std::move(variantBreakdown), breakdown));
        }

        // Create package variant from breakdown
        static DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationVariantT DoReturn(DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation &variantBreakdown, DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> *breakdown)
        {
            typedef DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> UnderlyingBreakdownT;
            return UnderlyingBreakdownT::InterpolationVariantT(UnderlyingBreakdownT::InterpolationOscillation(std::move(variantBreakdown), breakdown));
        }

        // Set the variant package's type
        static void Do(Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal &variantPackage, ::Atmos::Modulator::Value::Type type)
        {
            variantPackage.value.type.value = static_cast<std::underlying_type<::Atmos::Modulator::Value::Type>::type>(type);
            variantPackage.value.SetType(type);
        }

        // Set the variant package's type
        static void Do(Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom &variantPackage, ::Atmos::Modulator::Value::Type type)
        {
            variantPackage.value.first.type.value = static_cast<std::underlying_type<::Atmos::Modulator::Value::Type>::type>(type);
            variantPackage.value.first.SetType(type);
            variantPackage.value.second.type.value = static_cast<std::underlying_type<::Atmos::Modulator::Value::Type>::type>(type);
            variantPackage.value.second.SetType(type);
        }
    };

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::OnTypeChanged(const DataBreakdownEditArgs &args)
    {
        switch (type.GetAsEnum())
        {
        case BuildT::Type::INT:
            variant.Set(IntBreakdownT("Value", this));
            break;
        case BuildT::Type::FLOAT:
            variant.Set(FloatBreakdownT("Value", this));
            break;
        }
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::AddAllChildren()
    {
        AddChild(type);
        if (variant.Is<IntBreakdownT>())
            AddChild(variant.Get<IntBreakdownT>());
        else if (variant.Is<FloatBreakdownT>())
            AddChild(variant.Get<FloatBreakdownT>());
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::SetupImpl()
    {
        type.Setup(Get()->type);
        ::function::Visit<ValueSetupStrategies>(variant, *Get());
        type.Get()->value = variant.GetTypeAsID();
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        type.CreateEditorProperties(afterThis);
        ::function::Visit<ModulatorGeneralStrategies>(variant, afterThis, StrategySelector<ModulatorGeneralStrategies::StrategyType::CREATE_EDITOR_PROPERTIES>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        type.UpdateEditorProperties();
        ::function::Visit<ModulatorGeneralStrategies>(variant, StrategySelector<ModulatorGeneralStrategies::StrategyType::UPDATE_EDITOR_PROPERTIES>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        type.DestroyEditorProperties(destroyTreeItem);
        ::function::Visit<ModulatorGeneralStrategies>(variant, destroyTreeItem, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESTROY_EDITOR_PROPERTIES>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::SetEditableImpl(bool set)
    {
        type.SetEditable(set);
        ::function::Visit<ModulatorGeneralStrategies>(variant, set, StrategySelector<ModulatorGeneralStrategies::StrategyType::SET_EDITABLE>{});
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        type("Type", this),
        variant(IntBreakdownT("Value", this))
    {
        AddAllChildren();
        type.RemoveData(BuildT::Type::NONE);
        type.SetEditable(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        type(std::move(arg.type), this),
        variant(::function::VisitReturn<ValueSetupStrategies, ChildVariantT>(arg.variant, this))
    {
        AddAllChildren();
        type.RemoveData(BuildT::Type::NONE);
        type.SetEditable(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::Value>>& DataBreakdown<Build::Package<::Atmos::Modulator::Value>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        type = std::move(arg.type);
        variant = std::move(arg.variant);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::OnEndStateTypeChanged(const DataBreakdownEditArgs &args)
    {
        typedef ::Atmos::Modulator::TrackNodeEndState::Type EndStateType;

        DataBreakdownCommon *made = nullptr;
        ChildReference prevChild;

        // Figure out if the variant is primary selected
        // Also, deselect it
        bool isPrimary = ::function::VisitReturn<ModulatorGeneralStrategies, bool>(endStateVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::IS_PRIMARY>{});
        // Destroy editor properties, which includes the tree piece (important)
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, true, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESTROY_EDITOR_PROPERTIES>{});
        // Now deselect
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESELECT>{});

        switch (static_cast<EndStateType>(endStateType.Get()->Build()))
        {
        case EndStateType::NORMAL:
        {
            // Set the variant correctly
            endStateVariant.Set(EndStateNormal("Normal", this));
            // Retrieve the underlying type we just set
            auto &got = endStateVariant.Get<EndStateNormal>();
            // Get the previous child (for insertion later)
            prevChild = ChildReference(Child(static_cast<DataBreakdownCommon*>(&got))).Previous();
            // Remove the created child
            RemoveChild(got);
            // Setup the variant in the underlying package correctly
            Get()->endStateVariant.Set(PackageT::EndStateNormal());
            // Now, setup our new object with the newly created package
            got.Setup(Get()->endStateVariant.Get<PackageT::EndStateNormal>());
            made = &got;
            break;
        }
        case EndStateType::RANDOM:
        {
            // Set the variant correctly
            endStateVariant.Set(EndStateRandom("Random", this));
            // Retrieve the underlying type we just set
            auto &got = endStateVariant.Get<EndStateRandom>();
            // Get the previous child (for insertion later)
            prevChild = ChildReference(Child(static_cast<DataBreakdownCommon*>(&got))).Previous();
            // Remove the created child
            RemoveChild(got);
            // Setup the variant in the underlying package correctly
            Get()->endStateVariant.Set(PackageT::EndStateRandom());
            // Now, setup our new object with the newly created package
            got.Setup(Get()->endStateVariant.Get<PackageT::EndStateRandom>());
            made = &got;
            break;
        }
        }

        // The common setup to all breakdowns
        InsertChild(*made, *prevChild);
        // Reselect what we made (it'll always be selected)
        (isPrimary) ? made->SelectThisPrimary() : made->SelectThisSecondary();
        // Reinsert the stuff
        ReinsertTreePiece(*made);
        ReinsertEditorProperties(*made);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::OnInterpolationTypeChanged(const DataBreakdownEditArgs &args)
    {
        typedef ::Atmos::Modulator::TrackNodeInterpolation::Type InterpolationType;

        DataBreakdownCommon *made = nullptr;
        ChildReference prevChild;

        // Figure out if the variant is primary selected
        // Also, deselect it
        bool isPrimary = ::function::VisitReturn<ModulatorGeneralStrategies, bool>(interpolationVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::IS_PRIMARY>{});
        // Destroy editor properties, which includes the tree piece (important)
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, true, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESTROY_EDITOR_PROPERTIES>{});
        // Now deselect
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESELECT>{});

        switch (static_cast<InterpolationType>(interpolationType.Get()->Build()))
        {
        case InterpolationType::LINEAR:
        {
            // Set the variant correctly
            interpolationVariant.Set(InterpolationLinear("Linear", this));
            // Retrieve the underlying type we just set
            auto &got = interpolationVariant.Get<InterpolationLinear>();
            // Get the previous child (for insertion later)
            prevChild = ChildReference(Child(static_cast<DataBreakdownCommon*>(&got))).Previous();
            // Remove the created child
            RemoveChild(got);
            // Setup the variant in the underlying package correctly
            Get()->interpolationVariant.Set(PackageT::InterpolationLinear());
            // Now, setup our new object with the newly created package
            got.Setup(Get()->interpolationVariant.Get<PackageT::InterpolationLinear>());
            made = &got;
            break;
        }
        case InterpolationType::OSCILLATION:
        {
            // Set the variant correctly
            interpolationVariant.Set(InterpolationOscillation("Oscillation", this));
            // Retrieve the underlying type we just set
            auto &got = interpolationVariant.Get<InterpolationOscillation>();
            // Get the previous child (for insertion later)
            prevChild = ChildReference(Child(static_cast<DataBreakdownCommon*>(&got))).Previous();
            // Remove the created child
            RemoveChild(got);
            // Setup the variant in the underlying package correctly
            Get()->interpolationVariant.Set(PackageT::InterpolationOscillation());
            // Now, setup our new object with the newly created package
            got.Setup(Get()->interpolationVariant.Get<PackageT::InterpolationOscillation>());
            made = &got;
            break;
        }
        }

        // The common setup to all breakdowns
        InsertChild(*made, *prevChild);
        // Reselect what we made (it'll always be selected)
        (isPrimary) ? made->SelectThisPrimary() : made->SelectThisSecondary();
        // Reinsert the stuff
        ReinsertTreePiece(*made);
        ReinsertEditorProperties(*made);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::AddAllChildren()
    {
        AddChild(endStateType);
        if (endStateVariant.Is<EndStateNormal>())
            AddChild(endStateVariant.Get<EndStateNormal>());
        else if (endStateVariant.Is<EndStateRandom>())
            AddChild(endStateVariant.Get<EndStateRandom>());

        AddChild(interpolationType);
        if (interpolationVariant.Is<InterpolationLinear>())
            AddChild(interpolationVariant.Get<InterpolationLinear>());
        else if (interpolationVariant.Is<InterpolationOscillation>())
            AddChild(interpolationVariant.Get<InterpolationOscillation>());
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::SubscribeEvents()
    {
        endStateType.edited.Subscribe(&DataBreakdown::OnEndStateTypeChanged, *this);
        interpolationType.edited.Subscribe(&DataBreakdown::OnInterpolationTypeChanged, *this);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::SetupImpl()
    {
        endStateType.Setup(Get()->endStateType);
        ::function::Visit<NodeEntrySetupStrategies>(Get()->endStateVariant, *this);
        interpolationType.Setup(Get()->interpolationType);
        ::function::Visit<NodeEntrySetupStrategies>(Get()->interpolationVariant, *this);

        endStateType.Get()->value = endStateVariant.GetTypeAsID();
        interpolationType.Get()->value = interpolationVariant.GetTypeAsID();
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::CreateEditorPropertiesImpl(const ChildReference &afterThis)
    {
        endStateType.CreateEditorProperties(afterThis);
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, afterThis, StrategySelector<ModulatorGeneralStrategies::StrategyType::CREATE_EDITOR_PROPERTIES>{});
        interpolationType.CreateEditorProperties(afterThis);
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, afterThis, StrategySelector<ModulatorGeneralStrategies::StrategyType::CREATE_EDITOR_PROPERTIES>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::UpdateEditorPropertiesImpl(DataViewSelection::Group &selected)
    {
        endStateType.UpdateEditorProperties();
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::UPDATE_EDITOR_PROPERTIES>{});
        interpolationType.UpdateEditorProperties();
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::UPDATE_EDITOR_PROPERTIES>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::DestroyEditorPropertiesImpl(bool destroyTreeItem)
    {
        endStateType.DestroyEditorProperties(destroyTreeItem);
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, destroyTreeItem, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESTROY_EDITOR_PROPERTIES>{});
        interpolationType.DestroyEditorProperties(destroyTreeItem);
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, destroyTreeItem, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESTROY_EDITOR_PROPERTIES>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::CreateTreePieceImpl(wxTreeItemId parentItemID, const ChildReference &afterThis)
    {
        endStateType.CreateTreePiece(GetTreeItemID(), afterThis);
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, GetTreeItemID(), afterThis, StrategySelector<ModulatorGeneralStrategies::StrategyType::CREATE_TREE_PIECE>{});
        interpolationType.CreateTreePiece(GetTreeItemID(), afterThis);
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, GetTreeItemID(), afterThis, StrategySelector<ModulatorGeneralStrategies::StrategyType::CREATE_TREE_PIECE>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::ChangeSelectImpl(SelectedState state)
    {
        if (state == SelectedState::NONE)
        {
            endStateType.DeselectThis();
            ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESELECT>{});
            interpolationType.DeselectThis();
            ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::DESELECT>{});
        }
        else
        {
            endStateType.SelectThisSecondary();
            ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::SELECT_SECONDARY>{});
            interpolationType.SelectThisSecondary();
            ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, StrategySelector<ModulatorGeneralStrategies::StrategyType::SELECT_SECONDARY>{});
        }
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::SetEditableImpl(bool set)
    {
        endStateType.SetEditable(set);
        ::function::Visit<ModulatorGeneralStrategies>(endStateVariant, set, StrategySelector<ModulatorGeneralStrategies::StrategyType::SET_EDITABLE>{});
        interpolationType.SetEditable(set);
        ::function::Visit<ModulatorGeneralStrategies>(interpolationVariant, set, StrategySelector<ModulatorGeneralStrategies::StrategyType::SET_EDITABLE>{});
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal::AddAllChildren()
    {
        AddChild(value);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal::SetupImpl()
    {
        value.Setup(Get()->value);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal::EndStateNormal(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        value("Value", this)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
        value.SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal::EndStateNormal(EndStateNormal &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        value(std::move(arg.value), this)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
        value.SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateNormal::operator=(EndStateNormal &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        value = std::move(arg.value);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom::AddAllChildren()
    {
        AddChild(value);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom::SetupImpl()
    {
        value.Setup(Get()->value);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom::EndStateRandom(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        value("Value", this)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
        value.SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom::EndStateRandom(EndStateRandom &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        value(std::move(arg.value), this)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
        value.SetAddCategory(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::EndStateRandom::operator=(EndStateRandom &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        value = std::move(arg.value);
        return *this;
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear::InterpolationLinear(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear::InterpolationLinear(InterpolationLinear &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationLinear::operator=(InterpolationLinear &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation::AddAllChildren()
    {
        AddChild(acceleration);
        AddChild(rate);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation::SetupImpl()
    {
        acceleration.Setup(Get()->acceleration);
        rate.Setup(Get()->rate);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation::InterpolationOscillation(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        acceleration("Acceleration", this),
        rate("Rate", this)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation::InterpolationOscillation(InterpolationOscillation &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        acceleration(std::move(arg.acceleration), this),
        rate(std::move(arg.rate), this)
    {
        AddAllChildren();
        SetAddCategory(false);
        SetAddTreePiece(false);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::InterpolationOscillation::operator=(InterpolationOscillation &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        acceleration = std::move(arg.acceleration);
        rate = std::move(arg.rate);
        return *this;
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        endStateType("End State Type", this),
        endStateVariant(EndStateNormal("End State", this)),
        interpolationType("Interpolation Type", this),
        interpolationVariant(InterpolationLinear("Linear", this))
    {
        AddAllChildren();
        SubscribeEvents();
        SetAddChildrenToProperties(false);
        SetAddChildrenToTree(false);
        endStateType.RemoveData(::Atmos::Modulator::TrackNodeEndState::Type::NONE);
        interpolationType.RemoveData(::Atmos::Modulator::TrackNodeInterpolation::Type::NONE);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        endStateType(std::move(arg.endStateType), this),
        endStateVariant(::function::VisitReturn<NodeEntrySetupStrategies, EndStateVariantT>(arg.endStateVariant, this)),
        interpolationType(std::move(arg.interpolationType), this),
        interpolationVariant(::function::VisitReturn<NodeEntrySetupStrategies, InterpolationVariantT>(arg.interpolationVariant, this))
    {
        AddAllChildren();
        SubscribeEvents();
        SetAddChildrenToProperties(false);
        SetAddChildrenToTree(false);
        endStateType.RemoveData(::Atmos::Modulator::TrackNodeEndState::Type::NONE);
        interpolationType.RemoveData(::Atmos::Modulator::TrackNodeInterpolation::Type::NONE);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        endStateType = std::move(arg.endStateType);
        endStateVariant = std::move(arg.endStateVariant);
        interpolationType = std::move(arg.interpolationType);
        interpolationVariant = std::move(arg.interpolationVariant);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>::ForceEditValueType(::Atmos::Modulator::Value::Type force)
    {
        ::function::Visit<NodeEntrySetupStrategies>(Get()->endStateVariant, force);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>::OnPrototypeChanged(const DataBreakdownEditArgs &args)
    {
        auto type = ModulatorGroups::GetTypeForTrack(static_cast<DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>*>(GetParent())->prototype.Get()->value, prototype.Get()->value);
        for (auto &loop : nodes)
            loop.ForceEditValueType(type);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>::AddAllChildren()
    {
        AddChild(prototype);
        AddChild(nodes);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>::SetupImpl()
    {
        prototype.Setup(Get()->prototype);
        nodes.Setup(Get()->nodes);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        prototype("Prototype", this),
        nodes("Nodes", this)
    {
        AddAllChildren();
        nodes.SetPrependEntryName("Node");
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        prototype(std::move(arg.prototype), this),
        nodes(std::move(arg.nodes), this)
    {
        AddAllChildren();
        nodes.SetPrependEntryName("Node");
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prototype = std::move(arg.prototype);
        nodes = std::move(arg.nodes);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::OnPrototypeChanged(const DataBreakdownEditArgs &args)
    {
        SyncTrackGroups();
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::OnTrackAdded(const DataBreakdownAddArgs &args)
    {
        auto added = static_cast<decltype(tracks)::BreakdownT*>(args.Added());
        added->prototype.SetGroup(ModulatorGroups::GetTrackGroup(prototype.Get()->Build()));
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::SyncTrackGroups()
    {
        // Reset the groups inside of the tracks
        for (auto &loop : tracks)
            loop.prototype.SetGroup(ModulatorGroups::GetTrackGroup(prototype.Get()->Build()));
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::AddAllChildren()
    {
        AddChild(prototype);
        AddChild(tracks);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::SubscribeEvents()
    {
        prototype.edited.Subscribe(&DataBreakdown::OnPrototypeChanged, *this);
        tracks.added.Subscribe(&DataBreakdown::OnTrackAdded, *this);
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::SetupImpl()
    {
        prototype.Setup(Get()->prototype);
        tracks.Setup(Get()->tracks);
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::DataBreakdown(const String &name, DataBreakdownCommon *parent) : DataBreakdownBase(name, parent),
        prototype("Prototype", this),
        tracks("Tracks", this)
    {
        AddAllChildren();
        SubscribeEvents();
        prototype.SetEditable(false);
        tracks.SetPrependEntryName("Track");
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent) : DataBreakdownBase(std::move(arg), parent),
        prototype(std::move(arg.prototype), this),
        tracks(std::move(arg.tracks), this)
    {
        AddAllChildren();
        SubscribeEvents();
        prototype.SetEditable(false);
        tracks.SetPrependEntryName("Track");
    }

    DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>& DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::operator=(DataBreakdown &&arg)
    {
        DataBreakdownBase::operator=(std::move(arg));
        prototype = std::move(arg.prototype);
        tracks = std::move(arg.tracks);
        return *this;
    }

    void DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>>::SetNameGroup(const StringGroup &group)
    {
        prototype.SetGroup(group);

        //name.SetEditable(true);
        Build::Package<String> package;
        package.value = *group.begin();
        prototype.Edit(package);
        //name.SetEditable(false);

        SyncTrackGroups();
    }
}