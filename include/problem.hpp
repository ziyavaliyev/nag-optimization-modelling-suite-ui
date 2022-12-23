// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

/*! Standard libraries". */
#include <iostream>
#include <math.h>
#include <numeric>
#include <vector>
#include <functional>
#include <unordered_map>

/*! File for calculating derivatives". */
#include "derivative.hpp"

/*! File include data type f77_integer used in this class. */
#include "e04/nagcpp_class_CommE04RA.hpp"

namespace nagcpp
{
    namespace opt
    {
        //! Problem class.
        /*!
            Contains information about objective function.
            Contains information about constraints.
        */
        template <typename LAMBDA_T>
        class Problem
        {
        private:
            LAMBDA_T &var_problem;   //!< Objective function in form of lambda function.
            types::f77_integer nvar; //!< Size of variable x.
            types::f77_integer mvar; //!< Amount of nonlinear constraints.

            std::function<void(const std::vector<double> &, double &, types::f77_integer &)> objfun;              //!< Objective function in form of std::function.
            std::function<void(const std::vector<double> &, std::vector<double> &, types::f77_integer &)> objgrd; //!< Gradient of the objective function.

            std::vector<double> x_initial;                                    //!< Start values of vector x.
            std::vector<double> simple_bound_lower, simple_bound_upper;       //!< Borders of box constraints.
            std::vector<double> linear_bound_lower, linear_bound_upper;       //!< Borders of linear constraints.
            std::vector<double> a_matrix;                                     //!< Sparse matrix of linear constraints.
            std::vector<double> nonlinear_bound_lower, nonlinear_bound_upper; //!< Borders of nonlinear constraints.
            std::vector<double> lin_coefs;                                    //!< Linear coefficients of objective function, if it is linear.

            int const LIN_CHECK_N = 20; //!< Amount of points where linearity of function will be checked.
                                        /*!< We check linearity in multiple points, because due to the construction of the function,
                                            checking in only few points can lead to incorrect result. */

            std::unordered_map<std::string, bool> problem_info; //!< std::map structure of flags with information about defined and undefined parameters.

            std::vector<bool> linearity_mask; //!< Information about linear and nonlinear components of nonlinear constraints.
            int lin_mask_zeroes = 0;          //!< Amount of nonlinear components of nonlinear constraints.

            std::function<void(const std::vector<double> &, types::f77_integer, std::vector<double> &, types::f77_integer &)> confun; //!< Constraint function in form of std::function.
            std::function<void(const std::vector<double> &, std::vector<double> &, types::f77_integer &)> congrd;                     //!< Gradient of the constraint function.

            std::function<void(const std::vector<double> &, const types::f77_integer, const double, const std::vector<double> &,
                               std::vector<double> &, types::f77_integer &)>
                hess; //!< Hessian function.

        public:
            //! Empty constructor.
            Problem() {}

            //! Constructor.
            /*!
                \param _nvar size of variable x.
                \param _var_problem objective function in form of lambda function.

                Initialization of basic values.
                Check on linearity of the objective function.
            */
            Problem(types::f77_integer _nvar, LAMBDA_T &_var_problem) : var_problem(_var_problem)
            {
                nvar = _nvar;

                problem_info["is_linear"] = true;
                problem_info["simple_bounds_declared"] = false;
                problem_info["linear_bounds_declared"] = false;
                problem_info["nonlinear_bounds_declared"] = false;

                linear_bound_lower.clear();
                linear_bound_upper.clear();
                nonlinear_bound_lower.clear();
                nonlinear_bound_upper.clear();

                linearity_mask.clear();
                lin_mask_zeroes = 0;

                //! Objective function.
                /*!
                    \param x vector of variable x.
                    \param y the value of objective function in x.
                    \param inform additional information.
                */
                auto _objfun = [&_var_problem](auto const &x, auto &y, auto &inform)
                {
                    _var_problem(x, y);
                };
                this->objfun = _objfun;

                //! Objective gradient.
                /*!
                    \param x vector of variable x.
                    \param fdx the value of objective gradient in x.
                    \param inform additional information.
                */
                auto _objgrd = [&_var_problem](auto const &x, auto &fdx, auto &inform)
                {
                    auto gradient_problem = [&_var_problem](auto const &x)
                    {
                        std::decay_t<decltype(x[0])> y;
                        _var_problem(x, y);
                        return y;
                    };

                    fdx = nagcpp::opt::derivative::gradient(x, gradient_problem);
                };
                this->objgrd = _objgrd;

                //! Objective function wrapper.
                /*!
                    \param x vector of variable x.
                    \return y the value of objective gradient in x.

                    Transforms objective function into the form that is used in "derivative.hpp" functions.
                */
                auto wrap_problem = [&_var_problem](auto const &x)
                {
                    std::decay_t<decltype(x[0])> y;
                    _var_problem(x, y);
                    return y;
                };

                for (int num = 1; num <= LIN_CHECK_N; ++num)
                {
                    std::vector<double> x(_nvar, (double)num);
                    if (!nagcpp::opt::derivative::lincheck(x, wrap_problem))
                    {
                        this->problem_info["is_linear"] = false;
                        break;
                    }
                }

                //! If objective is linear, we derive linear coefficients from the gradient.
                if (problem_info["is_linear"])
                {
                    std::vector<double> x(_nvar, 1.0);
                    lin_coefs = nagcpp::opt::derivative::gradient(x, wrap_problem);
                }
            }

            //! Function for setting initial values of variable x.
            /*!
                \param _initial initial value.
            */
            void set_initial_values(std::vector<double> _initial)
            {
                this->x_initial = _initial;
            }

            //! Function for setting box constraints.
            /*!
                \param lower lower border of variable x.
                \param upper upper border of variable x.
            */
            void set_simple_bounds(std::vector<double> lower, std::vector<double> upper)
            {
                this->problem_info["simple_bounds_declared"] = true;

                this->simple_bound_lower = lower;
                this->simple_bound_upper = upper;
            }

            //! Function for setting linear constraints.
            /*!
                \param lower lower border of a * x.
                \param upper upper border of a * x.
                \param a matrix of linear constraints.
            */
            void set_linear_bounds(std::vector<double> lower, std::vector<double> upper, std::vector<double> a)
            {
                this->problem_info["linear_bounds_declared"] = true;

                for (int i = 0; i < lower.size(); ++i)
                {
                    this->linear_bound_lower.push_back(lower[i]);
                    this->linear_bound_upper.push_back(upper[i]);
                    for (int j = 0; j < this->nvar; ++j)
                    {
                        this->a_matrix.push_back(a[i * this->nvar + j]);
                    }
                }
            }

            //! Function for setting nonlinear constraints.
            /*!
                \param lower lower border of con_problem(x).
                \param upper upper border of con_problem(x).
                \param con_problem constraint function.
            */
            template <typename CON_LAMBDA_T>
            void set_nonlinear_bounds(std::vector<double> lower, std::vector<double> upper, CON_LAMBDA_T &con_problem)
            {
                this->mvar = lower.size();

                auto obj_problem = this->var_problem;

                //! Objective function wrapper.
                /*!
                    \param x vector of variable x.
                    \return y the value of objective gradient in x.

                    Transforms objective function into the form that is used in "derivative.hpp" functions.
                */
                auto obj_wrap_problem = [&obj_problem](auto const &x)
                {
                    std::decay_t<decltype(x[0])> y;
                    obj_problem(x, y);
                    return y;
                };

                //! Constraint function wrapper.
                /*!
                    \param x vector of variable x.
                    \return y the value of constraint gradient in x.

                    Transforms constraint function into the form that is used in "derivative.hpp" functions.
                    This wrapper DOES NOT take into account linearity of each component.
                */
                auto con_wrap_problem_not_adjusted = [&con_problem](auto const &x)
                {
                    std::vector<std::decay_t<decltype(x[0])>> y;
                    con_problem(x, y);
                    return y;
                };

                /*! Check on linearity for every component of nonlinear constraints.
                    Then filter out linear components and move them to linear constraints.
                    Fill in linearity mask with respective values. */
                for (int i = 0; i < this->mvar; ++i)
                {
                    bool con_is_linear = true;
                    for (int num = 1; num <= LIN_CHECK_N; ++num)
                    {
                        std::vector<double> x(this->nvar, (double)num);
                        if (!nagcpp::opt::derivative::con_lincheck(x, con_wrap_problem_not_adjusted, i))
                        {
                            con_is_linear = false;
                            break;
                        }
                    }

                    if (con_is_linear)
                    {
                        this->linear_bound_lower.push_back(lower[i]);
                        this->linear_bound_upper.push_back(upper[i]);

                        std::vector<double> x(this->nvar, 1.0);
                        auto con_lin_coefs = nagcpp::opt::derivative::con_gradient(x, con_wrap_problem_not_adjusted, i);
                        for (int j = 0; j < this->nvar; ++j)
                        {
                            this->a_matrix.push_back(con_lin_coefs[j]);
                        }

                        this->problem_info["linear_bounds_declared"] = true;
                    }
                    else
                    {
                        this->nonlinear_bound_lower.push_back(lower[i]);
                        this->nonlinear_bound_upper.push_back(upper[i]);

                        this->problem_info["nonlinear_bounds_declared"] = true;

                        this->lin_mask_zeroes++; //!< Counting nonlinear components.
                    }

                    this->linearity_mask.push_back(con_is_linear); //!< Filling in linearity mask.
                }

                //! Constraint function wrapper.
                /*!
                    \param x vector of variable x.
                    \return y the value of constraint gradient in x (only for linear components of constraints).

                    Transforms constraint function into the form that is used in "derivative.hpp" functions.
                    This wrapper DOES take into account linearity of each component.
                */
                auto con_wrap_problem = [&con_problem, this](auto const &x)
                {
                    std::vector<std::decay_t<decltype(x[0])>> temp;
                    std::vector<std::decay_t<decltype(x[0])>> y;
                    con_problem(x, temp);

                    //! Filtering nonlinear components.
                    y.resize(this->lin_mask_zeroes);
                    int k = 0;
                    for (int i = 0; i < this->mvar; ++i)
                    {
                        if (this->linearity_mask[i])
                        {
                            continue;
                        }

                        y[k] = temp[i];
                        ++k;
                    }

                    return y;
                };

                //! Constraint function.
                /*!
                    \param x vector of variable x.
                    \param ncnln number of nonlinear constraints.
                    \param y the value of constraint function in x (only for linear components of constraint).
                    \param inform additional information.
                */
                auto _confun = [&con_problem, this](auto const &x, types::f77_integer ncnln, std::vector<double> &y, auto &inform)
                {
                    std::vector<double> temp;
                    con_problem(x, temp);

                    //! Filtering nonlinear components.
                    y.resize(this->lin_mask_zeroes);
                    int k = 0;
                    for (int i = 0; i < this->mvar; ++i)
                    {
                        if (this->linearity_mask[i])
                        {
                            continue;
                        }

                        y[k] = temp[i];
                        ++k;
                    }
                };
                this->confun = _confun;

                //! Constraint function.
                /*!
                    \param x vector of variable x.
                    \param fdx the value of constraint gradient in x (only for linear components of constraint).
                    \param nnzgd number of nonzero elements in the sparse Jacobian matrix.
                */
                auto _congrd = [con_wrap_problem, this](auto const &x, auto &fdx, auto &nnzgd)
                {
                    std::vector<double> jacobian_transform;
                    for (int i = 0; i < this->lin_mask_zeroes; ++i)
                    {
                        auto grad = nagcpp::opt::derivative::con_gradient(x, con_wrap_problem, i);

                        for (int j = 0; j < this->nvar; ++j)
                        {
                            jacobian_transform.push_back(grad[j]);
                        }
                    }
                    fdx = jacobian_transform;
                };
                this->congrd = _congrd;

                //! Constraint function.
                /*!
                    \param x vector of variable x.
                    \param idf specification of computed result
                            idf = -1 : the values of the Hessian of the Lagrangian will be computed.
                            idf = 0  : the values of the Hessian of the objective function will be computed.
                            idf > 0  : the values of the Hessian of the constraint function with index idf will be computed.

                    \param sigma the value of the sigma quantity in the definition of the Hessian of the Lagrangian.
                    \param lamda the value of the lamda quantity in the definition of the Hessian of the Lagrangian.
                            Definition of the Lagrangian: sigma * H(f(x)) + sum(lamda_i * H(g_i(x))), where
                                H(f(x)) - Hessian of objective function.
                                H(g_i(x)) - Hessian of i-th component of constraint function.
                                sum - summarize all elements for i = 1..ncnln.

                    \param ffdxdx the value of constraint hessian matrix in x (only for linear components of constraint).
                    \param inform additional information.
                */
                auto _hess = [obj_wrap_problem, con_wrap_problem, this](auto const &x, auto idf, auto sigma, auto &lamda, auto &ffdxdx, auto &inform)
                {
                    //! Because of symmetry of Hessian, we only need upper triangle of matrix.

                    auto obj_mtrx = nagcpp::opt::derivative::hessian(x, obj_wrap_problem);
                    std::vector<double> obj_hess_transform;
                    for (int i = 0; i < x.size(); ++i)
                    {
                        for (int j = i; j < x.size(); ++j)
                        {
                            obj_hess_transform.push_back(obj_mtrx[i][j]);
                        }
                    }

                    std::vector<std::vector<double>> con_hess_transform_list;
                    for (int k = 0; k < this->lin_mask_zeroes; ++k)
                    {
                        auto mtrx = nagcpp::opt::derivative::con_hessian(x, con_wrap_problem, k);
                        std::vector<double> mtrx_transform;

                        for (int i = 0; i < x.size(); ++i)
                        {
                            for (int j = i; j < x.size(); ++j)
                            {
                                mtrx_transform.push_back(mtrx[i][j]);
                            }
                        }
                        con_hess_transform_list.push_back(mtrx_transform);
                    }

                    if (idf == -1)
                    {
                        //! Calculate Hessian of the Lagrangian.
                        std::vector<double> lag_hess_transform;
                        int k = 0;
                        for (int i = 0; i < x.size(); ++i)
                        {
                            for (int j = i; j < x.size(); ++j)
                            {
                                double con_sum = 0;
                                for (int v = 0; v < con_hess_transform_list.size(); ++v)
                                {
                                    con_sum += con_hess_transform_list[v][k] * lamda[v];
                                }
                                lag_hess_transform.push_back(sigma * obj_hess_transform[k] + con_sum);
                                ++k;
                            }
                        }

                        ffdxdx = lag_hess_transform;
                    }
                    else if (idf == 0)
                    {
                        ffdxdx = obj_hess_transform;
                    }
                    else
                    {
                        ffdxdx = con_hess_transform_list[idf - 1];
                    }
                };
                this->hess = _hess;
            }

            //! Set of get-functions for interaction between Solver and Problem classes.

            //! Get size of variable x.
            auto get_nvar()
            {
                return this->nvar;
            }

            //! Get objective function in form of std::function.
            auto get_objfun()
            {
                return this->objfun;
            }

            //! Get objective gradient.
            auto get_objgrd()
            {
                return this->objgrd;
            }

            //! Get constraint function in form of std::function.
            auto get_confun()
            {
                return this->confun;
            }

            //! Get constraint gradient.
            auto get_congrd()
            {
                return this->congrd;
            }

            //! Get Hessian function.
            auto get_hess()
            {
                return this->hess;
            }

            //! Get start values of variable x.
            auto get_initial()
            {
                return this->x_initial;
            }

            //! Get borders for box constraints.
            auto get_simple_bounds()
            {
                return make_pair(this->simple_bound_lower, this->simple_bound_upper);
            }

            //! Get borders for linear constraints.
            auto get_linear_bounds()
            {
                return make_pair(this->linear_bound_lower, this->linear_bound_upper);
            }

            //! Get borders for nonlinear constraints.
            auto get_nonlinear_bounds()
            {
                return make_pair(this->nonlinear_bound_lower, this->nonlinear_bound_upper);
            }

            //! Get linear coefficients of  linear objective function.
            auto get_lin_coefs()
            {
                return this->lin_coefs;
            }

            //! Get matrix for linear constraints.
            auto get_a_matrix()
            {
                return this->a_matrix;
            }

            //! Get information about initialized constraints and linearity.
            auto get_problem_info()
            {
                return this->problem_info;
            }
        };
    }
}
