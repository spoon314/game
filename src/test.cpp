#include "catch.hpp"
#include "lib.hpp"

using namespace sf;
using namespace std;

TEST_CASE("TestPlayerClass") {
    Player player("3.png", 200, 270, 32, 32);
    // float time = 0;
    // player.update(time);
    // player.select = 0;
    REQUIRE(player.x == 200);
    REQUIRE(player.y == 270);
};

TEST_CASE("TestPlayerClass2") {
    Player pll("3.png", 200, 270, 32, 32);
    float time = 5;
    float shot=0;
    pll.Left(shot,time);
    REQUIRE(pll.select == 0);
    REQUIRE(pll.speed == doctest::Approx(0.1));
    REQUIRE(shot == doctest::Approx(0.025));
};

TEST_CASE("TestPlayerClass3") {
    Player plr("3.png", 200, 270, 32, 32);
    float time = 5;
    float shot=0;
    plr.Right(shot,time);
    REQUIRE(plr.select == 1);
    REQUIRE(plr.speed == doctest::Approx(0.1));
    REQUIRE(shot == doctest::Approx(0.025));
};

// TEST_CASE("TestPlayerClass4") {
//     Player plx("3.png", 200, 270, 32, 32);
//     float time = 5;
//     plx.update(time);
//     REQUIRE(plx.x < 200);
// };




