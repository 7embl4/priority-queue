#include "priority_queue.hpp"
#include <gtest/gtest.h>


TEST(CommonFunctionality, CheckForTheLowestAfterPush) {
	pq::priority_queue<int> pq_;
	pq_.push(1408, 3);
	EXPECT_EQ(pq_.peek().value, 1408);

	pq_.push(42, 1);
	EXPECT_EQ(pq_.peek().value, 42);

	pq_.push(13, 2);
	EXPECT_EQ(pq_.peek().value, 42);
}

TEST(CommonFunctionality, PushAfterPop) {
	pq::priority_queue<int> pq_;
	pq_.push(1408, 3);
	pq_.push(42, 1);
	pq_.push(13, 2);
	EXPECT_EQ(pq_.pop(), 42);

	pq_.push(2024, 1);
	EXPECT_EQ(pq_.peek().value, 2024);
}
               
TEST(CommonFunctionality, DifferentElementsWithSamePriority) {
	pq::priority_queue<int> pq_;
	pq_.push(1408, 3);
	pq_.push(42, 1);
	pq_.push(13, 1);
	EXPECT_EQ(pq_.pop(), 42);
	EXPECT_EQ(pq_.peek().value, 13);
}


TEST(Pop, TheLowestHasRightChild) {
	pq::priority_queue<std::string> pq_;
	pq_.push("Triss", 3);
	pq_.push("Geralt", 4);
	pq_.push("Ciri", 1);
	pq_.push("Yennefer", 2);

	EXPECT_EQ(pq_.pop(), "Ciri");
	EXPECT_EQ(pq_.peek().value, "Yennefer");
	EXPECT_EQ(pq_.getCount(), 3);
}

TEST(Pop, TheLowestDoesntHaveRightChild) {
	pq::priority_queue<std::string> pq_;
	pq_.push("Triss", 3);
	pq_.push("Geralt", 4);
	pq_.push("Yennefer", 2);
	pq_.push("Ciri", 1);

	EXPECT_EQ(pq_.pop(), "Ciri");
	EXPECT_EQ(pq_.peek().value, "Yennefer");
	EXPECT_EQ(pq_.getCount(), 3);
}

TEST(Pop, PopTheHead) {
	pq::priority_queue<std::string> pq_;
	pq_.push("Yennefer", 2);
	pq_.push("Triss", 3);
	pq_.push("Geralt", 4);

	EXPECT_EQ(pq_.pop(), "Yennefer");
	EXPECT_EQ(pq_.peek().value, "Triss");
	EXPECT_EQ(pq_.getCount(), 2);
}

int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
