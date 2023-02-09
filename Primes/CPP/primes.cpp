#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

const int N = 1000000;
std::vector<int> primes;
std::mutex primes_mutex;

void find_primes(int start, int end) {
    std::vector<bool> is_prime(end - start + 1, true);
    for (int i = 0; i < primes.size(); ++i) {
        int prime = primes[i];
        int first = std::max(start, (start + prime - 1) / prime * prime);
        for (int j = first; j <= end; j += prime) {
            is_prime[j - start] = false;
        }
    }
    std::lock_guard<std::mutex> lock(primes_mutex);
    for (int i = start; i <= end; ++i) {
        if (is_prime[i - start]) {
            primes.push_back(i);
        }
    }
}

int main() {
    std::vector<std::thread> threads;
    int n_threads = std::thread::hardware_concurrency();
    int chunk_size = N / n_threads;
    for (int i = 2; i < N; i += chunk_size) {
        threads.push_back(std::thread(find_primes, i, std::min(i + chunk_size - 1, N - 1)));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    std::cout << "Found " << primes.size() << " primes." << std::endl;
    return 0;
}
