# Generic C++ Benchmark

## Usage:
```cpp
const int n = 1000000;
int arr[n];

void f(int n, int * arr)
{
    for(int i = 1; i <= n; i++) arr[i] = arr[i-1]*51 + i*23;
}

int main()
{
    std::cout << benchmark(1e3, 100, f, n, arr) << '\n';
    // runs the function 100 times and returns the total time in 1/1e3 seconds.
    // Do Not Change the order of arguments.
    // Pass a void function.
}
```

## Main Function
```cpp
template <class... T>
extern intmax_t benchmark(const intmax_t divide_seconds, intmax_t no_of_iterations, void (*fptr)(T...), T... params)
{
    if((divide_seconds > 1e9) || (divide_seconds <= 0)) throw std::runtime_error("Invalid Value for divide_seconds");

    using namespace std::chrono;

    steady_clock::time_point t1 = steady_clock::now();
    // steady_clock is used since,
    // The time points of this clock cannot decrease as physical time moves forward and the time between ticks of this clock is constant.
    // And high_resolution_clock is an alias for steady_clock/system_clock.

    while (no_of_iterations--) //The Overhead involved with the internal iteration is in the order of nanoseconds and can be safely ignored.
        (*fptr)(params...);

    steady_clock::time_point t2 = steady_clock::now();

    duration ts = duration_cast<std::chrono::duration<intmax_t, std::nano>>(t2 - t1);
    return ts.count() / (1e9/divide_seconds);
}
```
