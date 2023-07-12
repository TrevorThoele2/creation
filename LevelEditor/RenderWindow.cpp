
#include "RenderWindow.h"
#include <wx/dcclient.h>

#include <Atmos/Environment.h>
#include <Atmos/GraphicsHandlerBase.h>

namespace Creation
{
    void RenderWindow::OnPaint(wxPaintEvent &e)
    {
        wxPaintDC dc(this);

        auto graphicsHandler = Atmos::Environment::GetGraphics();
        if (!graphicsHandler->Start())
        {
            e.Skip();
            return;
        }

        auto &sprites = GetSprites();

        graphicsHandler->ClearTarget(Atmos::GraphicsHandlerBase::Target::MAIN, refreshColor);
        Atmos::GraphicsHandlerBase::ScreenDimensions prevDimensions(graphicsHandler->GetMainDimensions());
        graphicsHandler->SetMainDimensions(Atmos::GraphicsHandlerBase::ScreenDimensions(GetClientSize().GetWidth(), GetClientSize().GetHeight()));
        graphicsHandler->StartSprites(sprites.size());

        for (auto &loop : sprites)
        {
            if(loop->IsEnabled() && loop->GetMaterial().IsValid())
                graphicsHandler->RenderSprite(*loop, 0, 0);
        }

        graphicsHandler->EndSprites();
        graphicsHandler->End();
        graphicsHandler->Present(GetHWND());
        graphicsHandler->SetMainDimensions(prevDimensions);

        e.Skip();
    }

    RenderWindow::RenderWindow(wxWindow *parent, wxWindowID winid, const wxPoint &pos, const wxSize &size, const wxString &name) : wxWindow(parent, winid, pos, size, wxFULL_REPAINT_ON_RESIZE, name), refreshColor(255, 255, 0, 0)
    {
        SetBackgroundColour(*wxBLACK);
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_PAINT, &RenderWindow::OnPaint, this);
    }

    void RenderWindow::SetRefreshColor(const Atmos::Color &set)
    {
        refreshColor = set;
    }

    const Atmos::Color& RenderWindow::GetRefreshColor() const
    {
        return refreshColor;
    }
}