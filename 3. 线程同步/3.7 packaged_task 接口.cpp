template <class _Ret, class... _Args>
class packaged_task<_Ret(_Args...)> {
    // class that defines an asynchronous provider that returns the result of a call to a function object
    // 提供异步函数调用返回值的类
public:
    packaged_task() : _MyPromise(0) {}

    template <class _Fty2, enable_if_t<!is_same_v<_Remove_cvref_t<_Fty2>, packaged_task>, int> = 0>
    explicit packaged_task(_Fty2&& _Fnarg) : _MyPromise(new _MyStateType(_STD forward<_Fty2>(_Fnarg))) {}

    ~packaged_task();

    future<_Ret> get_future();
    void operator()(_Args... _Args);
};