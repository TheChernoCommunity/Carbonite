//
//	Created by MarcasRealAccount on 11. Nov. 2020
//

#pragma once

#include <string>
#include <unordered_map>

template <typename T>
class Registry
{
public:
	// Register an element to the registry.
	static void RegisterElement(const std::string& id, T* element)
	{
		Registry<T>::m_Instance->m_Elements.insert({ id, element });
	}

	// Get an element from the registry.
	static const T* GetElement(const std::string& id)
	{
		auto itr = Registry<T>::m_Instance->m_Elements.find(id);
		if (itr != Registry<T>::m_Instance->m_Elements.end())
		{
			return &itr->second;
		}
		return nullptr;
	}

private:
	std::unordered_map<std::string, T> m_Elements; // The elements in the registry.

private:
	static Registry<T>* m_Instance; // The static registry instance.
};
