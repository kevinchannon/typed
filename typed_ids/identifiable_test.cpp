
#include <typed/identifiable.hpp>
#include <typed/io/idio.hpp>

///////////////////////////////////////////////////////////////////////////////

namespace {

///////////////////////////////////////////////////////////////////////////////

/// <summary>
/// A sheep is identifiable and we use the identifiable_mixin to provide our id-related data and methods.
/// </summary>
struct Sheep : public typed::identifiable_mixin< Sheep, size_t > {
  constexpr Sheep(id_type id) : typed::identifiable_mixin< Sheep, size_t >{id} {}
  constexpr Sheep(size_t id) : typed::identifiable_mixin< Sheep, size_t >{id} {}
};

///////////////////////////////////////////////////////////////////////////////

TEST(IdentifiableTests, ConstructWithIdHasTheRightId) {
  constexpr auto x = Sheep{Sheep::id_type{1234}};
  ASSERT_EQ(Sheep::id_type{1234}, x.id());
}

TEST(IdentifiableTests, ConstructWithIdValueType) {
  constexpr auto x = Sheep{100};
  ASSERT_EQ(Sheep::id_type{100}, x.id());
}

///////////////////////////////////////////////////////////////////////////////

}  // namespace

///////////////////////////////////////////////////////////////////////////////
