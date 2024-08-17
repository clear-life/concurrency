template <class T>
struct atomic : _Choose_atomic_base_t<T> 
{
private:
    using Base = _Choose_atomic_base_t<T>;

public:
    using Base::Base;

    constexpr atomic() noexcept(is_nothrow_default_constructible_v<T>) : Base() {}

    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;


    bool is_lock_free() const 
    {
        return static_cast<const volatile atomic*>(this)->is_lock_free();
    }

    T operator=(const T val) 
    {
        this->store(val);
        return val;
    }

    using Base::store;
    void store(const T val) volatile 
    {
        const_cast<atomic*>(this)->Base::store(val);
    }

    using Base::load;
    T load() const volatile 
    {
        return const_cast<const atomic*>(this)->Base::load();
    }

    using Base::exchange;
    T exchange(const T val) volatile 
    {
        return const_cast<atomic*>(this)->Base::exchange(val);
    }

    using Base::compare_exchange_strong;
    bool compare_exchange_strong(T& _Expected, const T _Desired) volatile 
    {
        return const_cast<atomic*>(this)->Base::compare_exchange_strong(_Expected, _Desired);
    }


    bool compare_exchange_weak(T& _Expected, const T _Desired) 
    {
        return this->compare_exchange_strong(_Expected, _Desired);
    }

    operator T() const 
    {
        return this->load();
    }
};