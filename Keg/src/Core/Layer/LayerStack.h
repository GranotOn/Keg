#pragma once
#include "Layer.h"
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
			m_Layers.insert(m_Layers.begin() + m_layerCount++, layer);
		}

		void RemoveLayer(Layer* layer)
		{ 
			auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

			if (it != std::end(m_Layers))
			{
				m_Layers.erase(it);
				m_layerCount--;
			}
		}

		void AddOverlay(Layer* layer)
		{
			m_Layers.push_back(layer);
		}

		void RemoveOverlay(Layer* layer)
		{
			m_Layers.pop_back();
		}

		LayerStack()
		{
			m_layerCount = 0;
		}
		~LayerStack()
		{
			for (Layer* layer : m_Layers)
			{
				delete layer;
			}
		}
	private:
		std::vector<Layer*> m_Layers;
		unsigned short m_layerCount;
	};
}

