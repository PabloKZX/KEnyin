#include "pch.hpp"
#include "KEnyin/Core/ApplicationLayerStack.hpp"

namespace KEnyin
{
    ApplicationLayerStack::~ApplicationLayerStack()
    {
        for (ApplicationLayer* layer : _layers)
        {
            layer->onDetach();
            delete layer;
        }
    }

    void ApplicationLayerStack::pushLayer(ApplicationLayer* layer)
    {
        _layers.emplace(_layers.begin() + _layerInsertIndex, layer);
        _layerInsertIndex++;
    }

    void ApplicationLayerStack::pushOverlay(ApplicationLayer* overlay)
    {
        _layers.emplace_back(overlay);
    }

    void ApplicationLayerStack::popLayer(ApplicationLayer* layer)
    {
        auto it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);
        if (it != _layers.begin() + _layerInsertIndex)
        {
            layer->onDetach();
            _layers.erase(it);
            _layerInsertIndex--;
        }
    }

    void ApplicationLayerStack::popOverlay(ApplicationLayer* overlay)
    {
        auto it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);
        if (it != _layers.end())
        {
            overlay->onDetach();
            _layers.erase(it);
        }
    }
}
