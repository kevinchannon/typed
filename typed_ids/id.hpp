#pragma once

///////////////////////////////////////////////////////////////////////////////

namespace type {

///////////////////////////////////////////////////////////////////////////////

template < typename Id_T, typename Value_T = size_t >
class id_type {
 public:
  using value_type = Value_T;

  constexpr id_type() noexcept = default;
  constexpr explicit id_type(value_type value) noexcept : _value{std::move(value)} {}

  constexpr id_type(const id_type&) noexcept = default;
  constexpr id_type(id_type&&) noexcept      = default;

  constexpr id_type& operator=(const id_type&) noexcept = default;
  constexpr id_type& operator=(id_type&&) noexcept = default;

  [[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

  [[nodiscard]] constexpr std::strong_ordering operator<=>(const id_type& other) const = default;

 private:
  value_type _value;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace type

///////////////////////////////////////////////////////////////////////////////

