#pragma once
#include "Layer.h"
#include "Core/Logger/Logger.h"
#include <vector>
#include <algorithm>
#include <iterator>

namespace Keg
{
	class LayerStack
	{
	public:
		void AddLayer(Layer* layer)
		{
			KEG_ENGINE_INFO("Adding layer ({0})", layer->GetDebugName());
			m_Layers.insert(m_Layers.begin() + m_layerCount++, layer);
			layer->OnAttach();
		}

		void RemoveLayer(Layer* layer)
		{ 
			auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

			if (it != std::end(m_Layers))
			{
				KEG_ENGINE_INFO("Removing layer ({0})", layer->GetDebugName());
				m_Layers.erase(it);
				layer->OnDetach();
				delete layer;
				m_layerCount--;
			}
			else
			{
				KEG_ENGINE_WARN("Tryed removing layer ({0}), but wasn't found in stack", layer->GetDebugName());
			}
		}

		void AddOverlay(Layer* layer)
		{
			KEG_ENGINE_INFO("Adding overlay ({0})", layer->GetDebugName());
			m_Layers.push_back(layer);
			layer->OnAttach();
		}

		void RemoveOverlay()
		{
			if (m_Layers.size() > 0)
			{
				Layer* overlay = m_Layers.back();
				KEG_ENGINE_INFO("Removing overlay ({0})", overlay->GetDebugName());
				overlay->OnDetach();
				delete overlay;
				m_Layers.pop_back();
			}
			else
			{ 
				KEG_ENGINE_WARN("Tryed removing overlay, but none was found");
			}
		}

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }


		LayerStack()
		{
			KEG_ENGINE_INFO("Layer stack initialized");
			m_layerCount = 0;
		}
		~LayerStack()
		{
			KEG_ENGINE_INFO("Destructcing layer stack");
			for (Layer* layer : m_Layers)
			{
				KEG_ENGINE_TRACE("Removing layer ({0})", layer->GetDebugName());
				layer->OnDetach();
				delete layer;
			}
		}
	private:
		std::vector<Layer*> m_Layers;
		unsigned short m_layerCount;
	};
}

