#include <chrono>
class ScopeTimer
{
public:
        ScopeTimer(std::string name) : mName(std::move(name)), mStart(std::chrono::steady_clock::now()) { }
        ScopeTimer() : mName("Timer"), mStart(std::chrono::steady_clock::now()) { }
        ~ScopeTimer()
        {
                const auto end = std::chrono::steady_clock::now();
                std::cout << mName << ": " << std::chrono::duration <double, std::milli>(end - mStart).count() << " ms\n";
        }

private:
        const std::string mName;
        const std::chrono::time_point<std::chrono::steady_clock> mStart;
};
