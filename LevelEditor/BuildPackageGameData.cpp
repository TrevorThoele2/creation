
#include "BuildPackageGameData.h"

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>)
        {
            scribe(health);
            scribe(mana);
            scribe(acumen);
        }

        Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>::Package(Package &&arg) : health(std::move(arg.health)), mana(std::move(arg.mana)), acumen(std::move(arg.acumen))
        {}

        Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>& Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>::operator=(Package &&arg)
        {
            health = std::move(arg.health);
            mana = std::move(arg.mana);
            acumen = std::move(arg.acumen);
            return *this;
        }

        bool Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>::operator==(const Package &arg) const
        {
            return health == arg.health && mana == arg.mana && acumen == arg.acumen;
        }

        bool Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        void Package<::Atmos::GlobalContext<::Atmos::ResourceAttributeTable>>::Build() const
        {
            BuildT::health = health.Build();
            BuildT::mana = mana.Build();
            BuildT::acumen = acumen.Build();
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage)
        {
            scribe(name);
            scribe(niceName);
            scribe(opposing);
        }

        Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage::EntryPackage(EntryPackage &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)),
            opposing(std::move(arg.opposing))
        {}

        Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage& Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage::operator=(EntryPackage &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            opposing = std::move(arg.opposing);
            return *this;
        }

        bool Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage::operator==(const EntryPackage &arg) const
        {
            return name == arg.name && niceName == arg.niceName && opposing == arg.opposing;
        }

        bool Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage::operator!=(const EntryPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage::BuildT Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::EntryPackage::Build() const
        {
            return BuildT(name.Build(), niceName.Build(), opposing.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>)
        {
            scribe(entries);
        }

        Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::Package(Package &&arg) : entries(std::move(arg.entries))
        {}

        Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>& Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::operator=(Package &&arg)
        {
            entries = std::move(arg.entries);
            return *this;
        }

        bool Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::operator==(const Package &arg) const
        {
            return entries == arg.entries;
        }

        bool Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        void Package<::Atmos::DataStandard<::Atmos::StatAttributeTable>>::Build() const
        {
            for (auto &loop : entries.value)
                BuildT::Add(std::move(loop.Build()));
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage)
        {
            scribe(name);
            scribe(niceName);
            scribe(opposing);
            scribe(statName);
        }

        Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage::EntryPackage(EntryPackage &&arg) : name(std::move(arg.name)), niceName(std::move(arg.niceName)),
            opposing(std::move(arg.opposing)), statName(std::move(arg.statName))
        {}

        Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage& Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage::operator=(EntryPackage &&arg)
        {
            name = std::move(arg.name);
            niceName = std::move(arg.niceName);
            opposing = std::move(arg.opposing);
            statName = std::move(arg.statName);
            return *this;
        }

        bool Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage::operator==(const EntryPackage &arg) const
        {
            return name == arg.name && niceName == arg.niceName && opposing == arg.opposing && statName == arg.statName;
        }

        bool Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage::operator!=(const EntryPackage &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage::BuildT Package<::Atmos::GlobalContext<::Atmos::Element>>::EntryPackage::Build() const
        {
            return BuildT(name.Build(), niceName.Build(), opposing.Build(), statName.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::GlobalContext<::Atmos::Element>>)
        {
            scribe(neutral);
            scribe(entries);
        }

        Package<::Atmos::GlobalContext<::Atmos::Element>>::Package(Package &&arg) : neutral(std::move(arg.neutral)), entries(std::move(arg.entries))
        {}

        Package<::Atmos::GlobalContext<::Atmos::Element>>& Package<::Atmos::GlobalContext<::Atmos::Element>>::operator=(Package &&arg)
        {
            neutral = std::move(arg.neutral);
            entries = std::move(arg.entries);
            return *this;
        }

        bool Package<::Atmos::GlobalContext<::Atmos::Element>>::operator==(const Package &arg) const
        {
            return neutral == arg.neutral && entries == arg.entries;
        }

        bool Package<::Atmos::GlobalContext<::Atmos::Element>>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        void Package<::Atmos::GlobalContext<::Atmos::Element>>::Build() const
        {
            BuildT::neutral = neutral.Build();
            for (auto &loop : entries.value)
                BuildT::Add(loop.Build());
        }
    }
}