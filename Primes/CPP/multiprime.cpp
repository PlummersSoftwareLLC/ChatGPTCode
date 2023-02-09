#include <iostream>
#include <chrono>
#include <bitset>
#include <thread>
#include <vector>
#include <atomic>

constexpr int N = 1000000;
constexpr int NS_PER_SEC = 1000000000;

class PrimeSieve
{
public:
    PrimeSieve(int size) : size(size), candidates(size + 1, true)
    {
        // Mark 0 and 1 as not prime
        candidates[0] = candidates[1] = false;

        // Optimize the sieve by only marking odd numbers as composite
        for (int i = 3; i * i <= size; i += 2)
        {
            if (candidates[i])
            {
                for (int j = i * i; j <= size; j += 2 * i)
                {
                    candidates[j] = false;
                }
            }
        }
    }

    int countPrimes() const
    {
        int count = 1;
        for (int i = 3; i <= size; i += 2)
        {
            if (candidates[i])
                count++;
        }
        return count;
    }

private:
    int size;
    std::vector<bool> candidates;
};

std::atomic<bool> stopSieving(false);
std::atomic<int> localCount = 0;

void runSieve(int& count, std::chrono::duration<double>& totalTime)
{
    
    std::chrono::duration<double> localTime;
    while (!stopSieving)
    {
        auto start = std::chrono::high_resolution_clock::now();
        PrimeSieve sieve(N);
        localCount++;
        auto end = std::chrono::high_resolution_clock::now();
        localTime += end - start;
    }
    count = localCount;
    totalTime = localTime;
}

int main()
{
    int count = 0;
    std::chrono::duration<double> totalTime;
    auto start = std::chrono::high_resolution_clock::now();

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++)
    {
        threads.emplace_back(runSieve, std::ref(count), std::ref(totalTime));
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    stopSieving = true;

    for (auto& t : threads)
    {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsedTime = end - start;

    PrimeSieve sieve(N);
    int numPrimes = sieve.countPrimes();

    std::cout << "Number of primes found in a single sieve: " << numPrimes << std::endl;
    std::cout << "Number of sieves completed: " << count << std::endl;
    std::cout << "Average time per sieve: " << totalTime.count() / NS_PER_SEC / count << " seconds" << std::endl;
}

