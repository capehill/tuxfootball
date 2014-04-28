#include <gtest/gtest.h>

#include "../src/point3d.h"

TEST(Point3DTest, testCopyConstructor) {
	Point3D p1(1,2,3);
	Point3D p2 = p1;
	ASSERT_FLOAT_EQ(1, p2.x());
    ASSERT_FLOAT_EQ(2, p2.y());
    ASSERT_FLOAT_EQ(3, p2.z());
}
