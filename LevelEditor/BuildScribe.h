#pragma once

#include "WorldGlobals.h"
#include "BuildPackageField.h"
#include <Atmos/SkipFileHelper.h>
#include <Atmos/FilePath.h>
#include <Inscription/BinaryScribe.h>

namespace Creation
{
    namespace Build
    {
        extern const char *buildExtension;

        class ScribeOut
        {
        public:
            enum class OpenMode
            {
                NONE,
                FORCE_EXTENSION
            };

            typedef Build::Package<::Atmos::Field> FieldPackage;
        private:
            typedef inscription::BinaryScribe ScribeT;

            class FieldSaver : public ::Atmos::SkipSaver<ScribeT>
            {
            public:
                typedef ::Atmos::FieldID IDType;
                typedef inscription::Buffer::SizeT SizeT;
            private:
                SizeT positionStart;

                void OnBeforeObjectSave() override;
                void OnAfterObjectSave() override;
                void SavePlaceholderExtra() override;
                void SaveExtra() override;
            public:
                IDType fieldID;
                inscription::Buffer::SizeT size;

                FieldSaver(ScribeT &cribe);
            };
        private:
            ScribeT basicScribe;

            ::Atmos::FilePath filePath;
            typedef std::vector<FieldSaver> FieldSaversVector;
            FieldSaversVector fieldSavers;
            FieldSaversVector::iterator curSaver;

            bool hasOutputHeader;

            void OutputHeader();
        public:
            WorldGlobals globals;

            ScribeOut(const ::Atmos::FilePath &filePath, inscription::ContainerSize::ValueT fieldCount, OpenMode openMode = OpenMode::FORCE_EXTENSION);
            void Save(FieldPackage &save);
            const ::Atmos::FilePath& GetFilePath() const;
        };

        class ScribeIn
        {
        public:
            enum class OpenMode
            {
                NONE,
                FORCE_EXTENSION
            };

            typedef Build::Package<::Atmos::Field> FieldPackage;
        private:
            typedef inscription::BinaryScribe ScribeT;

            class FieldHandle : public ::Atmos::SkipHandle<ScribeT>
            {
            public:
                typedef ::Atmos::FieldID IDType;
                typedef inscription::Buffer::SizeT SizeT;
            private:
                void LoadExtra() override;
            public:
                ::Atmos::FieldID fieldID;
                SizeT size;

                FieldHandle(ScribeT &scribe);
            };

            typedef std::map<::Atmos::FieldID, FieldHandle> FieldHandles;
        private:
            ScribeT basicScribe;

            ::Atmos::FilePath filePath;
            FieldHandles fieldHandles;
        public:
            WorldGlobals globals;

            ScribeIn(const ::Atmos::FilePath &filePath, OpenMode openMode = OpenMode::FORCE_EXTENSION);

            void Load();

            // Returns if actually retrieved anything
            bool Get(::Atmos::FieldID id, FieldPackage &package);
            void GetIDs(std::vector<::Atmos::FieldID> &ids) const;

            const ::Atmos::FilePath& GetFilePath() const;
        };
    }
}