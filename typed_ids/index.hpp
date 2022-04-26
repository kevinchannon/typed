#pragma once

#include <type_traits>

///////////////////////////////////////////////////////////////////////////////

template < typename Id_T, typename Value_T = size_t >
requires std::is_integral_v< Value_T > and std::is_unsigned_v< Value_T >
class index_type {
 public:
  using value_type = Value_T;

  constexpr index_type() noexcept = default;
  constexpr explicit index_type(value_type value) noexcept : _value{std::move(value)} {}

  constexpr index_type(const index_type&) noexcept = default;
  constexpr index_type(index_type&&) noexcept      = default;

  constexpr index_type& operator=(const index_type&) noexcept = default;
  constexpr index_type& operator=(index_type&&) noexcept      = default;

  [[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

  [[nodiscard]] constexpr std::strong_ordering operator<=>(const index_type& other) const noexcept = default;

  index_type& operator+=(value_type increment) noexcept {
    _value += increment;
    return *this;
  }

  index_type& operator+=(const index_type& other) noexcept {
    return *this += other._value;
  }

  index_type& operator++() noexcept { return *this += index_type{1}; }

  index_type operator++(int) noexcept {
    auto out = *this;
    ++_value;
    return out;
  }

  index_type& operator-=(value_type decrement) noexcept {
    _value -= decrement;
    return *this;
  }

  index_type& operator-=(const index_type& other) noexcept { return *this -= other._value; }

  index_type& operator--() noexcept { return *this -= index_type{1}; }

  index_type operator--(int) noexcept {
    auto out = *this;
    --_value;
    return out;
  }

 private:
  value_type _value{0};
};

///////////////////////////////////////////////////////////////////////////////
