#include "MockWindow.h"

MockWindow::MockWindow(Atmos::Logging::Logger& logger) : WindowBase(logger, "Mock")
{}

void MockWindow::Show()
{}

void MockWindow::Exit()
{}

bool MockWindow::IsCurrentlyFocused() const
{
	return false;
}

void MockWindow::Suspend(const Atmos::Time::Milliseconds& time)
{}

bool MockWindow::OnStartFrame()
{
	return true;
}

void* MockWindow::Handle() const
{
	return nullptr;
}

void MockWindow::OnPositionChanged()
{}

void MockWindow::OnSizeChanged()
{}

void MockWindow::OnFullscreenChanged()
{}

auto MockWindow::WindowSizeFromClientSize() const -> Size
{
	return {};
}

auto MockWindow::TotalScreenSize() const -> Size
{
	return {};
}