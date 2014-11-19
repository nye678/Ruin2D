#ifndef __RUIN2D_ENTITYDATA_H_
#define __RUIN2D_ENTITYDATA_H_

#include <glm\glm.hpp>

namespace Ruin2D
{
	/*
	* EntityData manages the basic data for all entities, position,
	* scale, and orientation. Each data point is keyed by the entity's
	* id number.	*/
	class EntityData
	{
	private:
		glm::vec2*	_position;
		glm::vec2*	_scale;
		double* _orientation;

		int _maxEntities;
	public:
		inline const glm::vec2 &getPosition(int entityId) const
		{
			return _position[entityId];
		}

		inline glm::vec2 &getPosition(int entityId)
		{
			return _position[entityId];
		}

		inline void setPosition(int entityId, const glm::vec2 &pos)
		{
			_position[entityId] = pos;
		}

		inline const glm::vec2 &getScale(int entityId) const
		{
			return _scale[entityId];
		}

		inline glm::vec2 &getScale(int entityId)
		{
			return _scale[entityId];
		}

		inline void setScale(int entityId, const glm::vec2 &scl)
		{
			_scale[entityId] = scl;
		}

		inline const double &getOrientation(int entityId) const
		{
			return _orientation[entityId];
		}

		inline double &getOrientation(int entityId)
		{
			return _orientation[entityId];
		}

		inline void setOrientation(int entityId, double ori)
		{
			_orientation[entityId] = ori;
		}

		inline int MaxEntities()
		{
			return _maxEntities;
		}

		EntityData(int maxEntities);
		EntityData(const EntityData &) = delete;
		EntityData(const EntityData &&);
		
		EntityData &operator= (const EntityData &) = delete;
		EntityData &operator= (const EntityData &&);

		~EntityData();
	};
}
#endif