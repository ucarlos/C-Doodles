/*
 * ------------------------------------------------------------------------------
 * Created by Ulysses Carlos on 11/06/2021 at 06:13 PM
 *
 * ExampleThread.cc
 * Thread Example file created while watching this video:
 * https://youtu.be/F6Ipn7gCOsY
 * ------------------------------------------------------------------------------
 */

#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
std::mutex mutex_lock;

class ExampleFunction {
public:
    ExampleFunction() = default;
    ExampleFunction(int val) : value{val} { }
    ExampleFunction(string tex, int val) : text{tex}, value{val} {}
    ExampleFunction(string tex, int val, int sleep_dur_ms): text{tex}, value{val}, sleep_duration_ms{sleep_dur_ms} { }
    
    void operator()() {
        for (int i = value; i >= 0; i--) {
            // mutex_lock.lock();
            write_to_stdout(i);
            // mutex_lock.unlock();
            this_thread::sleep_for(std::chrono::milliseconds(sleep_duration_ms));
        }
    }

private:
    int value{0};
    string text{"Default text"};
    int sleep_duration_ms{1500};

    void write_to_stdout(int i) {
        std::lock_guard<std::mutex> lock(mutex_lock);
        cout << text << ": " << i << endl;
    }
};

int main(void) {
    ExampleFunction function1{"Thread1", 10, 1500};
    ExampleFunction function2{"Thread2", 20, 1500};

    std::thread thread1{function1};
    //this_thread::sleep_for(chrono::seconds(1));
    std::thread thread2{function2};

    thread1.join();
    thread2.join();
}
