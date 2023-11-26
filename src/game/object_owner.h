#ifndef UR_OBJECT_OWNER_H
#define UR_OBJECT_OWNER_H

#include "SDL.h"
#include "proto/agm.pb.h"
#include "Vector2D.h"
#include "Point2D.h"

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

  /**
   * Describes the result of a collision check.
   */
  struct CollisionResult {
      enum Axis {
          None = 0,
          Vertical = 1 << 0,
          Horizontal = 1 << 1,
      };

      Axis collidedOn = Axis::None;

      /**
       * The transformed vector of movement of the object, clamped by any collisions.
       */
      Vector2D clampedVector = Vector2D();

    /**
     * @brief Index of the tile type that was collided with.
     *
     * @note This is the first tile that is collided with
     * by the vector; the clamped vector may collide with other tiles (such as approaching a corner at an angle).
     */
    Sint64 tileTypeIdx = 0;

      // TODO: adopt std::optional?
    /**
     * @brief  Pointer of the tile type that was collided with.
     *
     * @note This is the first tile that is collided with
     * by the vector; the clamped vector may collide with other tiles (such as approaching a corner at an angle).
     *
     * `nullptr` if `collidedOn` is `Axis::None`.
     */
    TileType *tileType = nullptr;
  };

  /**
   * @brief Interrogate the object owner to determine if any collisions
   * with map geometry can occur along the given path. If so,
   * returns what map tile the collision would occur at and the exact location
   * of the collision.
   *
   * @param obj Object to check for collisions.
   * @param position Position of the object.
   * @param vector Vector of movement of the object.
   *
   * @return CollisionResult struct.
   */
  virtual CollisionResult checkMapPathCollision(Object *obj, Point2D position, Vector2D vector) = 0;
  // NOTE: this approach to map collisions has some limitations: the object's
  // physics logic cannot be aware of the details of the geometry. But it works for
  // now.

  //   virtual Object *checkObjectCollision(Object *obj, Sint64 *xpos, Sint64
  //   *ypos);
};
} // namespace ur

#endif // UR_OBJECT_OWNER_H
