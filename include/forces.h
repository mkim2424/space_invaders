#ifndef __FORCES_H__
#define __FORCES_H__

#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "scene.h"
#include "collision.h"

/**
 * Adds a Newtonian gravitational force between two bodies in a scene.
 * See https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation#Vector_form.
 * The force should not be applied when the bodies are very close,
 * because its magnitude blows up as the distance between the bodies goes to 0.
 *
 * @param scene the scene containing the bodies
 * @param G the gravitational proportionality constant
 * @param body1 the first body
 * @param body2 the second body
 */
void create_newtonian_gravity(Scene *scene, double G, Body *body1, Body *body2);

/**
 * Adds a Hooke's-Law spring force between two bodies in a scene.
 * See https://en.wikipedia.org/wiki/Hooke%27s_law.
 *
 * @param scene the scene containing the bodies
 * @param k the Hooke's constant for the spring
 * @param body1 the first body
 * @param body2 the second body
 */
void create_spring(Scene *scene, double k, Body *body1, Body *body2);

/**
 * Adds a drag force on a body proportional to its velocity.
 * The force points opposite the body's velocity.
 *
 * @param scene the scene containing the bodies
 * @param gamma the proportionality constant between force and velocity
 *   (higher gamma means more drag)
 * @param body the body to slow down
 */
void create_drag(Scene *scene, double gamma, Body *body);

/**
 * Adds a ForceCreator to a scene that destroys two bodies when they collide.
 * The bodies should be destroyed by calling body_remove().
 *
 * @param scene the scene containing the bodies
 * @param body1 the first body
 * @param body2 the second body
 */
void create_destructive_collision(Scene *scene, Body *body1, Body *body2);

#endif // #ifndef __FORCES_H__
