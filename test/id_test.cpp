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

    std::string forbidden[] = {"A0", "D1", "F1", "G1",
                               "J1", "M1", "Q1", "V1", "A1-", "1", "",
                               "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"};

    for (const auto& s : forbidden)
    {
        try
        {
            test_id = s;
        }
        catch (std::invalid_argument e)
        {
            exception_is_trown = true;
        }

        EXPECT_TRUE(exception_is_trown);
        exception_is_trown = false;
    }
}

#ifdef _perfomance_test_
#include <chrono>

TEST(IdTest, RerfTest)
{
    id test_id{"A1"};

    auto start = std::chrono::system_clock::now();
    while (test_id.get_incremented() != "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9") {}
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}
#endif

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
