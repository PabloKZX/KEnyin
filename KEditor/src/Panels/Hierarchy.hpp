#pragma once
#include <KEnyin.hpp>

namespace KEnyin::KEditor
{
    namespace Panels
    {
        class Hierarchy
        {
            using OnEntitySelectedChangeCallback = std::function<void(Entity)>;

        public:
            Hierarchy() = default;
            Hierarchy(const std::shared_ptr<Scene>& context);

            void setContext(const std::shared_ptr<Scene>& context);
            void setOnEntitySelectedChangedCallback(OnEntitySelectedChangeCallback onEntitySelectedChanged);
            void onImGuiRender();
        private:
            void drawEntity(Entity entity);

            std::shared_ptr<Scene> _context;
            Entity _selectedEntity;
            OnEntitySelectedChangeCallback _onEntitySelectedChanged;
        };
    }
}
