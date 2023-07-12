#pragma once

#include "DataBreakdownBase.h"
#include "DataBreakdownGeneral.h"

#include "BuildPackageModulators.h"

#include "ModulatorData.h"
#include <Function/Variant.h>

namespace Creation
{
    template<>
    class DataBreakdown<Build::Package<::Atmos::Modulator::Value>> : public DataBreakdownBase<Build::Package<::Atmos::Modulator::Value>>
    {
    public:
        typedef PackageT::BuildT BuildT;
    private:
        void OnTypeChanged(const DataBreakdownEditArgs &args);

        void AddAllChildren();

        void SetupImpl() override final;

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void SetEditableImpl(bool set) override final;
    public:
        typedef DataBreakdown<Build::Package<::Atmos::Modulator::ValueTraits<BuildT::Type::INT>::T>> IntBreakdownT;
        typedef DataBreakdown<Build::Package<::Atmos::Modulator::ValueTraits<BuildT::Type::FLOAT>::T>> FloatBreakdownT;
        typedef ::function::Variant<IntBreakdownT, FloatBreakdownT> ChildVariantT;

        DataBreakdownEnum<BuildT::Type> type;
        ChildVariantT variant;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage>
    {
    private:
        void OnEndStateTypeChanged(const DataBreakdownEditArgs &args);
        void OnInterpolationTypeChanged(const DataBreakdownEditArgs &args);

        void AddAllChildren();
        void SubscribeEvents();

        void SetupImpl() override final;

        void CreateEditorPropertiesImpl(const ChildReference &afterThis) override final;
        void UpdateEditorPropertiesImpl(DataViewSelection::Group &selected) override final;
        void DestroyEditorPropertiesImpl(bool destroyTreeItem) override final;
        void CreateTreePieceImpl(wxTreeItemId parentItemID, const ChildReference &afterThis) override final;
        void ChangeSelectImpl(SelectedState state) override final;
        void SetEditableImpl(bool set) override final;
    public:
        typedef DataBreakdown<Build::Package<::Atmos::Modulator::TrackNodeInterpolation::Acceleration>> InterpolationAccelerationT;
        typedef DataBreakdown<Build::Package<::Atmos::Modulator::TrackNodeInterpolation::Rate>> InterpolationRateT;
    public:
        class EndStateNormal : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateNormal>
        {
        private:
            void AddAllChildren();

            void SetupImpl() override final;
        public:
            DataBreakdown<Build::Package<::Atmos::Modulator::Value>> value;

            EndStateNormal(const String &name, DataBreakdownCommon *parent);
            EndStateNormal(EndStateNormal &&arg, DataBreakdownCommon *parent = nullptr);
            EndStateNormal& operator=(EndStateNormal &&arg);
        };

        class EndStateRandom : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::EndStateRandom>
        {
        private:
            void AddAllChildren();

            void SetupImpl() override final;
        public:
            DataBreakdown<Build::Package<::Atmos::Range<::Atmos::Modulator::Value>>> value;

            EndStateRandom(const String &name, DataBreakdownCommon *parent);
            EndStateRandom(EndStateRandom &&arg, DataBreakdownCommon *parent = nullptr);
            EndStateRandom& operator=(EndStateRandom &&arg);
        };

        class InterpolationLinear : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationLinear>
        {
        private:
            void AddAllChildren() {}

            void SetupImpl() override final {}
        public:
            InterpolationLinear(const String &name, DataBreakdownCommon *parent);
            InterpolationLinear(InterpolationLinear &&arg, DataBreakdownCommon *parent = nullptr);
            InterpolationLinear& operator=(InterpolationLinear &&arg);
        };

        class InterpolationOscillation : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage::InterpolationOscillation>
        {
        private:
            void AddAllChildren();

            void SetupImpl() override final;
        public:
            InterpolationAccelerationT acceleration;
            InterpolationRateT rate;

            InterpolationOscillation(const String &name, DataBreakdownCommon *parent);
            InterpolationOscillation(InterpolationOscillation &&arg, DataBreakdownCommon *parent = nullptr);
            InterpolationOscillation& operator=(InterpolationOscillation &&arg);
        };
    public:
        DataBreakdownEnum<::Atmos::Modulator::TrackNodeEndState::Type> endStateType;
        typedef ::function::Variant<EndStateNormal, EndStateRandom> EndStateVariantT;
        EndStateVariantT endStateVariant;
        
        DataBreakdownEnum<::Atmos::Modulator::TrackNodeInterpolation::Type> interpolationType;
        typedef ::function::Variant<InterpolationLinear, InterpolationOscillation> InterpolationVariantT;
        InterpolationVariantT interpolationVariant;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);

        void ForceEditValueType(::Atmos::Modulator::Value::Type force);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage> : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage>
    {
    private:
        void OnPrototypeChanged(const DataBreakdownEditArgs &args);

        void AddAllChildren();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> prototype;
        DataBreakdownList<Build::Package<::Atmos::Modulator::GeneratorRoute>::NodeEntryPackage> nodes;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);
    };

    template<>
    class DataBreakdown<Build::Package<::Atmos::Modulator::GeneratorRoute>> : public DataBreakdownBase<Build::Package<::Atmos::Modulator::GeneratorRoute>>
    {
    public:
        typedef PackageT::BuildT BuildT;
    private:
        void OnPrototypeChanged(const DataBreakdownEditArgs &args);
        void OnTrackAdded(const DataBreakdownAddArgs &args);

        void SyncTrackGroups();

        void AddAllChildren();
        void SubscribeEvents();

        void SetupImpl() override final;
    public:
        DataBreakdown<Build::Package<::Atmos::Name>> prototype;
        DataBreakdownList<Build::Package<::Atmos::Modulator::GeneratorRoute>::TrackNodePackage> tracks;

        DataBreakdown(const String &name, DataBreakdownCommon *parent);
        DataBreakdown(DataBreakdown &&arg, DataBreakdownCommon *parent = nullptr);
        DataBreakdown& operator=(DataBreakdown &&arg);

        void SetNameGroup(const StringGroup &group);
    };
}