#include "forces.h"

#define CLOSE 1

typedef struct {
    double constant;
    List *bodies;
} force_info;

void gravity_creator(force_info *aux) {
    assert(aux != NULL);
    double G = aux->constant;
    Body *body1 = (Body *) list_get(aux->bodies, 0);
    Body *body2 = (Body *) list_get(aux->bodies, 1);
    assert(G > 0 && body1 != NULL && body2 != NULL);
    double m1 = body_get_mass(body1);
    double m2 = body_get_mass(body2);
    Vector r  = vec_subtract(body_get_centroid(body2), body_get_centroid(body1));
    double force = G * m1 * m2 / vec_dot(r, r);
    double magnitude = sqrt(vec_dot(r, r));
    Vector force_gravity = vec_multiply(force / magnitude, r);

    if (magnitude > CLOSE) {
        body_add_force(body1, force_gravity);
        body_add_force(body2, vec_negate(force_gravity));
    }
}

void create_newtonian_gravity(Scene *scene, double G, Body *body1, Body *body2) {
    assert(scene != NULL && G > 0 && body1 != NULL && body2 != NULL);
    force_info *aux = malloc(sizeof(force_info));
    assert(aux != NULL);
    aux->constant = G;

    List *bodies = list_init(2, NULL);
    list_add(bodies, body1);
    list_add(bodies, body2);
    aux->bodies = bodies;

    scene_add_bodies_force_creator(scene, (ForceCreator) gravity_creator, aux,
        bodies, (FreeFunc) free);
}

void spring_creator(force_info *aux) {
    assert(aux != NULL);
    double k = aux->constant;
    Body *body1 = (Body *) list_get(aux->bodies, 0);
    Body *body2 = (Body *) list_get(aux->bodies, 1);
    assert(k > 0 && body1 != NULL && body2 != NULL);
    Vector x  = vec_subtract(body_get_centroid(body2), body_get_centroid(body1));

    body_add_force(body1, vec_multiply(k, x));
    body_add_force(body2, vec_multiply(-k, x));
}

void create_spring(Scene *scene, double k, Body *body1, Body *body2) {
    assert(scene != NULL && k >= 0 && body1 != NULL && body2 != NULL);
    force_info *aux = malloc(sizeof(force_info));
    assert(aux != NULL);
    aux->constant = k;

    List *bodies = list_init(2, NULL);
    list_add(bodies, body1);
    list_add(bodies, body2);
    aux->bodies = bodies;

    scene_add_bodies_force_creator(scene, (ForceCreator) spring_creator, aux,
        bodies, (FreeFunc) free);
}

void drag_creator(force_info *aux) {
    assert(aux != NULL);
    double gamma = aux->constant;
    Body *body = (Body *) list_get(aux->bodies, 0);
    assert(gamma >= 0 && body != NULL);

    body_add_force(body, vec_multiply(-gamma, body_get_velocity(body)));
}

void create_drag(Scene *scene, double gamma, Body *body) {
    assert(scene != NULL && gamma >= 0 && body != NULL);
    force_info *aux = malloc(sizeof(force_info));
    assert(aux != NULL);
    aux->constant = gamma;

    List *bodies = list_init(1, NULL);
    list_add(bodies, body);
    aux->bodies = bodies;

    scene_add_bodies_force_creator(scene, (ForceCreator) drag_creator, aux,
        bodies, (FreeFunc) free);
}

void destruction_creator(force_info *aux) {
    assert(aux != NULL);
    Body *body1 = (Body *) list_get(aux->bodies, 0);
    Body *body2 = (Body *) list_get(aux->bodies, 1);
    List *shape1 = body_get_shape(body1);
    List *shape2 = body_get_shape(body2);
    
    if (find_collision(shape1, shape2)) {
        body_remove(body1);
        body_remove(body2);
    }
}

void create_destructive_collision(Scene *scene, Body *body1, Body *body2) {
    assert(scene != NULL && body1 != NULL && body2 != NULL);
    force_info *aux = malloc(sizeof(force_info));
    assert(aux != NULL);
    aux->constant = 0;

    List *bodies = list_init(2, NULL);
    list_add(bodies, body1);
    list_add(bodies, body2);
    aux->bodies = bodies;

    scene_add_bodies_force_creator(scene, (ForceCreator) destruction_creator, 
        aux, bodies, (FreeFunc) free);
}
