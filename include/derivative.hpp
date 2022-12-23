// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

/*! File for using dco/c++ library. */
#define DCO_AUTO_SUPPORT
#include "dco.hpp"

namespace nagcpp
{
    namespace opt
    {
        //! Namespace includes various functions for derivative calculating
        /*!
            Contains functions for calculating gradient (first derivative).
            Contains functions for calculating hessian matrix (second derivative).
            Contains functions for checking on linearity.

            Relies heavily on dco/c++ package.
        */
        namespace derivative
        {
            //! Function for calculating gradient for function F : R^n -> R.
            /*!
                \param x vector of variable x.
                \param f function, which gradient we want to calculate.

                Used for objective functions.
            */
            template <typename LAMBDA_T>
            std::vector<double> gradient(std::vector<double> x, LAMBDA_T &f)
            {
                std::vector<double> grad(x.size());
                using type = dco::gt1s<double>::type;
                std::vector<type> ax(x.begin(), x.end());
                for (std::size_t i = 0; i < x.size(); ++i)
                {
                    dco::derivative(ax[i]) = 1.0;
                    type ay = f(ax);
                    grad[i] = dco::derivative(ay);
                    dco::derivative(ax[i]) = 0.0;
                }
                return grad;
            }

            //! Function for calculating gradient for function F : R^n -> R^m.
            /*!
                \param x vector of variable x.
                \param f function, which gradient we want to calculate.
                \param idf index of output component of F, which gradient we want to calculate. Condition: 0 <= idf < m.

                Used for constraints functions.
            */
            template <typename LAMBDA_T>
            std::vector<double> con_gradient(std::vector<double> x, LAMBDA_T &f, int idf)
            {
                std::vector<double> grad(x.size());
                using type = dco::gt1s<double>::type;
                std::vector<type> ax(x.begin(), x.end());
                for (std::size_t i = 0; i < x.size(); ++i)
                {
                    dco::derivative(ax[i]) = 1.0;
                    auto ay = f(ax);
                    grad[i] = dco::derivative(ay[idf]); //!< We take calculate result only for component with index idf.
                    dco::derivative(ax[i]) = 0.0;
                }
                return grad;
            }

            //! Function for calculating Hessian matrix for function F : R^n -> R.
            /*!
                \param x vector of variable x.
                \param f function, which Hessian matrix we want to calculate.

                Used for objective functions.
            */
            template <typename LAMBDA_T>
            std::vector<std::vector<double>> hessian(std::vector<double> x, LAMBDA_T &f)
            {
                using mode_t = dco::ga1s<dco::gt1s<double>::type>;
                using type = mode_t::type;
                std::vector<std::vector<double>> hessian(x.size(), std::vector<double>(x.size()));
                mode_t::global_tape = mode_t::tape_t::create();
                std::vector<type> ax(x.begin(), x.end());
                for (std::size_t i = 0; i < x.size(); ++i)
                {
                    mode_t::global_tape->register_variable(ax);
                    dco::derivative(dco::value(ax[i])) = 1.0;
                    type y = f(ax);
                    mode_t::global_tape->register_output_variable(y);
                    dco::derivative(y) = 1.0;
                    mode_t::global_tape->interpret_adjoint();
                    for (std::size_t j = 0; j < x.size(); j++)
                    {
                        hessian[i][j] = dco::derivative(dco::derivative(ax[j]));
                    }
                    dco::derivative(dco::value(ax[i])) = 0.0;
                    mode_t::global_tape->reset();
                }
                mode_t::tape_t::remove(mode_t::global_tape);
                return hessian;
            }

            //! Function for calculating Hessian matrix for function F : R^n -> R^m.
            /*!
                \param x vector of variable x.
                \param f function, which Hessian matrix we want to calculate.
                \param idf index of output component of F, which Hessian matrix we want to calculate. Condition: 0 <= idf < m.

                Used for constraints functions.
            */
            template <typename LAMBDA_T>
            std::vector<std::vector<double>> con_hessian(std::vector<double> x, LAMBDA_T &f, int idf)
            {
                using mode_t = dco::ga1s<dco::gt1s<double>::type>;
                using type = mode_t::type;
                std::vector<std::vector<double>> hessian(x.size(), std::vector<double>(x.size()));
                mode_t::global_tape = mode_t::tape_t::create();
                std::vector<type> ax(x.begin(), x.end());
                for (std::size_t i = 0; i < x.size(); ++i)
                {
                    mode_t::global_tape->register_variable(ax);
                    dco::derivative(dco::value(ax[i])) = 1.0;
                    std::vector<type> y = f(ax);
                    mode_t::global_tape->register_output_variable(y[idf]);
                    dco::derivative(y[idf]) = 1.0;
                    mode_t::global_tape->interpret_adjoint();
                    for (std::size_t j = 0; j < x.size(); j++)
                    {
                        hessian[i][j] = dco::derivative(dco::derivative(ax[j]));
                    }
                    dco::derivative(dco::value(ax[i])) = 0.0;

                    mode_t::global_tape->reset();
                }
                mode_t::tape_t::remove(mode_t::global_tape);
                return hessian;
            }

            //! Function for checking linearity for function F : R^n -> R.
            /*!
                \param x vector of variable x.
                \param f function, which linearity we want to check.

                Calculates diagonal (only) of Hessian matrix and checks it on 0 values.
                1) All zeroes - linear.
                2) Otherwise - nonlinear.

                Used for objective functions.
            */
            template <typename LAMBDA_T>
            bool lincheck(std::vector<double> x, LAMBDA_T &f)
            {
                using mode_t = dco::ga1s<dco::gt1s<double>::type>;
                using type = mode_t::type;
                std::vector<double> secder(x.size());
                mode_t::global_tape = mode_t::tape_t::create();
                std::vector<type> ax(x.begin(), x.end());
                for (std::size_t i = 0; i < x.size(); ++i)
                {
                    mode_t::global_tape->register_variable(ax);
                    dco::derivative(dco::value(ax[i])) = 1.0;
                    type y = f(ax);
                    mode_t::global_tape->register_output_variable(y);
                    dco::derivative(y) = 1.0;
                    mode_t::global_tape->interpret_adjoint();
                    secder[i] = dco::derivative(dco::derivative(ax[i]));
                    dco::derivative(dco::value(ax[i])) = 0.0;
                    mode_t::global_tape->reset();
                }
                mode_t::tape_t::remove(mode_t::global_tape);
                for (std::size_t k = 0; k < x.size(); ++k)
                {
                    if (secder[k] != 0)
                        return false;
                }
                return true;
            }

            //! Function for checking linearity for function F : R^n -> R^m.
            /*!
                \param x vector of variable x.
                \param f function, which linearity we want to check.
                \param idf index of output component of F, which linearity we want to check. Condition: 0 <= idf < m.

                Calculates diagonal (only) of Hessian matrix and checks it on 0 values.
                1) All zeroes - linear.
                2) Otherwise - nonlinear.

                Used for constraints functions.
            */
            template <typename LAMBDA_T>
            bool con_lincheck(std::vector<double> x, LAMBDA_T &f, int idf)
            {
                using mode_t = dco::ga1s<dco::gt1s<double>::type>;
                using type = mode_t::type;
                std::vector<double> secder(x.size());
                mode_t::global_tape = mode_t::tape_t::create();
                std::vector<type> ax(x.begin(), x.end());
                for (std::size_t i = 0; i < x.size(); ++i)
                {
                    mode_t::global_tape->register_variable(ax);
                    dco::derivative(dco::value(ax[i])) = 1.0;
                    std::vector<type> y = f(ax);
                    mode_t::global_tape->register_output_variable(y[idf]);
                    dco::derivative(y[idf]) = 1.0;
                    mode_t::global_tape->interpret_adjoint();
                    secder[i] = dco::derivative(dco::derivative(ax[i]));
                    dco::derivative(dco::value(ax[i])) = 0.0;
                    mode_t::global_tape->reset();
                }

                mode_t::tape_t::remove(mode_t::global_tape);
                for (std::size_t k = 0; k < x.size(); ++k)
                {
                    if (secder[k] != 0)
                        return false;
                }
                return true;
            }
        }
    }
}
