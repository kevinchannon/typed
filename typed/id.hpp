#pragma once

#include <compare>

///////////////////////////////////////////////////////////////////////////////

namespace typed {

///////////////////////////////////////////////////////////////////////////////

template < typename Id_T, typename Value_T = size_t >
class id {
 public:
  using value_type = Value_T;

  constexpr id() noexcept = default;
  constexpr explicit id(value_type value) noexcept : _value{std::move(value)} {}

  constexpr id(const id&) noexcept = default;
  constexpr id(id&&) noexcept      = default;

  constexpr id& operator=(const id&) noexcept = default;
  constexpr id& operator=(id&&) noexcept = default;

  [[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

  [[nodiscard]] auto operator<=>(const id<Id_T, Value_T>& other) const = default;

 private:
  value_type _value;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace type

///////////////////////////////////////////////////////////////////////////////

