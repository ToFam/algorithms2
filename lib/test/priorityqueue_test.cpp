#include <BinaryHeap.h>
#include <PairingHeap.h>

#include <gtest/gtest.h>

template<typename T>
class PQTest : public ::testing::Test
{
public:
    PQTest()
    {
        pq = new T();
    }

    ~PQTest()
    {
        delete pq;
    }

protected:
    PriorityQueue<int>* pq;
};

TYPED_TEST_CASE_P(PQTest);

TYPED_TEST_P(PQTest, testEmpty)
{
    ASSERT_EQ(0, this->pq->size());
    ASSERT_EQ(-1, this->pq->min().key);
}


TYPED_TEST_P(PQTest, testAdd)
{
    this->pq->insert({0, 0});

    ASSERT_EQ(1, this->pq->size());

    this->pq->insert({1, 1});
    this->pq->insert({2, 2});

    ASSERT_EQ(3, this->pq->size());

    for (int i = 3; i < 100; i++)
    {
        this->pq->insert({i, i});
    }

    ASSERT_EQ(100, this->pq->size());
}

TYPED_TEST_P(PQTest, testMin)
{
    this->pq->insert({5, 5});

    ASSERT_EQ(5, this->pq->min().value);

    this->pq->insert({6, 6});

    ASSERT_EQ(5, this->pq->min().value);

    this->pq->insert({7, 4});

    ASSERT_EQ(7, this->pq->min().value);

    this->pq->insert({8, 3});
    this->pq->insert({9, 2});

    ASSERT_EQ(9, this->pq->min().value);
}

TYPED_TEST_P(PQTest, testDel)
{
    this->pq->insert({0,0});
    this->pq->deleteMin();

    ASSERT_EQ(0, this->pq->size());

    PQElement<int> in{0, 0};
    this->pq->insert(in);
    PQElement<int> out = this->pq->deleteMin();

    ASSERT_EQ(in, out);

    PQElement<int> one{1,1};
    PQElement<int> two{2,2};
    this->pq->insert(two);
    this->pq->insert(one);
    ASSERT_EQ(one, this->pq->deleteMin());
    ASSERT_EQ(1, this->pq->size());
    ASSERT_EQ(two, this->pq->deleteMin());

    for (int i = 0; i < 6; i++)
    {
        this->pq->insert({i, i});
    }
    ASSERT_EQ(PQElement<int>(0,0), this->pq->deleteMin());
    ASSERT_EQ(PQElement<int>(1,1), this->pq->deleteMin());
    ASSERT_EQ(PQElement<int>(2,2), this->pq->deleteMin());
    ASSERT_EQ(PQElement<int>(3,3), this->pq->deleteMin());
    ASSERT_EQ(PQElement<int>(4,4), this->pq->deleteMin());
    ASSERT_EQ(PQElement<int>(5,5), this->pq->deleteMin());
    ASSERT_EQ(0, this->pq->size());
}

REGISTER_TYPED_TEST_CASE_P(PQTest, testEmpty, testAdd, testMin, testDel);

typedef ::testing::Types<BinaryHeap<int>, PairingHeap<int>> pqTypes;
INSTANTIATE_TYPED_TEST_CASE_P(Bla, PQTest, pqTypes);

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
