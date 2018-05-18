#pragma once

#include <Atmos/WindowBase.h>

class MockWindow final : public Atmos::Window::WindowBase
{
public:
    MockWindow(Atmos::Logging::Logger& logger);
public:
    void Show() override;
    void Exit() override;
    [[nodiscard]] bool IsCurrentlyFocused() const override;
    void Suspend(const Atmos::Time::Milliseconds& time) override;
    bool OnStartFrame() override;

    [[nodiscard]] void* Handle() const override;
protected:
    void OnPositionChanged() override;
    void OnSizeChanged() override;
    void OnFullscreenChanged() override;
    [[nodiscard]] Size WindowSizeFromClientSize() const override;

    [[nodiscard]] Size TotalScreenSize() const override;
};