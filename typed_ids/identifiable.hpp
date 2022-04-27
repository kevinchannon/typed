#pragma once

#include "id.hpp"

///////////////////////////////////////////////////////////////////////////////

namespace typed {

///////////////////////////////////////////////////////////////////////////////

template < typename Base_T, typename Id_T >
class identifiable_mixin {
  using _base_type = Base_T;

 public:
  using id_type = id< _base_type, Id_T >;

  identifiable_mixin() noexcept = delete;
  identifiable_mixin(const identifiable_mixin&) = default;
  identifiable_mixin(identifiable_mixin&&) noexcept = default;
  identifiable_mixin& operator=(const identifiable_mixin&)     = default;
  identifiable_mixin& operator=(identifiable_mixin&&) noexcept = default;
  auto operator<=>(const identifiable_mixin&) const            = default;

  constexpr explicit identifiable_mixin(id_type id) : _id{std::move(id)} {}
  constexpr explicit identifiable_mixin(typename id_type::value_type id) : _id{std::move(id)} {}

  [[nodiscard]] constexpr const id_type& id() const noexcept { return _id; }

 protected:
  ~identifiable_mixin() = default;

  id_type _id;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
