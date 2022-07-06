#pragma once
#include <KEnyin.hpp>

namespace KEnyin::KEditor
{
    namespace Panels
    {
        class Hierarchy
        {
        public:
            Hierarchy() = default;
            Hierarchy(const std::shared_ptr<Scene>& context);

            void setContext(const std::shared_ptr<Scene>& context);
            void onImGuiRender();
        private:
            std::shared_ptr<Scene> _context;
        };
    }
}
