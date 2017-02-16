#include <PairingHeap.h>

#include <gtest/gtest.h>

template<typename T>
class APQTest : public ::testing::Test
{
public:
    APQTest()
    {
        pq = new T();
    }

    ~APQTest()
    {
        delete pq;
    }

protected:
    AdressablePQ<int>* pq;
};

TYPED_TEST_CASE_P(APQTest);

TYPED_TEST_P(APQTest, testRemove)
{
    ASSERT_EQ(0, this->pq->size());

    PQElement<int> data[20];
    for (int i = 0; i < 20; i++)
        data[i] = PQElement<int>(i, i);

    this->pq->insert(data[0]);

    ASSERT_EQ(data[0], this->pq->remove(0));
    ASSERT_EQ(0, this->pq->size());

    this->pq->insert(data[1]);
    ASSERT_EQ(-1, this->pq->remove(0).key);
    ASSERT_EQ(data[1], this->pq->remove(1));
    ASSERT_EQ(0, this->pq->size());

    for (int i = 0; i < 20; i++)
        this->pq->insert(data[i]);

    this->pq->deleteMin();

    ASSERT_EQ(data[9], this->pq->remove(9));
    ASSERT_EQ(-1, this->pq->remove(9).key);
}

TYPED_TEST_P(APQTest, testMerge)
{
    AdressablePQ<int>* pq2 = new TypeParam();

    this->pq->merge(pq2);

    ASSERT_EQ(0, this->pq->size());
    ASSERT_EQ(0, pq2->size());

    PQElement<int> data[20];
    for (int i = 0; i < 20; i++)
    {
        data[i] = PQElement<int>(i, i);
        pq2->insert(data[i]);
    }

    this->pq->merge(pq2);

    ASSERT_EQ(20, this->pq->size());
    ASSERT_EQ(0, pq2->size());
}

TYPED_TEST_P(APQTest, testDecrease)
{
    PQElement<int> data[20];
    for (int i = 0; i < 20; i++)
    {
        data[i] = PQElement<int>(i, i);
        this->pq->insert(data[i]);
    }

    this->pq->decreaseKey(19, 2);

    ASSERT_EQ(2, this->pq->remove(19).key);
}

REGISTER_TYPED_TEST_CASE_P(APQTest, testRemove, testMerge, testDecrease);

typedef ::testing::Types<PairingHeap<int>> pqTypes;
INSTANTIATE_TYPED_TEST_CASE_P(Bla, APQTest, pqTypes);

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
