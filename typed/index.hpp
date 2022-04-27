#pragma once

#include <type_traits>
#include <compare>

///////////////////////////////////////////////////////////////////////////////

namespace typed {

///////////////////////////////////////////////////////////////////////////////

template < typename Id_T, typename Value_T = size_t >
requires std::is_integral_v< Value_T > and std::is_unsigned_v< Value_T >
class index {
 public:
  using value_type = Value_T;

  constexpr index() noexcept = default;
  constexpr explicit index(value_type value) noexcept : _value{std::move(value)} {}

  constexpr index(const index&) noexcept = default;
  constexpr index(index&&) noexcept      = default;

  constexpr index& operator=(const index&) noexcept = default;
  constexpr index& operator=(index&&) noexcept = default;

  [[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

  [[nodiscard]] auto operator<=>(const index& other) const = default;

  constexpr index& operator+=(value_type increment) noexcept {
    _value += increment;
    return *this;
  }

  constexpr index& operator+=(const index& other) noexcept { return *this += other._value; }

  constexpr index& operator++() noexcept { return *this += index{1}; }

  constexpr index operator++(int) noexcept {
    auto out = *this;
    ++_value;
    return out;
  }

  constexpr index& operator-=(value_type decrement) noexcept {
    _value -= decrement;
    return *this;
  }

  constexpr index& operator-=(const index& other) noexcept { return *this -= other._value; }

  constexpr index& operator--() noexcept { return *this -= index{1}; }

  constexpr index operator--(int) noexcept {
    auto out = *this;
    --_value;
    return out;
  }

  [[nodiscard]] constexpr index operator+(value_type value) const noexcept {
    auto out = *this;
    out += value;
    return out;
  }

  [[nodiscard]] constexpr index operator+(index out) const noexcept {
    out += _value;
    return out;
  }

  [[nodiscard]] constexpr index operator-(value_type value) const noexcept {
    auto out = *this;
    out -= value;
    return out;
  }

  [[nodiscard]] constexpr index operator-(index other) const noexcept {
    auto out = *this;
    out -= other._value;
    return out;
  }

 private:
  value_type _value{0};
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
