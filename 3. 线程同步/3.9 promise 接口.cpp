template <class _Ty>
class promise 
{ // class that defines an asynchronous provider that holds a value
// 定义一个异步方式提供值的类
public:
    promise() : _MyPromise(new _Associated_state<_Ty>) {}

    template <class _Alloc>
    promise(allocator_arg_t, const _Alloc& _Al) : _MyPromise(_Make_associated_state<_Ty>(_Al)) {}

    promise(promise&& _Other);

    promise& operator=(promise&& _Other);

    ~promise();


    future<_Ty> get_future() {
        return future<_Ty>(_MyPromise._Get_state_for_future(), _Nil{});
    }

    void set_value(const _Ty& _Val) {
        _MyPromise._Get_state_for_set()._Set_value(_Val, false);
    }

    void set_value(_Ty&& _Val) {
        _MyPromise._Get_state_for_set()._Set_value(_STD forward<_Ty>(_Val), false);
    }

private:
    _Promise<_Ty> _MyPromise;
};