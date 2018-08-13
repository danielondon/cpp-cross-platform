#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <numeric>
#include <experimental/coroutine>
#include <future>


using namespace std;


template <typename T>
std::vector<T> range(T first, T last)
{
    std::vector<T> values;
    while (first != last)
        values.push_back(first++);
    return values;
}


template <typename T>
struct Generator
{
    T first;
    T last;
    struct iterator 
    {
        T value;
        /*using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;*/
        using pointer = T const*;
        using reference = T const&;

        iterator& operator++() 
        {
            ++value;
            return *this;
        }

        iterator operator++(int) = delete;

        bool operator==(iterator const& other) const
        {
            return value == other.value;
        }

        bool operator!=(iterator const& other) const
        {
            return !(*this == other);
        }

        reference operator*() const
        {
            return value;
        }

        pointer operator->() const
        {
            return std::addressof(value);
        }
    };

    iterator begin() { return{ first }; }
    iterator end() { return{ last }; }
};

template <typename T>
Generator<T> rangeGenerator(T first, T last)
{
    return{ first, last };
}

// A coroutine Generator
/*template <typename T>
struct GeneratorCoroutine
{
    struct promise_type { 
        //std::variant<T const*, std::exception_ptr> value;
    };

    using handle_type = std::experimental::coroutine_handle<promise_type>;

    handle_type handle{ nullptr };

    //struct iterator { ... };

    ~GeneratorCoroutine()
    {
        if (handle)
            handle.destroy();
    }

    iterator begin()
    {
        ...
            handle.resume();
        ...
    }

    iterator end()
    {
        return nullptr;
    }
};
*/


//Example 2
#include <windows.h>
using namespace std::chrono;
/*auto operator await(std::chrono::system_clock::duration duration) 
{
    class awaiter 
    {
        static void CALLBACK TimerCallback(PTP_CALLBACK_INSTANCE, void *Context, PTP_TIMER) 
        {
            std::experimental::coroutine_handle<>::from_address(Context)();
        }

        PTP_TIMER timer = nullptr;
        std::chrono::system_clock::duration duration;

    public:
        explicit awaiter(std::chrono::system_clock::duration d) : duration(d) {}
        bool await_ready() const { return duration.count() <= 0; }
        bool await_suspend(std::experimental::coroutine_handle<> resume_cb) 
        {
            int64_t relative_count = -duration.count();
            timer = CreateThreadpoolTimer(TimerCallback, resume_cb.to_address(), nullptr);
            SetThreadpoolTimer(timer, (PFILETIME)&relative_count, 0, 0);
            return timer != 0;
        }

        void await_resume() {}

        ~awaiter() 
        { 
            if (timer) 
                CloseThreadpoolTimer(timer); 
        }
    };

    return awaiter{ duration };
}*/



int main()
{
    cout << "== Co-routines =====" << endl;
    int myrange[10];

    std::iota(std::begin(myrange), std::end(myrange), 0);

    cout << "Iota and for loop: ";
    for (auto & x : myrange)
        printf("%d ", x);

    cout << endl;
    cout << "Range Function: ";
    for (int i : range(0, 10))
        printf("%d ", i);


    cout << endl;
    cout << "Range Generator: ";
    for (int i : rangeGenerator(0, 10))
        printf("%d ", i);

    cout << endl;
    cout << "Coroutine: ";
    //for (int i : GeneratorCoroutine(0, 10))
    //    printf("%d ", i);
    cout << endl;
    //////
    
  	return 0;
}