#include "KeyData.h"

namespace Creation::Editing
{
    EnumDescriptors<Atmos::Input::Key> EnumTraits<Atmos::Input::Key>::descriptors({
        { EnumT::LeftMouseButton, "LeftMouseButton" },
        { EnumT::MiddleMouseButton, "MiddleMouseButton" },
        { EnumT::RightMouseButton, "RightMouseButton" },
        { EnumT::X1MouseButton, "X1MouseButton" },
        { EnumT::X2MouseButton, "X2MouseButton" },

        { EnumT::A, "A" },
        { EnumT::B, "B" },
        { EnumT::C, "C" },
        { EnumT::D, "D" },
        { EnumT::E, "E" },
        { EnumT::F, "F" },
        { EnumT::G, "G" },
        { EnumT::H, "H" },
        { EnumT::I, "I" },
        { EnumT::J, "J" },
        { EnumT::K, "K" },
        { EnumT::L, "L" },
        { EnumT::M, "M" },
        { EnumT::N, "N" },
        { EnumT::O, "O" },
        { EnumT::P, "P" },
        { EnumT::Q, "Q" },
        { EnumT::R, "R" },
        { EnumT::S, "S" },
        { EnumT::T, "T" },
        { EnumT::U, "U" },
        { EnumT::V, "V" },
        { EnumT::W, "W" },
        { EnumT::X, "X" },
        { EnumT::Y, "Y" },
        { EnumT::Z, "Z" },

        { EnumT::Zero, "Zero" },
        { EnumT::One, "One" },
        { EnumT::Two, "Two" },
        { EnumT::Three, "Three" },
        { EnumT::Four, "Four" },
        { EnumT::Five, "Five" },
        { EnumT::Six, "Six" },
        { EnumT::Seven, "Seven" },
        { EnumT::Eight, "Eight" },
        { EnumT::Nine, "Nine" },

        { EnumT::Left, "Left" },
        { EnumT::Up, "Up" },
        { EnumT::Right, "Right" },
        { EnumT::Down, "Down" },

        { EnumT::F1, "F1" },
        { EnumT::F2, "F2" },
        { EnumT::F3, "F3" },
        { EnumT::F4, "F4" },
        { EnumT::F5, "F5" },
        { EnumT::F6, "F6" },
        { EnumT::F7, "F7" },
        { EnumT::F8, "F8" },
        { EnumT::F9, "F9" },
        { EnumT::F10, "F10" },
        { EnumT::F11, "F11" },
        { EnumT::F12, "F12" },
        { EnumT::F13, "F13" },
        { EnumT::F14, "F14" },
        { EnumT::F15, "F15" },
        { EnumT::F16, "F16" },
        { EnumT::F17, "F17" },
        { EnumT::F18, "F18" },
        { EnumT::F19, "F19" },
        { EnumT::F20, "F20" },
        { EnumT::F21, "F21" },
        { EnumT::F22, "F22" },
        { EnumT::F23, "F23" },
        { EnumT::F24, "F24" },

        { EnumT::LeftAlt, "LeftAlt" },
        { EnumT::LeftControl, "LeftControl" },
        { EnumT::LeftShift, "LeftShift" },
        { EnumT::LeftBracket, "LeftBracket" },
        { EnumT::LeftGui, "LeftGui" },

        { EnumT::RightAlt, "RightAlt" },
        { EnumT::RightControl, "RightControl" },
        { EnumT::RightShift, "RightShift" },
        { EnumT::RightBracket, "RightBracket" },
        { EnumT::RightGui, "RightGui" },

        { EnumT::PageDown, "PageDown" },
        { EnumT::PageUp, "PageUp" },

        { EnumT::Keypad0, "Keypad0" },
        { EnumT::Keypad00, "Keypad00" },
        { EnumT::Keypad000, "Keypad000" },
        { EnumT::Keypad1, "Keypad1" },
        { EnumT::Keypad2, "Keypad2" },
        { EnumT::Keypad3, "Keypad3" },
        { EnumT::Keypad4, "Keypad4" },
        { EnumT::Keypad5, "Keypad5" },
        { EnumT::Keypad6, "Keypad6" },
        { EnumT::Keypad7, "Keypad7" },
        { EnumT::Keypad8, "Keypad8" },
        { EnumT::Keypad9, "Keypad9" },
        { EnumT::KeypadA, "KeypadA" },
        { EnumT::KeypadB, "KeypadB" },
        { EnumT::KeypadC, "KeypadC" },
        { EnumT::KeypadD, "KeypadD" },
        { EnumT::KeypadE, "KeypadE" },
        { EnumT::KeypadF, "KeypadF" },
        { EnumT::KeypadAmpersand, "KeypadAmpersand" },
        { EnumT::KeypadAt, "KeypadAt" },
        { EnumT::KeypadBackspace, "KeypadBackspace" },
        { EnumT::KeypadBinary, "KeypadBinary" },
        { EnumT::KeypadClear, "KeypadClear" },
        { EnumT::KeypadClearEntry, "KeypadClearEntry" },
        { EnumT::KeypadColon, "KeypadColon" },
        { EnumT::KeypadComma, "KeypadComma" },
        { EnumT::KeypadAmpersandAmpersand, "KeypadAmpersandAmpersand" },
        { EnumT::KeypadBarBar, "KeypadBarBar" },
        { EnumT::KeypadDecimal, "KeypadDecimal" },
        { EnumT::KeypadForwardSlash, "KeypadForwardSlash" },
        { EnumT::KeypadEnter, "KeypadEnter" },
        { EnumT::KeypadEquals, "KeypadEquals" },
        { EnumT::KeypadEqualsAS400, "KeypadEqualsAS400" },
        { EnumT::KeypadExclamation, "KeypadExclamation" },
        { EnumT::KeypadGreater, "KeypadGreater" },
        { EnumT::KeypadLess, "KeypadLess" },
        { EnumT::KeypadPound, "KeypadPound" },
        { EnumT::KeypadHexadecimal, "KeypadHexadecimal" },
        { EnumT::KeypadLeftBrace, "KeypadLeftBrace" },
        { EnumT::KeypadLeftParenthesis, "KeypadLeftParenthesis" },
        { EnumT::KeypadMemAdd, "KeypadMemAdd" },
        { EnumT::KeypadMemClear, "KeypadMemClear" },
        { EnumT::KeypadMemDivide, "KeypadMemDivide" },
        { EnumT::KeypadMemMultiply, "KeypadMemMultiply" },
        { EnumT::KeypadMemRecall, "KeypadMemRecall" },
        { EnumT::KeypadMemStore, "KeypadMemStore" },
        { EnumT::KeypadMemSubtract, "KeypadMemSubtract" },
        { EnumT::KeypadHyphen, "KeypadHyphen" },
        { EnumT::KeypadAsterisk, "KeypadAsterisk" },
        { EnumT::KeypadOctal, "KeypadOctal" },
        { EnumT::KeypadPercent, "KeypadPercent" },
        { EnumT::KeypadPeriod, "KeypadPeriod" },
        { EnumT::KeypadPlus, "KeypadPlus" },
        { EnumT::KeypadPlusMinus, "KeypadPlusMinus" },
        { EnumT::KeypadPower, "KeypadPower" },
        { EnumT::KeypadRightBrace, "KeypadRightBrace" },
        { EnumT::KeypadRightParenthesis, "KeypadRightParenthesis" },
        { EnumT::KeypadSpace, "KeypadSpace" },
        { EnumT::KeypadTab, "KeypadTab" },
        { EnumT::KeypadBar, "KeypadBar" },
        { EnumT::KeypadXor, "KeypadXor" },

        { EnumT::BrightnessUp, "BrightnessUp" },
        { EnumT::BrightnessDown, "BrightnessDown" },

        { EnumT::VolumeUp, "VolumeUp" },
        { EnumT::VolumeDown, "VolumeDown" },

        { EnumT::AudioMute, "AudioMute" },
        { EnumT::AudioNext, "AudioNext" },
        { EnumT::AudioPlay, "AudioPlay" },
        { EnumT::AudioPrevious, "AudioPrevious" },
        { EnumT::AudioStop, "AudioStop" },

        { EnumT::AcBack, "AcBack" },
        { EnumT::AcBookmarks, "AcBookmarks" },
        { EnumT::AcForward, "AcForward" },
        { EnumT::AcHome, "AcHome" },
        { EnumT::AcRefresh, "AcRefresh" },
        { EnumT::AcSearch, "AcSearch" },
        { EnumT::AcStop, "AcStop" },

        { EnumT::IlluminationDown, "IlluminationDown" },
        { EnumT::IlluminationUp, "IlluminationUp" },
        { EnumT::IlluminationToggle, "IlluminationToggle" },

        { EnumT::Backslash, "Backslash" },
        { EnumT::Backspace, "Backspace" },
        { EnumT::Comma, "Comma" },
        { EnumT::Quote, "Quote" },
        { EnumT::Again, "Again" },
        { EnumT::AltErase, "AltErase" },
        { EnumT::Application, "Application" },
        { EnumT::Calculator, "Calculator" },
        { EnumT::Cancel, "Cancel" },
        { EnumT::CapsLock, "CapsLock" },
        { EnumT::Clear, "Clear" },
        { EnumT::ClearAgain, "ClearAgain" },
        { EnumT::Computer, "Computer" },
        { EnumT::Copy, "Copy" },
        { EnumT::CrSel, "CrSel" },
        { EnumT::CurrencySubUnit, "CurrencySubUnit" },
        { EnumT::CurrencyUnit, "CurrencyUnit" },
        { EnumT::Cut, "Cut" },
        { EnumT::DecimalSeparator, "DecimalSeparator" },
        { EnumT::Del, "Del" },
        { EnumT::DisplaySwitch, "DisplaySwitch" },
        { EnumT::Eject, "Eject" },
        { EnumT::End, "End" },
        { EnumT::Equals, "Equals" },
        { EnumT::Escape, "Escape" },
        { EnumT::Execute, "Execute" },
        { EnumT::ExSel, "ExSel" },
        { EnumT::Find, "Find" },
        { EnumT::Grave, "Grave" },
        { EnumT::Help, "Help" },
        { EnumT::Home, "Home" },
        { EnumT::Insert, "Insert" },
        { EnumT::Mail, "Mail" },
        { EnumT::MediaSelect, "MediaSelect" },
        { EnumT::Menu, "Menu" },
        { EnumT::Hyphen, "Hyphen" },
        { EnumT::ModeSwitch, "ModeSwitch" },
        { EnumT::Mute, "Mute" },
        { EnumT::Numlock, "Numlock" },
        { EnumT::Oper, "Oper" },
        { EnumT::Out, "Out" },
        { EnumT::Paste, "Paste" },
        { EnumT::Pause, "Pause" },
        { EnumT::Period, "Period" },
        { EnumT::Power, "Power" },
        { EnumT::PrintScreen, "PrintScreen" },
        { EnumT::Prior, "Prior" },
        { EnumT::Enter, "Enter" },
        { EnumT::ScrollLock, "ScrollLock" },
        { EnumT::Select, "Select" },
        { EnumT::Semicolon, "Semicolon" },
        { EnumT::Separator, "Separator" },
        { EnumT::ForwardSlash, "ForwardSlash" },
        { EnumT::Sleep, "Sleep" },
        { EnumT::Space, "Space" },
        { EnumT::Stop, "Stop" },
        { EnumT::SysReq, "SysReq" },
        { EnumT::Tab, "Tab" },
        { EnumT::ThousandsSeparator, "ThousandsSeparator" },
        { EnumT::Undo, "Undo" },
        { EnumT::WorldWideWeb, "WorldWideWeb" } });

    NexusBatch<Data::ModifierKey>::NexusBatch(wxPropertyGrid& grid, NexusHistory nexusHistory, UI& ui) :
        NexusBatchCommon(grid),
        key("Key", "Key", nullptr, grid, nexusHistory, ui)
    {
        SetupProperties();
    }

    NexusBatch<Data::ModifierKey>::NexusBatch(NexusBatch&& arg) noexcept :
        NexusBatchCommon(std::move(arg)),
        key(std::move(arg.key))
    {
        SetupProperties();
    }

    void NexusBatch<Data::ModifierKey>::SetupProperties()
    {
        Auto(key, &Nexus::key);
    }

    Nexus<Data::ModifierKey>::Nexus(
        DataT& data, NexusNode* parent, NexusHistory nexusHistory, UI& ui, Arca::Reliquary& reliquary)
        :
        EditableNexusCommon(
            data,
            parent,
            nexusHistory,
            ui,
            reliquary,
            CalculateLabel(data.key)),
        key(data.key, this, nexusHistory, ui, reliquary, "Key")
    {
        SetupChildren();
    }

    Nexus<Data::ModifierKey>::Nexus(Nexus&& arg, NexusNode* parent) noexcept :
        EditableNexusCommon(std::move(arg), parent),
        key(std::move(arg.key), this)
    {
        SetupChildren();
    }

    void Nexus<Data::ModifierKey>::SetupChildren()
    {
        autoHandler.Auto(*this, key, &DataT::key);

        eventConnections =
        {
            key.onDataChanged.Subscribe([this](const Atmos::Input::Key& key)
            {
                ChangeLabel(CalculateLabel(key));
            })
        };
    }

    String Nexus<Data::ModifierKey>::CalculateLabel(Atmos::Input::Key key) const
    {
        return *EnumTraits<Atmos::Input::Key>::descriptors.Name(key);
    }
}