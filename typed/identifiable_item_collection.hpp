#pragma once

#include <typed/index.hpp>

#include <map>
#include <memory>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

namespace typed {

///////////////////////////////////////////////////////////////////////////////

template < typename Item_T, typename Index_T = size_t >
class identifiable_item_collection {
  using _this_type      = identifiable_item_collection< Item_T, Index_T >;
  using _ptr_type       = std::unique_ptr< Item_T >;
  using _container_type = std::vector< _ptr_type >;

 public:
  using value_type = Item_T;
  using index_type = index< _this_type, Index_T >;
  using size_type  = index_type;
  using id_type    = typename value_type::id_type;

  [[nodiscard]] constexpr size_type size() const noexcept {
    return size_type{static_cast< typename size_type::value_type >(_values.size())};
  }

  [[nodiscard]] constexpr size_type count() const noexcept { return size(); }

  std::pair< value_type* const, bool > add(_ptr_type&& val) {
    auto out = find(val->id());
    if (nullptr != out) {
      return {out, false};
    }

    return {_unchecked_add(std::move(val)), true};
  }

  std::pair< value_type* const, bool > add(value_type val) { return add(std::make_unique< value_type >(std::move(val))); }

  template < typename... Arg_Ts >
  std::pair< value_type* const, bool > emplace(Arg_Ts... args) {
    return add(std::make_unique< value_type >(std::forward< Arg_Ts >(args)...));
  }

  [[nodiscard]] constexpr const value_type& at(const index_type& idx) const { return *_values[idx.get()]; }
  [[nodiscard]] value_type& at(const index_type& idx) { return *_values[idx.get()]; }

  [[nodiscard]] constexpr const value_type* const find(const id_type& id) const {
    const auto idx = _find_index(id);
    return idx != _values.size() ? _values[idx].get() : nullptr;
  }

  [[nodiscard]] constexpr value_type* const find(const id_type& id) {
    return const_cast< value_type* >(const_cast< const _this_type* >(this)->find(id));
  }

  _ptr_type remove(const id_type& id) {
    auto idx = _find_index(id);
    if (_values.size() == idx) {
      return nullptr;
    }

    auto out = std::move(_values[idx]);
    _values.erase(std::next(_values.begin(), idx));

    return out;
  }

 private:
  typename _container_type::size_type _find_index(const id_type& id) const {
    return std::distance(_values.begin(),
                         std::find_if(_values.begin(), _values.end(), [&id](auto&& val) { return val->id() == id; }));
  }

  value_type* _unchecked_add(_ptr_type&& val) {
    _values.push_back(std::forward< _ptr_type >(val));
    return _values.back().get();
  }

  _container_type _values;
};

///////////////////////////////////////////////////////////////////////////////

}  // namespace typed

///////////////////////////////////////////////////////////////////////////////
