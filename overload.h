template <typename F>
struct forwarder_t : private F
{
  using F::operator();

  forwarder_t(F f) : F(std::move(f))
  {
  }
};

template <typename F>
struct forwarder_t<F&> : private F
{
  using F::operator();

  forwarder_t(F f) : F(std::move(f))
  {
  }
};

template <typename T, typename... Ts>
struct forwarder_t<T (&)(Ts...)>
{
  using F = T (&)(Ts...);
  F f_;

  T operator()(Ts... ts) const
  {
    return f_(std::forward<Ts>(ts)...);
  }

  forwarder_t(F f) : f_(f)
  {
  }
};

template <typename T, typename... Ts>
struct overload_t : private forwarder_t<T>, private overload_t<Ts...>
{
  using forwarder_t<T>::operator();
  using overload_t<Ts...>::operator();

  overload_t(T t, Ts... ts)
      : forwarder_t<T>(std::move(t)), overload_t<Ts...>(std::forward<Ts>(ts)...)
  {
  }
};

template <typename T>
struct overload_t<T> : private forwarder_t<T>
{
  using forwarder_t<T>::operator();

  overload_t(T t) : forwarder_t<T>(std::move(t))
  {
  }
};

template <typename... Ts>
auto overload(Ts&&... ts)
{
  return overload_t<Ts...>(std::forward<Ts>(ts)...);
}

