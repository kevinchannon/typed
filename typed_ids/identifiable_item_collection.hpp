#pragma once

#include "index.hpp"

#include <vector>

///////////////////////////////////////////////////////////////////////////////

namespace typed {

///////////////////////////////////////////////////////////////////////////////

template < typename Item_T, typename Index_T = size_t >
class identifiable_item_collection {
  using _this_type = identifiable_item_collection< Item_T, Index_T >;

 public:
  using value_type = Item_T;
  using index_type = index< _this_type, Index_T >;
  using size_type  = typename index_type::value_type;

  [[nodiscard]] constexpr size_type size() const noexcept { return 0; }

  value_type* add(value_type val) {
    _values.push_back(std::move(val));
    return &_values.back();
  }

 private:
  std::vector<value_type> _values;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
