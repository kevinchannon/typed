#pragma once

#include <type_traits>

///////////////////////////////////////////////////////////////////////////////

template < typename Id_T, typename Value_T = size_t >
requires std::is_integral_v< Value_T > and std::is_unsigned_v< Value_T >
class index_type {
 public:
  using value_type = Value_T;

  [[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

 private:
  value_type _value{0};
};

///////////////////////////////////////////////////////////////////////////////
