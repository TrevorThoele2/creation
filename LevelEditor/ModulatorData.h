#pragma once

#include "DataBase.h"
#include <Atmos/Modulator.h>

#include "StringGroup.h"

namespace Creation
{
    template<>
    class Data<::Atmos::Modulator::TrackNodeEndState::Type> : public DataBase<::Atmos::Modulator::TrackNodeEndState::Type>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Modulator::TrackNodeEndState::Type> : public DataManagerBase<::Atmos::Modulator::TrackNodeEndState::Type, DataManager<::Atmos::Modulator::TrackNodeEndState::Type>>
    {
    private:
        friend BaseT;

        DataManager();
    };

    template<>
    class Data<::Atmos::Modulator::TrackNodeInterpolation::Type> : public DataBase<::Atmos::Modulator::TrackNodeInterpolation::Type>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Modulator::TrackNodeInterpolation::Type> : public DataManagerBase<::Atmos::Modulator::TrackNodeInterpolation::Type, DataManager<::Atmos::Modulator::TrackNodeInterpolation::Type>>
    {
    private:
        friend BaseT;

        DataManager();
    };

    template<>
    class Data<::Atmos::Modulator::Value::Type> : public DataBase<::Atmos::Modulator::Value::Type>
    {
    public:
        Data(ValueT value, StringT &&string);
    };

    template<>
    class DataManager<::Atmos::Modulator::Value::Type> : public DataManagerBase<::Atmos::Modulator::Value::Type, DataManager<::Atmos::Modulator::Value::Type>>
    {
    private:
        friend BaseT;

        DataManager();
    };

    class ModulatorGroups
    {
    public:
        typedef ::Atmos::Modulator::Value::Type ValueType;
    private:
        struct TrackEntry
        {
            ValueType type;
            TrackEntry(ValueType type);
        };

        struct Entry
        {
            std::unordered_map<String, TrackEntry> tracks;
            Entry() = default;
        };
    private:
        std::unordered_map<String, Entry> entries;

        ModulatorGroups();
    public:
        static ModulatorGroups& Instance();
        static StringGroup GetTrackGroup(const String &name);
        static ValueType GetTypeForTrack(const String &modulatorName, const String &trackName);
    };
}