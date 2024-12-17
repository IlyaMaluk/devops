#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdio.h>
#include <memory>

// Функция для выполнения HTTP GET запроса (используем curl через popen для простоты)
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
        // Запускаем сервер в фоне (предполагается, что серверный бинарник называется server_app)
        // Если ваш сервер запускается иначе, измените команду соответственно.
        // Можно использовать & для запуска в фоне.
        int ret = system("./server_app &");
        (void)ret; // избегаем предупреждения о неиспользуемой переменной

        // Ждем пару секунд, чтобы сервер успел стартовать
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    static void TearDownTestSuite() {
        // Если нужно убить сервер, сделайте это тут.
        // Например, если известен его pid или предусмотрен способ graceful shutdown.
        // Здесь пропустим, предполагается, что сервер сам завершится или вы сделаете это вручную.
    }
};

TEST_F(ComputeTimeTest, CheckComputeTimeWithinRange) {
    // Отправляем запрос к серверу
    std::string response = httpGet("http://localhost:8081/compute");

    // Ответ должен быть числом миллисекунд
    int elapsed_ms = std::stoi(response);

    // Проверяем что время в диапазоне от 5 до 20 секунд
    EXPECT_GE(elapsed_ms, 5000);
    EXPECT_LE(elapsed_ms, 20000);
}
