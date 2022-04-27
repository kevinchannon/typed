#pragma once

#include "index.hpp"

#include <memory>
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

  [[nodiscard]] constexpr size_type size() const noexcept { return static_cast< size_type >(_values.size()); }

  value_type* const add(value_type val) { return add(std::make_unique< value_type >(std::move(val))); }

  value_type* const add(std::unique_ptr< value_type >&& val) {
    _values.push_back(std::forward< std::unique_ptr< value_type > >(val));
    return _values.back().get();
  }

  [[nodiscard]] constexpr const value_type& get(index_type idx) const { return *_values[idx.get()]; }

 private:
  std::vector< std::unique_ptr< value_type > > _values;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
