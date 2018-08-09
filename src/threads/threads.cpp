#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

using namespace std;

std::atomic<int> global_counter(0);

void increase_global(int n) { for (int i = 0; i<n; ++i) ++global_counter; }

static void my_wait(int seconds)
{
    //cout << "Waiting for " << seconds << " seconds..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
    //cout << "End of wait" << endl;
}

void accumulate(std::vector<int>::iterator first,
    std::vector<int>::iterator last,
    std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    my_wait(4); 
    accumulate_promise.set_value(sum);  // Notify future
    my_wait(4);
}

void do_work(std::promise<void> barrier)
{
    my_wait(1);
    barrier.set_value();
    my_wait(1);
}

int main()
{
    cout << "--- THREADS ---" << endl;
    std::vector<std::thread> threads;

    std::cout << "increase global counter with 10 threads...\n";
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(increase_global, 1000));

    std::cout << "synchronizing all threads...\n";
    for (auto& th : threads) th.join();

    std::cout << "global_counter: " << global_counter << '\n';

    cout << "--- PROMISES AND FUTURES ---" << endl;

    // Demonstrate using promise<void> to signal state between threads.
    cout << "  -----  " << endl;
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();

    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();

    // Demonstrate using promise<int> to transmit a result between threads.
    cout << "  -----  " << endl;
    cout << "Creating vector" << endl;
    std::vector<int> numbers (100000000, 5);
    cout << "Vector created" << endl;
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    
    cout << " Creating Thread" << endl;
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
    cout << " Waiting" << endl;
    accumulate_future.wait();  // wait for result
    
    std::cout << "result=" << accumulate_future.get() << '\n';
    cout << " joining " << endl;
    work_thread.join();  // wait for thread completion
    cout << " joined " << endl;
    return 0;    
}
