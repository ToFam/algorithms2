#include <PriorityQueue.h>

#include <gtest/gtest.h>

TEST(pqTest, test42)
{
	PriorityQueue pq;
	ASSERT_EQ(42, pq.test());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}