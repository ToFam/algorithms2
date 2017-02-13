#include <BinaryHeap.h>

#include <gtest/gtest.h>

template<typename T>
class PQTest : public ::testing::Test
{
public:

};

TYPED_TEST_CASE_P(PQTest);

TYPED_TEST_P(PQTest, testSize)
{
	PriorityQueue<int>* pq = new TypeParam();

	ASSERT_EQ(0, pq->size());

	delete pq;
}

REGISTER_TYPED_TEST_CASE_P(PQTest, testSize);

typedef ::testing::Types<BinaryHeap<int>> pqTypes;
INSTANTIATE_TYPED_TEST_CASE_P(Bla, PQTest, pqTypes);

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}