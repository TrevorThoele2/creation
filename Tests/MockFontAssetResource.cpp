#include "MockFontAssetResource.h"

Atmos::Render::LoadedGlyph MockFontAssetResource::Load(char32_t codepoint, bool bold, bool italics) const
{
	return {};
}

float MockFontAssetResource::MaximumGlyphHeight() const
{
	return 0.0f;
}