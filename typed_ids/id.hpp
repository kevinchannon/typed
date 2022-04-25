#pragma once

///////////////////////////////////////////////////////////////////////////////

template < typename Id_T, typename Value_T = size_t >
class id_type {
 public:
  using value_type = Value_T;

  [[nodiscard]] constexpr const value_type& get() const noexcept { return _value; }

  private:
  value_type _value;
};

///////////////////////////////////////////////////////////////////////////////
