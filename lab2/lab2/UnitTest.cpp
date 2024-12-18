#include "HTTP_Server.h"
#include "TrigonometryClass.h"
#include "factorial.h"
#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdio.h>
#include <memory>


std::string httpGet(const std::string& url) {
    std::string cmd = "curl -s " + url;
    std::array<char, 128> buffer{};
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

class ComputeTimeTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        int ret = system("./HTTP_Server &");
        (void)ret;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    static void TearDownTestSuite() {
    }
};

TEST_F(ComputeTimeTest, CheckComputeTimeWithinRange) {

    std::string response = httpGet("http://localhost:8081/compute");

    int elapsed_ms = std::stoi(response);


    EXPECT_GE(elapsed_ms, 0);
    EXPECT_LE(elapsed_ms, 40000);
}