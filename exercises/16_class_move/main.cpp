#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]{0,1}), cached(2) {}

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci&& other) noexcept    //移动构造器，专门用来抢资源的
    {
        cached=other.cached;
        cache=other.cache;
        other.cached=0;
        other.cache=nullptr;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci&& p) noexcept   //如果遇到右值也是抢
    {
        if(this==&p)
        {
            return *this;
        }
        delete[] cache;
        cached=p.cached;
        cache=p.cache;
        p.cached=0;
        p.cache=nullptr;
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci()
    {
        delete[] cache;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached<=i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);       //注意std::move方法，这个方法返回右值，这个表达式是初始化新对象，所以要调用构造函数，因为其还是右值所以调用移动构造函数
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);        //这里是对新对象进行赋值，所以调用移动赋值函数
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
