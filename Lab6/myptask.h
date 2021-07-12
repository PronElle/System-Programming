//
// Created by elle on 05/06/21.
//

#ifndef LAB6_MYPTASK_H
#define LAB6_MYPTASK_H

#include <tuple>
#include <future>

template <typename F, typename  ...Args>
class MyPackagedTask {
  F& _f;
  std::tuple<Args...> _args;
  using R = decltype(apply(_f, _args));
  std::promise<R> p;

public:
    explicit MyPackagedTask(F&& fn, Args&& ...args): _f(fn), _args(std::forward<Args>(args)...){}

    MyPackagedTask & operator = (MyPackagedTask && other) noexcept {
        swap(*this, other);
        return *this;
    }

    void operator() (){
        p.set_value(apply(_f, _args));
    }

    std::future<R> get_future(){
        return p.get_future();
    }
};




#endif //LAB6_MYPTASK_H
