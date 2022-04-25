#include "id.hpp"

///////////////////////////////////////////////////////////////////////////////

using IdTypes = ::testing::Types< size_t, int, std::string >;

class IdTypeNames {
 public:
  template < typename T >
  static std::string GetName(int) {
    if constexpr (std::is_same< T, size_t >()) {
      return "size_t";
    }
    if constexpr (std::is_same< T, int >()) {
      return "int";
    }
    if constexpr (std::is_same< T, std::string >()) {
      return "string";
    }
  }
};

template<typename Tested_T>
struct IdTests : public testing::Test {};

TYPED_TEST_CASE(IdTests, IdTypes, IdTypeNames);

///////////////////////////////////////////////////////////////////////////////

namespace {
struct Dog {};
}  // namespace

///////////////////////////////////////////////////////////////////////////////

TYPED_TEST(IdTests, DefaultConstructToDefaultValue) {
  const auto id = id_type<Dog, TypeParam >{};
  const auto expected = TypeParam{};
  ASSERT_EQ(expected, id.get());
}

///////////////////////////////////////////////////////////////////////////////
