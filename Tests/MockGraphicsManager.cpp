#include "MockGraphicsManager.h"

#include "MockSurfaceResource.h"

class ImageAssetDataImplementation final : public Asset::Resource::Image
{
public:
    ImageAssetDataImplementation() = default;

    [[nodiscard]] Spatial::Size2D Size() const override
    {
        return {};
    }
};

class ShaderAssetDataImplementation final : public Asset::Resource::Shader
{
public:
    ShaderAssetDataImplementation() = default;
};

MockGraphicsManager::MockGraphicsManager(Logging::Logger& logger) : GraphicsManager(logger, "Mock")
{}

void MockGraphicsManager::SetFullscreen(bool set)
{}

void MockGraphicsManager::ChangeVerticalSync(bool set)
{}

std::unique_ptr<Asset::Resource::Image> MockGraphicsManager::CreateImageResourceImpl(
    const Buffer& buffer,
    const Name& name,
    const Spatial::Size2D& size)
{
    return std::make_unique<ImageAssetDataImplementation>();
}

std::unique_ptr<Asset::Resource::Shader> MockGraphicsManager::CreateShaderResourceImpl(
    const Buffer& buffer, const Name& name)
{
    return std::make_unique<ShaderAssetDataImplementation>();
}

std::unique_ptr<Resource::Surface> MockGraphicsManager::CreateMainSurfaceResourceImpl(
    void* window)
{
    return std::make_unique<MockSurfaceDataImplementation>();
}

std::unique_ptr<Resource::Surface> MockGraphicsManager::CreateSurfaceResourceImpl(
    void* window)
{
    return std::make_unique<MockSurfaceDataImplementation>();
}

Buffer MockGraphicsManager::CompileShaderImpl(const File::Path& filePath)
{
    return {};
}

bool MockGraphicsManager::ShouldReconstructInternals() const
{
    return false;
}

void MockGraphicsManager::ReconstructInternals(GraphicsReconstructionObjects objects)
{}

void MockGraphicsManager::DrawFrameImpl(const AllRenders& allRenders, const Spatial::Point2D& mapPosition)
{
    imageRenders.insert(imageRenders.end(), allRenders.images.begin(), allRenders.images.end());
    lineRenders.insert(lineRenders.end(), allRenders.lines.begin(), allRenders.lines.end());
    regionRenders.insert(regionRenders.end(), allRenders.regions.begin(), allRenders.regions.end());
    textRenders.insert(textRenders.end(), allRenders.texts.begin(), allRenders.texts.end());
}

void MockGraphicsManager::ResourceDestroyingImpl(Asset::Resource::Image& resource)
{

}

void MockGraphicsManager::ResourceDestroyingImpl(Asset::Resource::Shader& resource)
{

}

void MockGraphicsManager::ResourceDestroyingImpl(Resource::Surface& resource)
{

}

void MockGraphicsManager::PruneResourcesImpl()
{

}

Spatial::Size2D MockGraphicsManager::TextBaseSizeImpl(
    const String& string, const Asset::Resource::Font& resource, bool bold, bool italics, float wrapWidth) const
{
    return { 1, 1 };
}