#pragma once

#include <string>

#include "WorldGlobals.h"
#include "BuildPackageField.h"

#include "Event.h"

#include <Atmos\Field.h>
#include <Atmos\FieldID.h>
#include <Atmos\WorldStart.h>
#include <Atmos\FilePath.h>

namespace Creation
{
    class CurrentWorld
    {
    public:
        typedef Atmos::Field Field;
        typedef Atmos::FieldID FieldID;
        typedef Atmos::FilePath FilePath;

        typedef Build::Package<::Atmos::WorldStart> WorldStartPackage;
        typedef Build::Package<Field> FieldPackage;
    private:
        FilePath buildFilePath;
        FilePath loadFilePath;
        std::unique_ptr<Field> currentField;
        WorldStartPackage worldStart;

        CurrentWorld() = default;
        ~CurrentWorld();
        CurrentWorld(const CurrentWorld &arg) = delete;
        CurrentWorld& operator=(const CurrentWorld &arg) = delete;

        static void SaveImpl(const ::Atmos::FilePath &filePath, bool moveFile = true);
        static void SelectField(FieldID field);
        static ::Atmos::FilePath MakeWorldFilePath();
        // Used for the temporary save; when the world needs to have a field added or removed
        static ::Atmos::FilePath MakeTemporarySaveFilePath();
    public:
        static NullEvent onFieldChanged;
        static FieldPackage fieldPackage;

        static WorldGlobals globals;

        static CurrentWorld& Instance();
        static void Add(FieldID id);
        static void Remove(FieldID id);
        static bool Select(FieldID id);
        static Field* GetCurrentField();
        static bool IsFieldValid();
        static bool IsFieldHere(FieldID id);
        static bool FieldsEmpty();
        static void Clear();

        static void SetWorldStart(FieldID id);
        static FieldID GetWorldStartField();

        static void Draw(Atmos::Position3D::ValueT z);
        static void StartWorld();

        static void SetFilePath(const FilePath &set);
        static const FilePath& GetFilePath();
        static bool IsFilePathValid();

        // Only possible when the file path is set
        // Only saves the build
        static void Save();
        // Will set the file path
        // Only saves the build
        static void Save(const FilePath &path);
        // Will set the file path
        // Only loads the build
        static void Load(const FilePath &path);

        static void Build();
    };

    ::Atmos::Field* GetCurrentField();
    ::Atmos::RenderFragmentHandler* GetCurrentRenderFragments();
}