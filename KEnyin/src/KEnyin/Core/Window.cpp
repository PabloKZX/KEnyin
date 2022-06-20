#ifdef KE_PLATFORM_WINDOWS
    #include "KEnyin/Platform/Windows/WindowsWindow.hpp"
#elif KE_PLATFORM_MACOS
    #include "KEnyin/Platform/MacOs/MacOsWindow.hpp"
#endif

namespace KEnyin
{
    Window* Window::create(const WindowProps& props)
    {
        #ifdef KE_PLATFORM_WINDOWS
            return new WindowsWindow(props);
        #elif KE_PLATFORM_MACOS
            return new MacOsWindow(props);
        #else
            KECheck_Engine(false, "Unknown platform!");
            return nullptr;
        #endif
    }
}
