#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) {              //静态函数只有在当前文件可见
    static int static_ = param;     //局部静态变量不会消失，所以第二次调用不会重新创建开辟空间
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;        //这里是后++是先返回再++
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
