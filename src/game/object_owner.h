#ifndef UR_OBJECT_OWNER_H
#define UR_OBJECT_OWNER_H

#include "SDL.h"
#include "proto/agm.pb.h"

namespace ur {

// forward declaration of Object:
class Object;

class ObjectOwner {
public:
  /**
   * @brief Register an object to participate in this layer's physics run.
   *
   * @param obj
   */
  virtual void registerObject(Object *obj) = 0;

  // OK, object owner needs to be able coordinate physical interactions.

  // current interface:
  // - objects check their owner (formerly layer) for map interactions.
  // - objects check their owner (formerly layer) all other objects for
  // collisions.

  struct Line2D {
    Sint64 x1;
    Sint64 y1;
    Sint64 x2;
    Sint64 y2;
  };

  struct CollisionResult {
    bool collision;

    // if collision is set, the following fields are available.

    /**
     * @brief Location of collision in X pixel coordinate.
     *
     * 0 if `collision` is false.
     */
    Sint64 x = 0;

    /**
     * @brief Location of collision in Y pixel coordinate.
     *
     * 0 if `collision` is false.
     */
    Sint64 y = 0;

    /**
     * @brief Index of the tile type that was collided with.
     */
    Sint64 tileTypeIdx = 0;

    /**
     * @brief Pointer to the tile type that was collided with.
     *
     * null if `collision` is false.
     */
    TileType *tileType = nullptr;
  };

  /**
   * @brief Interrogate the object owner to determine if any collisions
   * with map geoemetry can occur along the given path. If so,
   * returns what map tile the collision would occur at and the exact location
   * of the collision.
   *
   * @param obj Object to check for collisions.
   * @param xpos X position of the object.
   * @param ypos Y position of the object.
   * @param xvel X velocity of the object.
   * @param yvel Y velocity of the object.
   *
   * @return CollisionResult struct.
   */
  virtual CollisionResult checkMapPathCollision(Object *obj, Sint64 xpos,
                                                Sint64 ypos, Sint64 xvel,
                                                Sint64 yvel) = 0;

  // NOTE: this approach to map collisions has some limitations: the object's
  // physics logic cannot be aware of any of the geometry. But it works for
  // now.

  //   virtual Object *checkObjectCollision(Object *obj, Sint64 *xpos, Sint64
  //   *ypos);
};
} // namespace ur

#endif // UR_OBJECT_OWNER_H
