// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

#include "nag_cpp.hpp"
#include "gtest/gtest.h"

auto test_problem = [](auto const &x, auto &y)
{
	y = pow(x[0], 2) + pow(x[1], 2);
};

class ProblemTest : public ::testing::Test
{
protected:
	nagcpp::types::f77_integer nvar;
	std::vector<double> x, b_lower, b_upper;

	void SetUp() override
	{
		nvar = 2;
		x = {-5, 3.9};
		b_lower = {-1.0, -2.0};
		b_upper = {0.8, 2.0};
	}

	template <typename PROBLEM_T>
	auto make_problem(PROBLEM_T &&problem)
	{
		auto ret = nagcpp::opt::Problem(nvar, problem);
		ret.set_initial_values(x);
		ret.set_simple_bounds(b_lower, b_upper);
		return ret;
	}
};

TEST_F(ProblemTest, NVarEQ)
{
	auto problem = make_problem(test_problem);
	ASSERT_EQ(nvar, problem.get_nvar()) << "nvar and problex.get_nvar are unequal";
}

TEST_F(ProblemTest, ObjFunEQ)
{
	auto problem = make_problem(test_problem);
	double y1, y2;
	long int _inform;
	long int &inform = _inform;
	test_problem(x, y1);
	problem.get_objfun()(x, y2, inform);
	ASSERT_EQ(y1, y2) << "test_problem and problem.get_objfun return unequal value";
}

TEST_F(ProblemTest, InitialValueEQ)
{
	auto problem = make_problem(test_problem);
	std::vector<double> getInitial = problem.get_initial();
	ASSERT_EQ(getInitial.size(), x.size()) << "Vectors x and problem.x_initial are of unequal length";
	for (int i = 0; i < nvar; ++i)
	{
		EXPECT_EQ(getInitial[i], x[i]) << "Vectors x and problem.x_initial differ at index " << i;
	}
}

TEST_F(ProblemTest, SimpleBoundsEQ)
{
	auto problem = make_problem(test_problem);
	auto getSimBounds = problem.get_simple_bounds();
	EXPECT_EQ(getSimBounds.first, b_lower) << "b_lower and problem.get_simple_bounds().first are unequal";
	EXPECT_EQ(getSimBounds.second, b_upper) << "b_upper and problem.get_simple_bounds().second are unequal";
}
