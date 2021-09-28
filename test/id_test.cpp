#include <fstream>
#include <thread>

#include "gtest/gtest.h"

#include "id.h"

class IdTest : public ::testing::Test {
protected:
    const int increments = 10000000;
    const std::string start_id = "Z8-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9";
    const std::string expected_id = "Z9-A1-A1-A1-A1-A1-A2-Z9-Z7-P2";
};

TEST_F(IdTest, Create_Id_Without_Arguments_Then_Increment)
{
    id test_id; // A1
    EXPECT_EQ(test_id.get_next(), "A2");
}

TEST_F(IdTest, Create_Id_With_An_Argument_Then_Increment)
{
    id test_id{"B1"};
    EXPECT_EQ(test_id.get_next(), "B2");
}

TEST_F(IdTest, Assign_To_Id_Then_Increment)
{
    id test_id;

    test_id = "C2";

    EXPECT_EQ(test_id.get_next(), "C3");
}

TEST_F(IdTest, Assign_Ill_Formatted_String_To_Id)
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

TEST_F(IdTest, Conner_Cases)
{
    id test_id{ "A1-Z9-Z9" };
    EXPECT_EQ(test_id.get_next(), "A2-A1-A1");

    test_id = "Z9-A2-Z9";
    EXPECT_EQ(test_id.get_next(), "Z9-A3-A1");

    test_id = "Z9-Z9-Z9";
    EXPECT_EQ(test_id.get_next(), "A1-A1-A1-A1");

    test_id = "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9";
    EXPECT_EQ(test_id.get_next(), "A1");

    test_id = "Z8-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9";
    EXPECT_EQ(test_id.get_next(), "Z9-A1-A1-A1-A1-A1-A1-A1-A1-A1");
}

TEST_F(IdTest, Perf_Test)
{
    id test_id{start_id};

    std::fstream fs;
    fs.open ("test_result.txt", std::fstream::out);

    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < increments; ++i)
    {
        fs << test_id.get_next() << '\n';
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    const auto end_id = test_id.get_next();

    std::cout << "Start Id:\t"      << start_id << '\n';
    std::cout << "End Id:\t\t"      << end_id << '\n';
    std::cout << "Expected Id:\t"   << expected_id << '\n';
    std::cout << "Elapsed time:\t"  << elapsed_seconds.count() << "s\n";

    fs.close();

    EXPECT_EQ(expected_id, end_id);
}

TEST_F(IdTest, Concurrent_Test)
{
    id test_id{start_id};

    const int n_threads = 8;
    std::vector<std::thread> threads;

    auto start = std::chrono::system_clock::now();
    for(int i = 0; i < n_threads; ++i)
    {
        threads.emplace_back([&test_id, &i, this]{
            std::fstream fs;
            fs.open ("test_result_" +
                    std::to_string(i)+".txt", std::fstream::out);

            for (int j = 0; j < increments/n_threads; ++j)
            {
                fs << test_id.get_next() << '\n';
            }
            fs.close();
        });
    }
    for(auto th = threads.begin(); th < threads.end(); ++th)
    {
        (*th).join();
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    const auto end_id = test_id.get_next();

    std::cout << "Start Id:\t"      << start_id << '\n';
    std::cout << "End Id:\t\t"      << end_id << '\n';
    std::cout << "Expected Id:\t"   << expected_id << '\n';
    std::cout << "Threads:\t"       << n_threads << '\n';
    std::cout << "Elapsed time:\t"  << elapsed_seconds.count() << "s\n";

    EXPECT_EQ(expected_id, end_id);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
