#pragma once
#include <map>

namespace Utils
{
	template<typename T_RESID, typename T_RES>
	class ResourceManager
	{
	public:
		
		T_RES const& getResource(T_RESID resourceId) const
		{
			return this->m_resources.at(resourceId);
		}

	protected:
		void addResource(T_RESID resourceId, std::string const& filePath)
		{
			T_RES res;
			res.loadFromFile(filePath);

			m_resources.insert(std::make_pair(resourceId, res));
		}

	private:
		std::map<T_RESID, T_RES> m_resources;
	};
}