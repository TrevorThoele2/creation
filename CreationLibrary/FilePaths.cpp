#include "FilePaths.h"

#include "Settings.h"
#include <Atmos/VulkanPaths.h>
#include <Atmos/JavaScriptPaths.h>

namespace Creation
{
    File::Path CompiledShaderPath(const File::Path& inputFilePath)
    {
        return settings.compiledShaderAssetPath / Atmos::Render::Vulkan::ToCompiledPath(inputFilePath).filename();
    }

    File::Path CompiledScriptPath(const File::Path& inputFilePath)
    {
        return settings.compiledScriptAssetPath / Atmos::Scripting::JavaScript::ToCompiledPath(inputFilePath).filename();
    }
}