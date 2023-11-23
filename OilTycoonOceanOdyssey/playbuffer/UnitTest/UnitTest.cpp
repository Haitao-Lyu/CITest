#define CATCH_CONFIG_MAIN
#include "UnitTest.h"

TEST_CASE("Sanity checks :)", "[Sanity]") {
	REQUIRE(1 == 1);
	REQUIRE(2 != 1);
}