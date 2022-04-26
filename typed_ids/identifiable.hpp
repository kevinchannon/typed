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

  constexpr explicit identifiable_mixin(id_type id) : _id{std::move(id)} {}

  [[nodiscard]] constexpr const id_type& id() const noexcept { return _id; }
  void set_id(id_type id) noexcept { _id = std::move(id); }

 protected:
  ~identifiable_mixin() = default;

  id_type _id;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
