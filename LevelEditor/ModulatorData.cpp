
#include "ModulatorData.h"

#include <Atmos/ModulatorDescribers.h>

namespace Creation
{
    Data<::Atmos::Modulator::TrackNodeEndState::Type>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Modulator::TrackNodeEndState::Type>::DataManager()
    {
        Add(DataT(::Atmos::Modulator::TrackNodeEndState::Type::NONE, "None"));
        Add(DataT(::Atmos::Modulator::TrackNodeEndState::Type::NORMAL, "Normal"));
        Add(DataT(::Atmos::Modulator::TrackNodeEndState::Type::RANDOM, "Random"));
    }

    Data<::Atmos::Modulator::TrackNodeInterpolation::Type>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Modulator::TrackNodeInterpolation::Type>::DataManager()
    {
        Add(DataT(::Atmos::Modulator::TrackNodeInterpolation::Type::NONE, "None"));
        Add(DataT(::Atmos::Modulator::TrackNodeInterpolation::Type::LINEAR, "Linear"));
        Add(DataT(::Atmos::Modulator::TrackNodeInterpolation::Type::OSCILLATION, "Oscillation"));
    }

    Data<::Atmos::Modulator::Value::Type>::Data(ValueT value, StringT &&string) : DataBase(value, std::move(string))
    {}

    DataManager<::Atmos::Modulator::Value::Type>::DataManager()
    {
        Add(DataT(::Atmos::Modulator::Value::Type::NONE, "None"));
        Add(DataT(::Atmos::Modulator::Value::Type::INT, "Int"));
        Add(DataT(::Atmos::Modulator::Value::Type::FLOAT, "Float"));
    }

    ModulatorGroups::TrackEntry::TrackEntry(ValueType type) : type(type)
    {}

    ModulatorGroups::ModulatorGroups()
    {
        Entry *focusedEntry = &entries.emplace(::Atmos::Modulator::Description::Sprite.name, Entry()).first->second;
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DX.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DY.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DZ.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::RotationX.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::RotationY.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::RotationZ.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::ScalingX.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::ScalingY.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::ScalingZ.name, TrackEntry(ValueType::FLOAT));

        focusedEntry = &entries.emplace(::Atmos::Modulator::Description::Sound.name, Entry()).first->second;
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DX.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DY.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DZ.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Volume.name, TrackEntry(ValueType::FLOAT));

        focusedEntry = &entries.emplace(::Atmos::Modulator::Description::AVEffect.name, Entry()).first->second;
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DX.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DY.name, TrackEntry(ValueType::FLOAT));
        focusedEntry->tracks.emplace(::Atmos::Modulator::Description::Position3DZ.name, TrackEntry(ValueType::FLOAT));
    }

    ModulatorGroups& ModulatorGroups::Instance()
    {
        static ModulatorGroups instance;
        return instance;
    }

    StringGroup ModulatorGroups::GetTrackGroup(const String &name)
    {
        StringGroup group;
        auto found = Instance().entries.find(name);
        // If found, populate the group
        if (found != Instance().entries.end())
            for (auto &loop : found->second.tracks)
                group.push_back(loop.first);

        // If didn't find anything, this will be empty
        return group;
    }

    ModulatorGroups::ValueType ModulatorGroups::GetTypeForTrack(const String &modulatorName, const String &trackName)
    {
        auto found = Instance().entries.find(modulatorName);
        if (found == Instance().entries.end())
            return ValueType::NONE;

        auto trackFound = found->second.tracks.find(trackName);
        if (trackFound == found->second.tracks.end())
            return ValueType::NONE;

        return trackFound->second.type;
    }
}