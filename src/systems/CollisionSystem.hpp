#pragma once

#include "World.hpp"
#include "components/Collision.hpp"
#include "components/Position.hpp"
#include "ecs/Scene.hpp"
#include "ecs/SceneView.hpp"

/**
 * @brief System that handles entity collision
 *
 */
struct CollisionSystem
{
	/**
	 * @brief Update the system
	 *
	 * @param scene Scene that provides entities and components
	 * @param dt Delta time between two updates
	 */
	void update(Scene& scene, float dt)
	{
		// Iterate over every entity
		for (uint i = 0; i < scene.entities.size(); i++)
		{
			int compId = GetId<Position>();

			if (scene.entities.at(i).mask.test(compId))
			{
				Position* position = static_cast<Position*>(scene.componentPools[compId]->get(i));

				// Iterate over every other entity
				for (uint j = i + 1; j < scene.entities.size(); j++)
				{
					Position* otherPosition = static_cast<Position*>(scene.componentPools[compId]->get(j));

					// If the entities are not the same and in the same position, add a collision component
					if (position->x == otherPosition->x && position->y == otherPosition->y)
					{
						auto collision = scene.Assign<Collision>(scene.entities.at(i).id);
						collision->damage = 1;
					}
				}
			}
		}
	}
};