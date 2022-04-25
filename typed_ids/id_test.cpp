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
struct IdTests : public testing::Test
{
 public:
   [[nodiscard]] constexpr Tested_T get_value() const {
    if constexpr (std::is_same< Tested_T, size_t >()) {
      return 10;
    }
    if constexpr (std::is_same< Tested_T, int >()) {
      return 20;
    }
    if constexpr (std::is_same< Tested_T, std::string >()) {
      return "ID: 1";
    }
  }
};

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

TYPED_TEST(IdTests, ConstructWithValue) {
  const auto id       = id_type< Dog, TypeParam >{this->get_value()};
  ASSERT_EQ(this->get_value(), id.get());
}

TYPED_TEST(IdTests, SetValue) {
  auto id = id_type< Dog, TypeParam >{};
  id.set(this->get_value());
  ASSERT_EQ(this->get_value(), id.get());
}

///////////////////////////////////////////////////////////////////////////////
