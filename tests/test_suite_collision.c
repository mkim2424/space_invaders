#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"
#include "collision.h"
#include "test_util.h"


// makes square given coordinates of upper left and lower right corners
List *make_square(Vector c1, Vector c2) {
    double height = fabs(c1.y - c2.y);
    List *sq = list_init(4, (FreeFunc) vec_free);
    Vector *up_left = vec_init(c1.x, c1.y);
    Vector *low_left = vec_init(c1.x, c1.x - height);
    Vector *low_right = vec_init(c2.x, c2.y);
    Vector *up_right = vec_init(c2.x, c2.y + height);
    list_add(sq, up_left);
    list_add(sq, low_left);
    list_add(sq, low_right);
    list_add(sq, up_right);
    return sq;
}


void test_does_overlap() {
    // overlapping squares
    List *square1 = make_square((Vector) {0, 2}, (Vector) {2, 0});
    List *square2 = make_square((Vector) {1, 2}, (Vector) {3, 0});
    assert(find_collision(square1, square2));
    // square4 inside of square3
    List *square3 = make_square((Vector) {0, 5}, (Vector) {5, 0});
    List *square4 = make_square((Vector) {2, 2}, (Vector) {3, 1});
    assert(find_collision(square3, square4));
    // two squares just touching
    List *square5 = make_square((Vector) {0, 5}, (Vector) {5, 0});
    List *square6 = make_square((Vector) {5, 5}, (Vector) {10, 0});
    assert(find_collision(square5, square6));
    list_free(square1);
    list_free(square2);
    list_free(square3);
    list_free(square4);
    list_free(square5);
    list_free(square6);
}

void test_does_not_overlap() {
    List *square1 = make_square((Vector) {0, 2}, (Vector) {2, 0});
    List *square2 = make_square((Vector) {4, 2}, (Vector) {6, 0});
    assert(find_collision(square1, square2) == false);
    list_free(square1);
    list_free(square2);
}


int main(int argc, char *argv[]) {
    // Run all tests? True if there are no command-line arguments
    bool all_tests = argc == 1;
    // Read test name from file
    char testname[100];
    if (!all_tests) {
        read_testname(argv[1], testname, sizeof(testname));
    }

    DO_TEST(test_does_overlap)
    DO_TEST(test_does_not_overlap)

    puts("collision_test PASS");

    return 0;
}
