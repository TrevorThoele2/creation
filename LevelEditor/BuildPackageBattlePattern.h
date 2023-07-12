#pragma once

#include "BuildPackage.h"
#include "BuildPackageGeneral.h"
#include "BuildPackageCombatChain.h"

#include <Atmos/BattlePatternHolder.h>

namespace Creation
{
    namespace Build
    {
        template<>
        class Package<::Atmos::BattlePatternHolder::Piece> : public PackageBase
        {
        public:
            typedef ::Atmos::BattlePatternHolder::Piece BuildT;
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::Sprite> selectionSprite;
            Package<BuildT::Power> power;
            Package<::Atmos::CombatChain> chain;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };

        template<>
        class Package<::Atmos::BattlePatternHolder> : public PackageBase
        {
        public:
            typedef ::Atmos::BattlePatternHolder BuildT;
        public:
            class PatternPiece : public PackageBase
            {
            private:
                INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
                INSCRIPTION_ACCESS;
            public:
                Package<::Atmos::RelativeGridPosition> position;
                Package<std::uint32_t> registryPosition;

                BUILD_PACKAGE_DEFAULT_SPECIFIC(PatternPiece);
                PatternPiece(PatternPiece &&arg);
                PatternPiece& operator=(PatternPiece &&arg);
                bool operator==(const PatternPiece &arg) const;
                bool operator!=(const PatternPiece &arg) const;
            };
        private:
            INSCRIPTION_SERIALIZE_FUNCTION_DECLARE;
            INSCRIPTION_ACCESS;
        public:
            Package<::Atmos::RandomAccessSequence<Package<BuildT::Piece>>> registry;
            Package<::Atmos::RandomAccessSequence<PatternPiece>> pattern;

            BUILD_PACKAGE_DEFAULT;
            Package(Package &&arg);
            Package& operator=(Package &&arg);
            bool operator==(const Package &arg) const;
            bool operator!=(const Package &arg) const;

            BuildT Build() const;
        };
    }
}