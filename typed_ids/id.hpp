#pragma once

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

  [[nodiscard]] constexpr std::strong_ordering operator<=>(const id& other) const = default;

 private:
  value_type _value;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace type

///////////////////////////////////////////////////////////////////////////////

