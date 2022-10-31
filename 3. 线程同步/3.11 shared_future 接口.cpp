template <class _Ty>
class shared_future : public _State_manager<_Ty> 
{
public:
    shared_future() noexcept {}
    shared_future(const shared_future& _Other);
    shared_future(future<_Ty>&& _Other);
    shared_future(shared_future&& _Other);

    shared_future& operator=(const shared_future& _Right);
    shared_future& operator=(shared_future&& _Right);

    ~shared_future();

    const _Ty& get() const 
    {
        return this->_Get_value();
    }
};