#pragma once

#include <iostream>
#include <chrono>
#include <sstream>

template <typename F_t>
class ttimer
{
  using clock = std::chrono::high_resolution_clock;

public:
  ttimer(F_t f) : f_(f)
  {
    start_ = clock::now();
  }

  ~ttimer()
  {
    if ( !engaged_) { return; }
    auto end = clock::now();
    f_(std::chrono::duration_cast<std::chrono::milliseconds>(end - start_)
          .count());
  }

  ttimer(ttimer&& t) : f_(std::move(t.f_)), start_(t.start_)
  {
    t.engaged_ = false;
  }

  ttimer(const ttimer&) = delete;

private:
  F_t f_;
  clock::time_point start_;
  bool engaged_ = true;
};

template <typename T>
void append_to_stream(std::ostream& s, T t)
{
  s << t;
}

template <typename T, typename... Ts>
void append_to_stream(std::ostream& s, T t, Ts... ts)
{
  s << t;
  append_to_stream(s, ts...);
}

struct timing_report
{
  template <typename... Ts>
  timing_report(Ts... ts)
  {
    std::stringstream ss;
    append_to_stream(ss, ts...);
    event = ss.str();
  }

  template <typename T>
  void operator()(T t) const
  {
    std::cout << event << " " << t << " us" << std::endl;
  }

private:
  std::string event;
};

template <typename F_t>
ttimer<F_t> make_timer(F_t f)
{
  return ttimer<F_t>(f);
}

ttimer<timing_report> make_timer(const char* s)
{
  return make_timer(timing_report(s));
}
ttimer<timing_report> make_timer(const std::string& s)
{
  return make_timer(timing_report(s));
}

template <typename... Ts>
ttimer<timing_report> make_timer(Ts... ts)
{
  return make_timer(timing_report(ts...));
}

class timer : ttimer<timing_report>
{
public:
  timer(const char* s) : ttimer(timing_report(s))
  {
  }
  timer(const std::string s) : ttimer(timing_report(s))
  {
  }
};

