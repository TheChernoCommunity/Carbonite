//
//	Created by MarcasRealAccount on 11. Nov. 2020
//

#pragma once

#include <string>
#include <unordered_map>

namespace gp1 {

	template <typename T>
	class Registry {
	public:
		static void RegisterElement(const std::string& id, T element) {
			Registry<T>::m_Instance->m_Elements.insert({ id, element });
		}

		static const T* GetElement(const std::string& id) {
			auto itr = Registry<T>::m_Instance->m_Elements.find(id);
			if (itr != Registry<T>::m_Instance->m_Elements.end()) {
				return &itr->second;
			}
			return nullptr;
		}

	private:
		static Registry<T>* m_Instance;

		std::unordered_map<std::string, T> m_Elements;
	};

} // namespace gp1
