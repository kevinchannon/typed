#include <typed/index.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace {

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
struct IndexTests : public testing::Test {};

TYPED_TEST_CASE(IndexTests, IndexTypes, IndexTypeNames);

///////////////////////////////////////////////////////////////////////////////

namespace {
  struct Cat {};
}  // namespace

///////////////////////////////////////////////////////////////////////////////

TYPED_TEST(IndexTests, DefaultConstructToZero) {
  const auto idx      = typed::index< Cat, TypeParam >{};
  const auto expected = TypeParam{0};
  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, ConstructWithValue) {
  constexpr auto expected = TypeParam{10};
  const auto idx          = typed::index< Cat, TypeParam >{expected};
  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, AssignValue) {
  auto idx                = typed::index< Cat, TypeParam >{};
  constexpr auto expected = TypeParam{5};
  idx                     = typed::index< Cat, TypeParam >{expected};

  ASSERT_EQ(expected, idx.get());
}

TYPED_TEST(IndexTests, CompareValues) {
  const auto idx_0 = typed::index< Cat, TypeParam >{};
  const auto idx_1 = typed::index< Cat, TypeParam >{10};
  const auto idx_2 = typed::index< Cat, TypeParam >{10};

  EXPECT_NE(idx_0, idx_1);
  EXPECT_EQ(idx_1, idx_2);
  EXPECT_GT(idx_1, idx_0);
  EXPECT_LT(idx_0, idx_1);
}

TYPED_TEST(IndexTests, PreIncrement) {
  auto idx = typed::index< Cat, TypeParam >{};
  ASSERT_EQ(1, (++idx).get());
  ASSERT_EQ(1, idx.get());
}

TYPED_TEST(IndexTests, PostIncrement) {
  constexpr auto expected = TypeParam{10};
  auto idx                = typed::index< Cat, TypeParam >{expected};
  const auto val          = idx++;
  ASSERT_EQ(expected, val.get());
  ASSERT_EQ(1 + expected, idx.get());
}

TYPED_TEST(IndexTests, IncrementAssignment) {
  constexpr auto n         = TypeParam{10};
  auto idx                 = typed::index< Cat, TypeParam >{n};
  constexpr auto increment = typed::index< Cat, TypeParam >{5};
  ASSERT_EQ(n + increment.get(), (idx += increment).get());
  ASSERT_EQ(n + increment.get(), idx.get());
}

TYPED_TEST(IndexTests, IncrementAssignmentWithValueType) {
  constexpr auto n         = TypeParam{10};
  auto idx                 = typed::index< Cat, TypeParam >{n};
  constexpr auto increment = TypeParam{5};
  ASSERT_EQ(n + increment, (idx += increment).get());
  ASSERT_EQ(n + increment, idx.get());
}

TYPED_TEST(IndexTests, PreDecrement) {
  auto idx = typed::index< Cat, TypeParam >{2};
  ASSERT_EQ(1, (--idx).get());
  ASSERT_EQ(1, idx.get());
}

TYPED_TEST(IndexTests, PostDecrement) {
  constexpr auto expected = TypeParam{10};
  auto idx                = typed::index< Cat, TypeParam >{expected};
  const auto val          = idx--;
  ASSERT_EQ(expected, val.get());
  ASSERT_EQ(expected - 1, idx.get());
}

TYPED_TEST(IndexTests, DecrementAssignment) {
  constexpr auto n         = TypeParam{10};
  auto idx                 = typed::index< Cat, TypeParam >{n};
  constexpr auto decrement = typed::index< Cat, TypeParam >{5};
  ASSERT_EQ(n - decrement.get(), (idx -= decrement).get());
  ASSERT_EQ(n - decrement.get(), idx.get());
}

TYPED_TEST(IndexTests, DecrementAssignmentWithValueType) {
  constexpr auto n         = TypeParam{10};
  auto idx                 = typed::index< Cat, TypeParam >{n};
  constexpr auto decrement = TypeParam{5};
  ASSERT_EQ(n - decrement, (idx -= decrement).get());
  ASSERT_EQ(n - decrement, idx.get());
}

TYPED_TEST(IndexTests, RightAddValueType) {
  constexpr auto initial = TypeParam{10};
  constexpr auto offset  = TypeParam{5};
  const auto idx         = typed::index< Cat, TypeParam >{initial} + offset;

  ASSERT_EQ(initial + offset, idx.get());
}

TYPED_TEST(IndexTests, Offset) {
  constexpr auto initial = TypeParam{10};
  constexpr auto offset  = TypeParam{5};
  const auto idx         = typed::index< Cat, TypeParam >{initial} + typed::index< Cat, TypeParam >{offset};

  ASSERT_EQ(initial + offset, idx.get());
}

TYPED_TEST(IndexTests, RightSubtractValueType) {
  constexpr auto initial = TypeParam{10};
  constexpr auto offset  = TypeParam{5};
  const auto idx         = typed::index< Cat, TypeParam >{initial} - offset;

  ASSERT_EQ(initial - offset, idx.get());
}

TYPED_TEST(IndexTests, Difference) {
  constexpr auto initial = TypeParam{10};
  constexpr auto offset  = TypeParam{5};
  const auto idx         = typed::index< Cat, TypeParam >{initial} - typed::index< Cat, TypeParam >{offset};

  ASSERT_EQ(initial - offset, idx.get());
}

///////////////////////////////////////////////////////////////////////////////

}  // namespace

///////////////////////////////////////////////////////////////////////////////
