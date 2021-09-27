#include "gtest/gtest.h"

#include "id.h"

TEST(IdTest, Create_Id_Without_Arguments_Then_Increment)
{
    id test_id; // A1
    EXPECT_EQ(test_id.get_next(), "A2");
}

TEST(IdTest, Create_Id_With_An_Argument_Then_Increment)
{
    id test_id{"B1"};
    EXPECT_EQ(test_id.get_next(), "B2");
}

TEST(IdTest, Assign_To_Id_Then_Increment)
{
    id test_id;

    test_id = "C2";

    EXPECT_EQ(test_id.get_next(), "C3");
}

TEST(IdTest, Assign_Ill_Formatted_String_To_Id)
{
    bool exception_is_trown = false;

    id test_id;

    std::string forbidden[] = {
        "A0", // excluded number
        "D1", "F1", "G1", "J1", "M1", "Q1", "V1", // excluded letters
        "", "1", "A1-", "Z9-Z", // size too short
        "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9" // size too long
     };

    for (const auto& s : forbidden)
    {
        try
        {
            test_id = s;
        }
        catch (std::invalid_argument& e)
        {
            exception_is_trown = true;
        }
        catch (std::out_of_range& e)
        {
            exception_is_trown = true;
        }

        EXPECT_TRUE(exception_is_trown);
        exception_is_trown = false;
    }
}

//fdef _perfomance_test_
TEST(IdTest, RerfTest)
{
    id test_id{ "A1-A1-A1" };

    auto start = std::chrono::system_clock::now();
    std::string s;
    for (int i = 0; i < 10000000; ++i)
    {
        s = test_id.get_next();
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "ID: " << s << '\n';
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}
//#endif

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
