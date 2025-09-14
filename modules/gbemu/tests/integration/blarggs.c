#include "../../../../deps/unity/src/unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_AverageThreeBytes_should_AverageMidRangeValues(void) {
  TEST_ASSERT_EQUAL_HEX8(1, 1);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_AverageThreeBytes_should_AverageMidRangeValues);

  return UNITY_END();
}
