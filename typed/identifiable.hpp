#pragma once

#include <typed/id.hpp>

#include <compare>

///////////////////////////////////////////////////////////////////////////////

namespace typed {

///////////////////////////////////////////////////////////////////////////////

template < typename Base_T, typename Id_T >
class identifiable {
  using _base_type = Base_T;

 public:
  using id_type = id< _base_type, Id_T >;

  identifiable() noexcept                                = delete;
  identifiable(const identifiable&)                = default;
  identifiable(identifiable&&) noexcept            = default;
  identifiable& operator=(const identifiable&)     = default;
  identifiable& operator=(identifiable&&) noexcept = default;
  auto operator<=>(const identifiable&) const            = default;

  constexpr explicit identifiable(id_type id) : _id{std::move(id)} {}
  constexpr explicit identifiable(typename id_type::value_type id) : _id{std::move(id)} {}

  [[nodiscard]] constexpr const id_type& id() const noexcept { return _id; }

 protected:
  ~identifiable() = default;

  id_type _id;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
