#include "index.hpp"

///////////////////////////////////////////////////////////////////////////////

using IndexTypes = ::testing::Types< uint8_t, uint16_t, uint32_t, uint64_t >;

class IndexTypeNames {
 public:
  template < typename T >
  static std::string GetName(int) {
    if constexpr (std::is_same< T, uint8_t >()) {
      return "uint8_t";
    }
    if constexpr (std::is_same< T, uint16_t >()) {
      return "uint16_t";
    }
    if constexpr (std::is_same< T, uint32_t >()) {
      return "uint32_t";
    }
    if constexpr (std::is_same< T, uint64_t >()) {
      return "uint64_t";
    }
  }
};

template < typename Tested_T >
struct IndexTests : public testing::Test {
 public:
  [[nodiscard]] constexpr Tested_T get_value() const { return {10}; }
};

TYPED_TEST_CASE(IndexTests, IndexTypes, IndexTypeNames);

///////////////////////////////////////////////////////////////////////////////

namespace {
struct Cat {};
}  // namespace

///////////////////////////////////////////////////////////////////////////////

TYPED_TEST(IndexTests, DefaultConstructToZero) {
  const auto idx       = index_type< Cat, TypeParam >{};
  const auto expected = TypeParam{0};
  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, ConstructWithValue) {
  const auto idx = index_type< Cat, TypeParam >{this->get_value()};
  ASSERT_EQ(this->get_value(), idx.get());
}

TYPED_TEST(IndexTests, SetValue) {
  auto idx = index_type< Cat, TypeParam >{};
  idx.set(this->get_value());
  ASSERT_EQ(this->get_value(), idx.get());
}

///////////////////////////////////////////////////////////////////////////////
