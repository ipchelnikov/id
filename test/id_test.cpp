#include "gtest/gtest.h"

#include "id.h"

TEST(IdTest, CreateIdWithoutArguments)
{
    id test_id; // A1
    EXPECT_EQ(test_id.get_incremented(), "A2");
}

TEST(IdTest, CreateIdWithAStringArgument)
{
    id test_id{"B1"};
    EXPECT_EQ(test_id.get_incremented(), "B2");
}

TEST(IdTest, AssignFormattedStringToId)
{
    id test_id;

    test_id = "C2";

    EXPECT_EQ(test_id.get_incremented(), "C3");
}

TEST(IdTest, AssignWithForbiddenSymbols)
{
    bool exception_is_trown = false;

    id test_id;

    try
    {
        test_id = "A0";
    }
    catch (std::invalid_argument e)
    {
        exception_is_trown = true;
        EXPECT_STREQ(e.what(), id::NUMBER_OUT_OF_RANGE);
    }

    EXPECT_TRUE(exception_is_trown);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
