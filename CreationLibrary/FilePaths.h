#pragma once

#include "FilePath.h"

namespace Creation
{
    [[nodiscard]] File::Path CompiledShaderPath(const File::Path& inputFilePath);
    [[nodiscard]] File::Path CompiledScriptPath(const File::Path& inputFilePath);
}