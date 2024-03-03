#pragma once

#include <Atmos/FontAssetResource.h>

class MockFontAssetResource final : public Atmos::Asset::Resource::Font
{
public:
    [[nodiscard]] Atmos::Render::LoadedGlyph Load(char32_t codepoint, bool bold, bool italics) const override;
    [[nodiscard]] float MaximumGlyphHeight() const override;
};