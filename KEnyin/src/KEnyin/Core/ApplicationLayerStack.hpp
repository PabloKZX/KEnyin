#pragma once

#include "KEnyin/Core/ApplicationLayer.hpp"

namespace KEnyin
{
    class ApplicationLayerStack
    {
    public:
        ApplicationLayerStack() = default;
        ~ApplicationLayerStack();
        
        void pushLayer(ApplicationLayer* layer);
        void pushOverlay(ApplicationLayer* overlay);
        void popLayer(ApplicationLayer* layer);
        void popOverlay(ApplicationLayer* overlay);
        
        std::vector<ApplicationLayer*>::iterator begin() { return _layers.begin(); }
        std::vector<ApplicationLayer*>::iterator end() { return _layers.end(); }
        std::vector<ApplicationLayer*>::reverse_iterator rbegin() { return _layers.rbegin(); }
        std::vector<ApplicationLayer*>::reverse_iterator rend() { return _layers.rend(); }

        std::vector<ApplicationLayer*>::const_iterator begin() const { return _layers.begin(); }
        std::vector<ApplicationLayer*>::const_iterator end()    const { return _layers.end(); }
        std::vector<ApplicationLayer*>::const_reverse_iterator rbegin() const { return _layers.rbegin(); }
        std::vector<ApplicationLayer*>::const_reverse_iterator rend() const { return _layers.rend(); }
    private:
        std::vector<ApplicationLayer*> _layers;
        unsigned int _layerInsertIndex = 0;
    };
}
