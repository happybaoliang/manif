#include <gtest/gtest.h>

#include "manif/SO3.h"
#include "manif/impl/utils.h"

using namespace manif;

TEST(TEST_SO3, TEST_SO3_CONSTRUCTOR_QUAT)
{
  SO3d so3(SO3d::DataType(1,0,0,0));

  EXPECT_DOUBLE_EQ(0, so3.x());
  EXPECT_DOUBLE_EQ(0, so3.y());
  EXPECT_DOUBLE_EQ(0, so3.z());
  EXPECT_DOUBLE_EQ(1, so3.w());
}

TEST(TEST_SO3, TEST_SO3_CONSTRUCTOR_QUAT_COEFFS)
{
  SO3d so3(0,0,0,1);

  EXPECT_DOUBLE_EQ(0, so3.x());
  EXPECT_DOUBLE_EQ(0, so3.y());
  EXPECT_DOUBLE_EQ(0, so3.z());
  EXPECT_DOUBLE_EQ(1, so3.w());
}

TEST(TEST_SO3, TEST_SO3_CONSTRUCTOR_ANGLE_AXIS)
{
  SO3d so3(Eigen::AngleAxis<double>(0, Eigen::Vector3d::UnitX()));

  EXPECT_DOUBLE_EQ(0, so3.x());
  EXPECT_DOUBLE_EQ(0, so3.y());
  EXPECT_DOUBLE_EQ(0, so3.z());
  EXPECT_DOUBLE_EQ(1, so3.w());
}

TEST(TEST_SO3, TEST_SO3_CONSTRUCTOR_ROLL_PITCH_YAW)
{
  SO3d so3(0, 0, 0);

  EXPECT_DOUBLE_EQ(0, so3.x());
  EXPECT_DOUBLE_EQ(0, so3.y());
  EXPECT_DOUBLE_EQ(0, so3.z());
  EXPECT_DOUBLE_EQ(1, so3.w());
}

TEST(TEST_SO3, TEST_SO3_IDENTITY)
{
  SO3d so3;

  so3.setIdentity();

  EXPECT_DOUBLE_EQ(0, so3.x());
  EXPECT_DOUBLE_EQ(0, so3.y());
  EXPECT_DOUBLE_EQ(0, so3.z());
  EXPECT_DOUBLE_EQ(1, so3.w());
}

TEST(TEST_SO3, TEST_SO3_IDENTITY2)
{
  const SO3d so3 = SO3d::Identity();

  EXPECT_DOUBLE_EQ(0, so3.x());
  EXPECT_DOUBLE_EQ(0, so3.y());
  EXPECT_DOUBLE_EQ(0, so3.z());
  EXPECT_DOUBLE_EQ(1, so3.w());
}

TEST(TEST_SO3, TEST_SO3_RANDOM)
{
  SO3d so3;

  so3.setRandom();

  const SO3d& so3_ref = so3;

  EXPECT_DOUBLE_EQ(1, so3_ref.coeffs().norm());
}

TEST(TEST_SO3, TEST_SO3_RANDOM2)
{
  const SO3d so3 = SO3d::Random();

  EXPECT_DOUBLE_EQ(1, so3.coeffs().norm());
}

TEST(TEST_SO3, TEST_SO3_TRANSFORM)
{
  SO3d so3 = SO3d::Identity();

  SO3d::Transformation t = so3.transform();

  EXPECT_EQ(4, t.rows());
  EXPECT_EQ(4, t.cols());

  EXPECT_DOUBLE_EQ(1, t(0,0));
  EXPECT_DOUBLE_EQ(0, t(0,1));
  EXPECT_DOUBLE_EQ(0, t(0,2));
  EXPECT_DOUBLE_EQ(0, t(0,3));
  EXPECT_DOUBLE_EQ(0, t(1,0));
  EXPECT_DOUBLE_EQ(1, t(1,1));
  EXPECT_DOUBLE_EQ(0, t(1,2));
  EXPECT_DOUBLE_EQ(0, t(1,3));
  EXPECT_DOUBLE_EQ(0, t(2,0));
  EXPECT_DOUBLE_EQ(0, t(2,1));
  EXPECT_DOUBLE_EQ(1, t(2,2));
  EXPECT_DOUBLE_EQ(0, t(2,3));
  EXPECT_DOUBLE_EQ(0, t(3,0));
  EXPECT_DOUBLE_EQ(0, t(3,1));
  EXPECT_DOUBLE_EQ(0, t(3,2));
  EXPECT_DOUBLE_EQ(1, t(3,3));

  /// @todo Eigen matrix comparison
}

TEST(TEST_SO3, TEST_SO3_ROTATION)
{
  SO3d so3 = SO3d::Identity();

  SO3d::Rotation r = so3.rotation();

  EXPECT_EQ(3, r.rows());
  EXPECT_EQ(3, r.cols());

  EXPECT_DOUBLE_EQ(1, r(0,0));
  EXPECT_DOUBLE_EQ(0, r(0,1));
  EXPECT_DOUBLE_EQ(0, r(0,2));
  EXPECT_DOUBLE_EQ(0, r(1,0));
  EXPECT_DOUBLE_EQ(1, r(1,1));
  EXPECT_DOUBLE_EQ(0, r(1,2));
  EXPECT_DOUBLE_EQ(0, r(2,0));
  EXPECT_DOUBLE_EQ(0, r(2,1));
  EXPECT_DOUBLE_EQ(1, r(2,2));

  /// @todo Eigen matrix comparison
}

/*
TEST(TEST_SO3, TEST_SO3_ASSIGN_OP)
{
  SO3d so3a(0);
  SO3d so3b(M_PI);

  so3a = so3b;

  EXPECT_DOUBLE_EQ(M_PI, so3a.angle());
}
*/


TEST(TEST_SO3, TEST_SO3_INVERSE)
{
    // inverse of identity is identity
  SO3d so3 = SO3d::Identity();

  auto so3_inv = so3.inverse();

  EXPECT_DOUBLE_EQ(0, so3_inv.x());
  EXPECT_DOUBLE_EQ(0, so3_inv.y());
  EXPECT_DOUBLE_EQ(0, so3_inv.z());
  EXPECT_DOUBLE_EQ(1, so3_inv.w());

  // inverse of random in quaternion form is conjugate
  so3 = SO3d::Random();

  so3_inv = so3.inverse();

  EXPECT_DOUBLE_EQ(so3.x(), -so3_inv.x());
  EXPECT_DOUBLE_EQ(so3.y(), -so3_inv.y());
  EXPECT_DOUBLE_EQ(so3.z(), -so3_inv.z());
  EXPECT_DOUBLE_EQ(so3.w(), +so3_inv.w());
}

TEST(TEST_SO3, TEST_SO3_RPLUS)
{
    // Adding zero to Identity
  SO3d so3a = SO3d::Identity();
  SO3Tangentd so3b = SO3Tangentd::Zero();

  auto so3c = so3a.rplus(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.x());
  EXPECT_DOUBLE_EQ(0, so3c.y());
  EXPECT_DOUBLE_EQ(0, so3c.z());
  EXPECT_DOUBLE_EQ(1, so3c.w());

  // Adding zero to random
  so3a = SO3d::Random();

  so3c = so3a.rplus(so3b);

  EXPECT_DOUBLE_EQ(so3a.x(), so3c.x());
  EXPECT_DOUBLE_EQ(so3a.y(), so3c.y());
  EXPECT_DOUBLE_EQ(so3a.z(), so3c.z());
  EXPECT_DOUBLE_EQ(so3a.w(), so3c.w());

  // todo: adding something to something
}

TEST(TEST_SO3, TEST_SO3_LPLUS)
{
    // Adding zero to Identity
    SO3d so3a = SO3d::Identity();
    SO3Tangentd so3t = SO3Tangentd::Zero();

    auto so3c = so3a.lplus(so3t);

    EXPECT_DOUBLE_EQ(0, so3c.x());
    EXPECT_DOUBLE_EQ(0, so3c.y());
    EXPECT_DOUBLE_EQ(0, so3c.z());
    EXPECT_DOUBLE_EQ(1, so3c.w());

    // Adding zero to random
    so3a = SO3d::Random();

    so3c = so3a.lplus(so3t);

    EXPECT_DOUBLE_EQ(so3a.x(), so3c.x());
    EXPECT_DOUBLE_EQ(so3a.y(), so3c.y());
    EXPECT_DOUBLE_EQ(so3a.z(), so3c.z());
    EXPECT_DOUBLE_EQ(so3a.w(), so3c.w());

    // todo: adding something to something
}

TEST(TEST_SO3, TEST_SO3_PLUS)
{
    // plus() is the same as rplus()
  SO3d so3a = SO3d::Random();
  SO3Tangentd so3t = SO3Tangentd::Random();

  auto so3c = so3a.plus(so3t);
  auto so3d = so3a.rplus(so3t);

  EXPECT_DOUBLE_EQ(so3c.x(), so3d.x());
  EXPECT_DOUBLE_EQ(so3c.y(), so3d.y());
  EXPECT_DOUBLE_EQ(so3c.z(), so3d.z());
  EXPECT_DOUBLE_EQ(so3c.w(), so3d.w());
}

TEST(TEST_SO3, TEST_SO3_OP_PLUS)
{
    // manif + tangent is the same as rplus()
  SO3d so3a = SO3d::Random();
  SO3Tangentd so3t = SO3Tangentd::Random();

  auto so3c = so3a + so3t;
  auto so3d = so3a.rplus(so3t);

  EXPECT_DOUBLE_EQ(so3c.x(), so3d.x());
  EXPECT_DOUBLE_EQ(so3c.y(), so3d.y());
  EXPECT_DOUBLE_EQ(so3c.z(), so3d.z());
  EXPECT_DOUBLE_EQ(so3c.w(), so3d.w());
}

TEST(TEST_SO3, TEST_SO3_OP_PLUS_EQ)
{
    // manif += tangent is the same as rplus()
  SO3d so3a = SO3d::Random();
  SO3Tangentd so3t = SO3Tangentd::Random();

  auto so3d = so3a.rplus(so3t);
  so3a += so3t;

  EXPECT_DOUBLE_EQ(so3a.x(), so3d.x());
  EXPECT_DOUBLE_EQ(so3a.y(), so3d.y());
  EXPECT_DOUBLE_EQ(so3a.z(), so3d.z());
  EXPECT_DOUBLE_EQ(so3a.w(), so3d.w());
}

TEST(TEST_SO3, TEST_SO3_RMINUS)
{
    // identity minus identity is zero
  SO3d so3a = SO3d::Identity();
  SO3d so3b = SO3d::Identity();

  auto so3c = so3a.rminus(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(0));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(1));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(2));

  // random minus the same is zero
  so3a = SO3d::Random();
  so3b = so3a;

  so3c = so3a.rminus(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(0));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(1));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(2));

  // todo subtracting something from something
}

TEST(TEST_SO3, TEST_SO3_LMINUS)
{
    // identity minus identity is zero
  SO3d so3a = SO3d::Identity();
  SO3d so3b = SO3d::Identity();

  auto so3c = so3a.rminus(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(0));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(1));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(2));

  // random minus the same is zero
  so3a = SO3d::Random();
  so3b = so3a;

  so3c = so3a.rminus(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(0));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(1));
  EXPECT_DOUBLE_EQ(0, so3c.coeffs()(2));

  // todo subtracting something from something
}

TEST(TEST_SO3, TEST_SO3_MINUS)
{
    // minus is the same as rminus
  SO3d so3a = SO3d::Random();
  SO3d so3b = SO3d::Random();

  auto so3c = so3a.minus(so3b);
  auto so3d = so3a.rminus(so3b);

  EXPECT_DOUBLE_EQ(so3d.coeffs()(0), so3c.coeffs()(0));
  EXPECT_DOUBLE_EQ(so3d.coeffs()(1), so3c.coeffs()(1));
  EXPECT_DOUBLE_EQ(so3d.coeffs()(2), so3c.coeffs()(2));
}

TEST(TEST_SO3, TEST_SO3_OP_MINUS)
{
    // '-' is the same as rminus, and in the same order
  SO3d so3a = SO3d::Random();
  SO3d so3b = SO3d::Random();

  auto so3c = so3a - so3b;
  auto so3d = so3a.rminus(so3b);

  EXPECT_DOUBLE_EQ(so3d.coeffs()(0), so3c.coeffs()(0));
  EXPECT_DOUBLE_EQ(so3d.coeffs()(1), so3c.coeffs()(1));
  EXPECT_DOUBLE_EQ(so3d.coeffs()(2), so3c.coeffs()(2));
}

TEST(TEST_SO3, TEST_SO3_LIFT)
{
  SO3d so3;

  auto so3_lift = so3.lift();

//  EXPECT_DOUBLE_EQ(M_PI, so3_lift.angle());
}

TEST(TEST_SO3, TEST_SO3_COMPOSE)
{
  SO3d so3a(toRad(-165),toRad(-135),toRad(-90));
  SO3d so3b(toRad(15),toRad(45),toRad(90));

  auto so3c = so3a.compose(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.x());
  EXPECT_DOUBLE_EQ(0, so3c.y());
  EXPECT_DOUBLE_EQ(0, so3c.z());
  EXPECT_DOUBLE_EQ(1, so3c.w());
}

TEST(TEST_SO3, TEST_SO3_OP_COMPOSE)
{
  SO3d so3a(toRad(-165),toRad(-135),toRad(-90));
  SO3d so3b(toRad(15),toRad(45),toRad(90));

  auto so3c = so3a * so3b;

  EXPECT_DOUBLE_EQ(0, so3c.x());
  EXPECT_DOUBLE_EQ(0, so3c.y());
  EXPECT_DOUBLE_EQ(0, so3c.z());
  EXPECT_DOUBLE_EQ(1, so3c.w());
}

TEST(TEST_SO3, TEST_SO3_OP_COMPOSE_EQ)
{
  SO3d so3a(toRad(-165),toRad(-135),toRad(-90));
  SO3d so3b(toRad(15),toRad(45),toRad(90));

  so3a *= so3b;

  EXPECT_DOUBLE_EQ(0, so3a.x());
  EXPECT_DOUBLE_EQ(0, so3a.y());
  EXPECT_DOUBLE_EQ(0, so3a.z());
  EXPECT_DOUBLE_EQ(1, so3a.w());
}

TEST(TEST_SO3, TEST_SO3_BETWEEN)
{
  SO3d so3b(toRad(15),toRad(45),toRad(90));
  SO3d so3a(toRad(-15),toRad(-45),toRad(-90));

  auto so3c = so3a.between(so3b);

  EXPECT_DOUBLE_EQ(0, so3c.x());
  EXPECT_DOUBLE_EQ(0, so3c.y());
  EXPECT_DOUBLE_EQ(0, so3c.z());
  EXPECT_DOUBLE_EQ(1, so3c.w());
}

/// with Jacs

TEST(TEST_SO3, TEST_SO3_INVERSE_JAC)
{
  SO3d so3 = SO3d::Identity();

  SO3d::Jacobian J_inv;
  SO3d so3_inv = so3.inverse(J_inv);

  EXPECT_DOUBLE_EQ(0, so3_inv.x());
  EXPECT_DOUBLE_EQ(0, so3_inv.y());
  EXPECT_DOUBLE_EQ(0, so3_inv.z());
  EXPECT_DOUBLE_EQ(1, so3_inv.w());

  EXPECT_EQ(3, J_inv.rows());
  EXPECT_EQ(3, J_inv.cols());

  /// @todo
//  EXPECT_DOUBLE_EQ(Eigen::Matrix3d::Identity(), J_inv);

//  so3.angle(M_PI);
//  so3_inv = so3.inverse(J_inv);

//  EXPECT_DOUBLE_EQ(-M_PI, so3_inv.angle());

//  EXPECT_EQ(1, J_inv.rows());
//  EXPECT_EQ(1, J_inv.cols());
//  EXPECT_DOUBLE_EQ(-1, J_inv(0));
}

TEST(TEST_SO3, TEST_SO3_LIFT_JAC)
{
  SO3d so3(0,0,0);

  SO3d::Tangent::Jacobian J_lift;

  /// @todo Jac not implemented yet
  SO3d::Tangent so3_lift = so3.lift(/*J_lift*/);

  EXPECT_DOUBLE_EQ(0, so3_lift.x());
  EXPECT_DOUBLE_EQ(0, so3_lift.y());
  EXPECT_DOUBLE_EQ(0, so3_lift.z());

  /// @todo check this J
  EXPECT_EQ(3, J_lift.rows());
  EXPECT_EQ(3, J_lift.cols());

//  EXPECT_DOUBLE_EQ(1, J_lift(0));
}

TEST(TEST_SO3, TEST_SO3_COMPOSE_JAC)
{
  SO3d so3a(toRad(-165),toRad(-135),toRad(-90));
  SO3d so3b(toRad(15),  toRad(45),  toRad(90));

  SO3d::Jacobian J_c_a, J_c_b;

  SO3d so3c = so3a.compose(so3b, J_c_a, J_c_b);

  EXPECT_DOUBLE_EQ(0, so3c.x());
  EXPECT_DOUBLE_EQ(0, so3c.y());
  EXPECT_DOUBLE_EQ(0, so3c.z());
  EXPECT_DOUBLE_EQ(1, so3c.w());

//  EXPECT_EQ(1, J_c_a.rows());
//  EXPECT_EQ(1, J_c_a.cols());
//  EXPECT_DOUBLE_EQ(1, J_c_a(0));

//  EXPECT_EQ(1, J_c_b.rows());
//  EXPECT_EQ(1, J_c_b.cols());
//  EXPECT_DOUBLE_EQ(1, J_c_b(0));
}
/*
TEST(TEST_SO3, TEST_SO3_RPLUS_JAC)
{
  SO3d so3a;
  SO3Tangentd so3b;

  SO3d so3c;
  SO3d::Jacobian J_rplus_m;
  SO3d::Jacobian J_rplus_t;

  so3a.rplus(so3b, so3c, J_rplus_m, J_rplus_t);

  EXPECT_DOUBLE_EQ(M_PI, so3c.angle());

  EXPECT_EQ(1, J_rplus_m.rows());
  EXPECT_EQ(1, J_rplus_m.cols());
  EXPECT_DOUBLE_EQ(1, J_rplus_m(0));

  EXPECT_EQ(1, J_rplus_t.rows());
  EXPECT_EQ(1, J_rplus_t.cols());
  EXPECT_DOUBLE_EQ(1, J_rplus_t(0));
}

TEST(TEST_SO3, TEST_SO3_LPLUS_JAC)
{
  SO3d so3a;
  SO3Tangentd so3b;

  SO3d so3c;
  SO3d::Jacobian J_lplus_t;
  SO3d::Jacobian J_lplus_m;

  so3a.lplus(so3b, so3c, J_lplus_t, J_lplus_m);

  EXPECT_DOUBLE_EQ(M_PI, so3c.angle());

  EXPECT_EQ(1, J_lplus_t.rows());
  EXPECT_EQ(1, J_lplus_t.cols());
  EXPECT_DOUBLE_EQ(1, J_lplus_t(0));

  EXPECT_EQ(1, J_lplus_m.rows());
  EXPECT_EQ(1, J_lplus_m.cols());
  EXPECT_DOUBLE_EQ(1, J_lplus_m(0));
}

TEST(TEST_SO3, TEST_SO3_PLUS_JAC)
{
  SO3d so3a;
  SO3Tangentd so3b;

  SO3d so3c;
  SO3d::Jacobian J_plus_m;
  SO3d::Jacobian J_plus_t;

  so3a.plus(so3b, so3c, J_plus_m, J_plus_t);

  EXPECT_DOUBLE_EQ(M_PI, so3c.angle());

  EXPECT_EQ(1, J_plus_m.rows());
  EXPECT_EQ(1, J_plus_m.cols());
  EXPECT_DOUBLE_EQ(1, J_plus_m(0));

  EXPECT_EQ(1, J_plus_t.rows());
  EXPECT_EQ(1, J_plus_t.cols());
  EXPECT_DOUBLE_EQ(1, J_plus_t(0));
}

TEST(TEST_SO3, TEST_SO3_RMINUS_JAC)
{
  SO3d so3a(M_PI);
  SO3d so3b(M_PI_2);

  SO3Tangentd so3c;

  SO3d::Jacobian J_rminus_a, J_rminus_b;

  so3a.rminus(so3b, so3c, J_rminus_a, J_rminus_b);

  EXPECT_DOUBLE_EQ(M_PI_2, so3c.angle());

  EXPECT_EQ(1, J_rminus_a.rows());
  EXPECT_EQ(1, J_rminus_a.cols());
  EXPECT_DOUBLE_EQ(1, J_rminus_a(0));

  EXPECT_EQ(1, J_rminus_b.rows());
  EXPECT_EQ(1, J_rminus_b.cols());
  EXPECT_DOUBLE_EQ(-1, J_rminus_b(0));
}

TEST(TEST_SO3, TEST_SO3_LMINUS_JAC)
{
  SO3d so3a(M_PI);
  SO3d so3b(M_PI_2);

  SO3Tangentd so3c;

  SO3d::Jacobian J_lminus_a, J_lminus_b;

  so3a.lminus(so3b, so3c, J_lminus_a, J_lminus_b);

  EXPECT_DOUBLE_EQ(-M_PI_2, so3c.angle());

  EXPECT_EQ(1, J_lminus_a.rows());
  EXPECT_EQ(1, J_lminus_a.cols());
  EXPECT_DOUBLE_EQ(-1, J_lminus_a(0));

  EXPECT_EQ(1, J_lminus_b.rows());
  EXPECT_EQ(1, J_lminus_b.cols());
  EXPECT_DOUBLE_EQ(1, J_lminus_b(0));
}

TEST(TEST_SO3, TEST_SO3_MINUS_JAC)
{
  SO3d so3a(M_PI);
  SO3d so3b(M_PI_2);

  SO3Tangentd so3c;

  SO3d::Jacobian J_minus_a, J_minus_b;

  so3a.minus(so3b, so3c, J_minus_a, J_minus_b);

  EXPECT_DOUBLE_EQ(M_PI_2, so3c.angle());

  EXPECT_EQ(1, J_minus_a.rows());
  EXPECT_EQ(1, J_minus_a.cols());
  EXPECT_DOUBLE_EQ(1, J_minus_a(0));

  EXPECT_EQ(1, J_minus_b.rows());
  EXPECT_EQ(1, J_minus_b.cols());
  EXPECT_DOUBLE_EQ(-1, J_minus_b(0));
}

*/

TEST(TEST_SO3, TEST_SO3_BETWEEN_JAC)
{
  SO3d so3b(toRad(15),toRad(45),toRad(90));
  SO3d so3a(toRad(-15),toRad(-45),toRad(-90));

  SO3d::Jacobian J_between_a, J_between_b;

  SO3d so3c = so3a.between(so3b, J_between_a, J_between_b);

  EXPECT_DOUBLE_EQ(0, so3c.x());
  EXPECT_DOUBLE_EQ(0, so3c.y());
  EXPECT_DOUBLE_EQ(0, so3c.z());
  EXPECT_DOUBLE_EQ(1, so3c.w());

  EXPECT_EQ(3, J_between_a.rows());
  EXPECT_EQ(3, J_between_a.cols());

  EXPECT_EQ(3, J_between_b.rows());
  EXPECT_EQ(3, J_between_b.cols());
}

TEST(TEST_SO3, TEST_SO3_TANGENT_SKEW)
{
  SO3Tangentd so3_tan(SO3Tangentd::DataType(1, 2, 3));

  SO3Tangentd::LieType so3_lie = so3_tan.skew();

  EXPECT_DOUBLE_EQ( 0, so3_lie(0,0));
  EXPECT_DOUBLE_EQ(-3, so3_lie(0,1));
  EXPECT_DOUBLE_EQ( 2, so3_lie(0,2));
  EXPECT_DOUBLE_EQ( 3, so3_lie(1,0));
  EXPECT_DOUBLE_EQ( 0, so3_lie(1,1));
  EXPECT_DOUBLE_EQ(-1, so3_lie(1,2));
  EXPECT_DOUBLE_EQ(-2, so3_lie(2,0));
  EXPECT_DOUBLE_EQ( 1, so3_lie(2,1));
  EXPECT_DOUBLE_EQ( 0, so3_lie(2,2));
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
