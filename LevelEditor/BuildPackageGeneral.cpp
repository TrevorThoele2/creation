
#include "BuildPackageGeneral.h"

#include <Atmos/AudioRegistry.h>
#include <Atmos/ShaderRegistry.h>

namespace Creation
{
    namespace Build
    {
        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<bool>)
        {
            scribe(value);
        }

        Package<bool>::Package() : value(false)
        {}

        Package<bool>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<bool>& Package<bool>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<bool>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<bool>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<bool>::BuildT Package<bool>::Build() const
        {
            return value;
        }

        Package<bool>* Package<bool>::Clone() const
        {
            return new Package(*this);
        }

        String Package<bool>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::uint8_t>)
        {
            scribe(value);
        }

        Package<std::uint8_t>::Package() : value(0)
        {}

        Package<std::uint8_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::uint8_t>& Package<std::uint8_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::uint8_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::uint8_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::uint8_t>::BuildT Package<std::uint8_t>::Build() const
        {
            return value;
        }

        Package<std::uint8_t>* Package<std::uint8_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::uint8_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::uint16_t>)
        {
            scribe(value);
        }

        Package<std::uint16_t>::Package() : value(0)
        {}

        Package<std::uint16_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::uint16_t>& Package<std::uint16_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::uint16_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::uint16_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::uint16_t>::BuildT Package<std::uint16_t>::Build() const
        {
            return value;
        }

        Package<std::uint16_t>* Package<std::uint16_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::uint16_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::uint32_t>)
        {
            scribe(value);
        }

        Package<std::uint32_t>::Package() : value(0)
        {}

        Package<std::uint32_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::uint32_t>& Package<std::uint32_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::uint32_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::uint32_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::uint32_t>::BuildT Package<std::uint32_t>::Build() const
        {
            return value;
        }

        Package<std::uint32_t>* Package<std::uint32_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::uint32_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::uint64_t>)
        {
            scribe(value);
        }

        Package<std::uint64_t>::Package() : value(0)
        {}

        Package<std::uint64_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::uint64_t>& Package<std::uint64_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::uint64_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::uint64_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::uint64_t>::BuildT Package<std::uint64_t>::Build() const
        {
            return value;
        }

        Package<std::uint64_t>* Package<std::uint64_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::uint64_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::int8_t>)
        {
            scribe(value);
        }

        Package<std::int8_t>::Package() : value(0)
        {}

        Package<std::int8_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::int8_t>& Package<std::int8_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::int8_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::int8_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::int8_t>::BuildT Package<std::int8_t>::Build() const
        {
            return value;
        }

        Package<std::int8_t>* Package<std::int8_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::int8_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::int16_t>)
        {
            scribe(value);
        }

        Package<std::int16_t>::Package() : value(0)
        {}

        Package<std::int16_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::int16_t>& Package<std::int16_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::int16_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::int16_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::int16_t>::BuildT Package<std::int16_t>::Build() const
        {
            return value;
        }

        Package<std::int16_t>* Package<std::int16_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::int16_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::int32_t>)
        {
            scribe(value);
        }

        Package<std::int32_t>::Package() : value(0)
        {}

        Package<std::int32_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::int32_t>& Package<std::int32_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::int32_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::int32_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::int32_t>::BuildT Package<std::int32_t>::Build() const
        {
            return value;
        }

        Package<std::int32_t>* Package<std::int32_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::int32_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<std::int64_t>)
        {
            scribe(value);
        }

        Package<std::int64_t>::Package() : value(0)
        {}

        Package<std::int64_t>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<std::int64_t>& Package<std::int64_t>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<std::int64_t>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<std::int64_t>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<std::int64_t>::BuildT Package<std::int64_t>::Build() const
        {
            return value;
        }

        Package<std::int64_t>* Package<std::int64_t>::Clone() const
        {
            return new Package(*this);
        }

        String Package<std::int64_t>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<float>)
        {
            scribe(value);
        }

        Package<float>::Package() : value(0.0f)
        {}

        Package<float>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<float>& Package<float>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<float>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<float>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<float>::BuildT Package<float>::Build() const
        {
            return value;
        }

        Package<float>* Package<float>::Clone() const
        {
            return new Package(*this);
        }

        String Package<float>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<double>)
        {
            scribe(value);
        }

        Package<double>::Package() : value(0.0f)
        {}

        Package<double>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<double> & Package<double>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<double>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<double>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<double>::BuildT Package<double>::Build() const
        {
            return value;
        }

        Package<double>* Package<double>::Clone() const
        {
            return new Package(*this);
        }

        String Package<double>::ToString() const
        {
            return ::Atmos::ToString(value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::String>)
        {
            scribe(value);
        }

        Package<::Atmos::String>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::String> & Package<::Atmos::String>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::String>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::String>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::String>::BuildT Package<::Atmos::String>::Build() const
        {
            return value;
        }

        String Package<::Atmos::String>::ToString() const
        {
            return value;
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::FilePath>)
        {
            scribe(value);
        }

        Package<::Atmos::FilePath>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::FilePath> & Package<::Atmos::FilePath>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::FilePath>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::FilePath>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::FilePath>::BuildT Package<::Atmos::FilePath>::Build() const
        {
            return value;
        }

        String Package<::Atmos::FilePath>::ToString() const
        {
            return value.GetValue();
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::FileName>)
        {
            scribe(value);
        }

        Package<::Atmos::FileName>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::FileName> & Package<::Atmos::FileName>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::FileName>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::FileName>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::FileName>::BuildT Package<::Atmos::FileName>::Build() const
        {
            return value;
        }

        String Package<::Atmos::FileName>::ToString() const
        {
            return value.GetValue();
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Percentage>)
        {
            scribe(value);
        }

        Package<::Atmos::Percentage>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Percentage> & Package<::Atmos::Percentage>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Percentage>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Percentage>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Percentage>::BuildT Package<::Atmos::Percentage>::Build() const
        {
            return BuildT(value.Build());
        }

        String Package<::Atmos::Percentage>::ToString() const
        {
            return ::Atmos::ToString(value.value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Angle>)
        {
            scribe(value);
        }

        Package<::Atmos::Angle>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Angle>& Package<::Atmos::Angle>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Angle>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Angle>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Angle>::BuildT Package<::Atmos::Angle>::Build() const
        {
            return BuildT(BuildT::Type::DEGREES, value.Build());
        }

        String Package<::Atmos::Angle>::ToString() const
        {
            return ::Atmos::ToString(value.value);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Position3D>)
        {
            scribe(x);
            scribe(y);
            scribe(z);
        }

        Package<::Atmos::Position3D>::Package(Package &&arg) : x(std::move(arg.x)), y(std::move(arg.y)), z(std::move(arg.z))
        {}

        Package<::Atmos::Position3D> & Package<::Atmos::Position3D>::operator=(Package &&arg)
        {
            x = std::move(arg.x);
            y = std::move(arg.y);
            z = std::move(arg.z);
            return *this;
        }

        bool Package<::Atmos::Position3D>::operator==(const Package &arg) const
        {
            return x == arg.x && y == arg.y && z == arg.z;
        }

        bool Package<::Atmos::Position3D>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Position3D>::BuildT Package<::Atmos::Position3D>::Build() const
        {
            return BuildT(x.Build(), y.Build(), z.Build());
        }

        String Package<::Atmos::Position3D>::ToString() const
        {
            return "(" + ::Atmos::ToString(x.value) + ", " + ::Atmos::ToString(y.value) + ", " + ::Atmos::ToString(z.value) + ")";
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::GridPosition>)
        {
            scribe(x);
            scribe(y);
            scribe(z);
        }

        Package<::Atmos::GridPosition>::Package(Package &&arg) : x(std::move(arg.x)), y(std::move(arg.y)), z(std::move(arg.z))
        {}

        Package<::Atmos::GridPosition> & Package<::Atmos::GridPosition>::operator=(Package &&arg)
        {
            x = std::move(arg.x);
            y = std::move(arg.y);
            z = std::move(arg.z);
            return *this;
        }

        bool Package<::Atmos::GridPosition>::operator==(const Package &arg) const
        {
            return x == arg.x && y == arg.y && z == arg.z;
        }

        bool Package<::Atmos::GridPosition>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::GridPosition>::BuildT Package<::Atmos::GridPosition>::Build() const
        {
            return BuildT(x.Build(), y.Build(), z.Build());
        }

        String Package<::Atmos::GridPosition>::ToString() const
        {
            return "(" + ::Atmos::ToString(x.value) + ", " + ::Atmos::ToString(y.value) + ", " + ::Atmos::ToString(z.value) + ")";
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::RelativeGridPosition>)
        {
            scribe(x);
            scribe(y);
            scribe(z);
        }

        Package<::Atmos::RelativeGridPosition>::Package(Package &&arg) : x(std::move(arg.x)), y(std::move(arg.y)), z(std::move(arg.z))
        {}

        Package<::Atmos::RelativeGridPosition> & Package<::Atmos::RelativeGridPosition>::operator=(Package &&arg)
        {
            x = std::move(arg.x);
            y = std::move(arg.y);
            z = std::move(arg.z);
            return *this;
        }

        bool Package<::Atmos::RelativeGridPosition>::operator==(const Package &arg) const
        {
            return x == arg.x && y == arg.y && z == arg.z;
        }

        bool Package<::Atmos::RelativeGridPosition>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::RelativeGridPosition>::BuildT Package<::Atmos::RelativeGridPosition>::Build() const
        {
            return BuildT(x.Build(), y.Build(), z.Build());
        }

        String Package<::Atmos::RelativeGridPosition>::ToString() const
        {
            return "(" + ::Atmos::ToString(x.value) + ", " + ::Atmos::ToString(y.value) + ", " + ::Atmos::ToString(z.value) + ")";
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Direction>)
        {
            scribe(value);
        }

        Package<::Atmos::Direction>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Direction> & Package<::Atmos::Direction>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Direction>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Direction>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Direction>::BuildT Package<::Atmos::Direction>::Build() const
        {
            return BuildT(static_cast<BuildT::ValueT>(value.Build()));
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Color>)
        {
            scribe(a);
            scribe(r);
            scribe(g);
            scribe(b);
        }

        Package<::Atmos::Color>::Package()
        {
            a.value = 255;
            r.value = 255;
            g.value = 255;
            b.value = 255;
        }

        Package<::Atmos::Color>::Package(Package &&arg) : a(std::move(arg.a)), r(std::move(arg.r)), g(std::move(arg.g)), b(std::move(arg.b))
        {}

        Package<::Atmos::Color> & Package<::Atmos::Color>::operator=(Package &&arg)
        {
            a = std::move(arg.a);
            r = std::move(arg.r);
            g = std::move(arg.g);
            b = std::move(arg.b);
            return *this;
        }

        bool Package<::Atmos::Color>::operator==(const Package &arg) const
        {
            return a == arg.a && r == arg.r && g == arg.g && b == arg.b;
        }

        bool Package<::Atmos::Color>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Color>::BuildT Package<::Atmos::Color>::Build() const
        {
            return BuildT(a.Build(), r.Build(), g.Build(), b.Build());
        }

        Package<::Atmos::Color>* Package<::Atmos::Color>::Clone() const
        {
            return new Package(*this);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Sprite>)
        {
            scribe(material);
            scribe(shaderPatch);
            scribe(index);
            scribe(color);
            scribe(xScaler);
            scribe(yScaler);
            scribe(zScaler);
            scribe(xRotation);
            scribe(yRotation);
            scribe(zRotation);
        }

        Package<::Atmos::Sprite>::Package()
        {
            index.value = 1;
            xScaler.value = 1;
            yScaler.value = 1;
            zScaler.value = 1;
        }

        Package<::Atmos::Sprite>::Package(Package &&arg) : material(std::move(arg.material)), shaderPatch(std::move(arg.shaderPatch)), index(std::move(arg.index)),
            color(std::move(arg.color)), xScaler(std::move(arg.xScaler)), yScaler(std::move(arg.yScaler)), zScaler(std::move(arg.zScaler)), xRotation(std::move(arg.xRotation)),
            yRotation(std::move(arg.yRotation)), zRotation(std::move(arg.zRotation))
        {}

        Package<::Atmos::Sprite> & Package<::Atmos::Sprite>::operator=(Package &&arg)
        {
            material = std::move(arg.material);
            shaderPatch = std::move(arg.shaderPatch);
            index = std::move(arg.index);
            color = std::move(arg.color);
            xScaler = std::move(arg.xScaler);
            yScaler = std::move(arg.yScaler);
            zScaler = std::move(arg.zScaler);
            xRotation = std::move(arg.xRotation);
            yRotation = std::move(arg.yRotation);
            zRotation = std::move(arg.zRotation);
            return *this;
        }

        bool Package<::Atmos::Sprite>::operator==(const Package &arg) const
        {
            return material == arg.material && shaderPatch == arg.shaderPatch && index == arg.index && color == arg.color && xScaler == arg.xScaler &&
                yScaler == arg.yScaler && zScaler == arg.zScaler && xRotation == arg.xRotation && yRotation == arg.yRotation && zRotation == arg.zRotation;
        }

        bool Package<::Atmos::Sprite>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Sprite>::BuildT Package<::Atmos::Sprite>::Build() const
        {
            BuildT ret(*material.Build(), index.Build(), color.Build());
            ret.SetShaderPatch(shaderPatch.Build());
            ret.SetXScaler(xScaler.Build());
            ret.SetYScaler(yScaler.Build());
            ret.SetZScaler(zScaler.Build());
            ret.SetXRotation(xRotation.Build());
            ret.SetYRotation(yRotation.Build());
            ret.SetZRotation(zRotation.Build());
            return ret;
        }

        Package<::Atmos::Sprite>* Package<::Atmos::Sprite>::Clone() const
        {
            return new Package(*this);
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Sound>)
        {
            scribe(audio);
            scribe(position);
        }

        Package<::Atmos::Sound>::Package(Package &&arg) : audio(std::move(arg.audio)), position(std::move(arg.position))
        {}

        Package<::Atmos::Sound> & Package<::Atmos::Sound>::operator=(Package &&arg)
        {
            audio = std::move(arg.audio);
            position = std::move(arg.position);
            return *this;
        }

        bool Package<::Atmos::Sound>::operator==(const Package &arg) const
        {
            return audio == arg.audio && position == arg.position;
        }

        bool Package<::Atmos::Sound>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Sound>::BuildT Package<::Atmos::Sound>::Build() const
        {
            return *::Atmos::AudioRegistry::CreateSound(audio.Build(), position.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Element>)
        {
            scribe(name);
        }

        Package<::Atmos::Element>::Package(Package &&arg) : name(std::move(arg.name))
        {}

        Package<::Atmos::Element>& Package<::Atmos::Element>::operator=(Package &&arg)
        {
            name = std::move(arg.name);
            return *this;
        }

        bool Package<::Atmos::Element>::operator==(const Package &arg) const
        {
            return name == arg.name;
        }

        bool Package<::Atmos::Element>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Element>::BuildT Package<::Atmos::Element>::Build() const
        {
            return BuildT(name.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::CombatTransactionGenerator>)
        {
            scribe(resourceName);
            scribe(statName);
            scribe(element);
            scribe(proficiencyName);
        }

        Package<::Atmos::CombatTransactionGenerator>::Package(Package &&arg) : resourceName(std::move(arg.resourceName)), statName(std::move(arg.statName)),
            element(std::move(arg.element)), proficiencyName(std::move(arg.proficiencyName))
        {}

        Package<::Atmos::CombatTransactionGenerator>& Package<::Atmos::CombatTransactionGenerator>::operator=(Package &&arg)
        {
            resourceName = std::move(arg.resourceName);
            statName = std::move(arg.statName);
            element = std::move(arg.element);
            proficiencyName = std::move(arg.proficiencyName);
            return *this;
        }

        bool Package<::Atmos::CombatTransactionGenerator>::operator==(const Package &arg) const
        {
            return resourceName == arg.resourceName && statName == arg.statName && element == arg.element && proficiencyName == arg.proficiencyName;
        }

        bool Package<::Atmos::CombatTransactionGenerator>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::CombatTransactionGenerator>::BuildT Package<::Atmos::CombatTransactionGenerator>::Build() const
        {
            return BuildT(resourceName.Build(), statName.Build(), element.Build(), proficiencyName.Build());
        }

        INSCRIPTION_SERIALIZE_FUNCTION_DEFINE(Package<::Atmos::Acumen>)
        {
            scribe(value);
        }

        Package<::Atmos::Acumen>::Package(Package &&arg) : value(std::move(arg.value))
        {}

        Package<::Atmos::Acumen>& Package<::Atmos::Acumen>::operator=(Package &&arg)
        {
            value = std::move(arg.value);
            return *this;
        }

        bool Package<::Atmos::Acumen>::operator==(const Package &arg) const
        {
            return value == arg.value;
        }

        bool Package<::Atmos::Acumen>::operator!=(const Package &arg) const
        {
            return !(*this == arg);
        }

        Package<::Atmos::Acumen>::BuildT Package<::Atmos::Acumen>::Build() const
        {
            return BuildT(value.Build());
        }
    }
}