#include "rrx.h"

#include "IceGL.hpp"
#include "Renderer.hpp"
#include "RenderConfigs.hpp"
#include "DMAProxyBusConnector.hpp"

static const uint32_t RESOLUTION_H = 600;
static const uint32_t RESOLUTION_W = 1024;
rr::DMAProxyBusConnector m_busConnector {};
#if VARIANT_RRXIF == 1
    rr::Renderer<rr::RenderConfigRRXIFZynq> m_renderer { m_busConnector };
#endif // VARIANT_RRXIF
#if VARIANT_RRXEF == 1
    rr::Renderer<rr::RenderConfigRRXEFZynq> m_renderer { m_busConnector };
#endif // VARIANT_RRXEF

void rrx_init()
{
    rr::IceGL::createInstance(m_renderer);
    m_renderer.setRenderResolution(RESOLUTION_W, RESOLUTION_H);
}

void rrx_swapFramebuffer()
{
    rr::IceGL::getInstance().render();
}

void rrx_GetDrawableSize(int* x, int* y)
{
    *x = RESOLUTION_W;
    *y = RESOLUTION_H;
}