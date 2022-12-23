// info@stce.rwth-aachen.de
// C++ UI design for NAG Optimization Modelling Suite
// Group 6: Tran, Man Khang; Feldman, Maksim; Valiyev, Ziya; Korkin, Konstantin; Huang, Yifei
// Superviser: Lotz, Johannes

/*! Files for creating and managing "handle". */
#include "e04/nagcpp_class_CommE04RA.hpp"
#include "e04/nagcpp_e04ra.hpp"

/*! Files for setting objective function. */
#include "e04/nagcpp_e04re.hpp"
#include "e04/nagcpp_e04rg.hpp"

/*! Files for setting different types of constraints. */
#include "e04/nagcpp_e04rh.hpp"
#include "e04/nagcpp_e04rj.hpp"
#include "e04/nagcpp_e04rk.hpp"

/*! File for setting hessian matrix of nonlinear constraints. */
#include "e04/nagcpp_e04rl.hpp"

/*! Files including different types of solvers. */
#include "e04/nagcpp_e04kf.hpp"
#include "e04/nagcpp_e04mt.hpp"
#include "e04/nagcpp_e04st.hpp"

/*! File including class "Problem", which contains all parameters of the problem itself. */
#include "problem.hpp"

/*! File including class "MonitorOption", which contains options for the solver. */
#include "monitor.hpp"

namespace nagcpp
{
    namespace opt
    {
        //! Solver class.
        /*!
            Contains respective solver-methods.
        */
        class Solver
        {
        private:
            //! Arguments for solvers.
            CommE04RA handle;          //!< Main object of problem solving. Contains all information about problem and output.
            std::vector<double> rinfo; //!< Error measures and various indicators at the end of the final iteration.
            std::vector<double> stats; //!< Solver statistics at the end of the final iteration.
            OptionalE04KF opt;         //!< Optional parameter container (for solvers e04kf, e04mt).
            OptionalE04ST opt_st;      //!< Optional parameter container (for solver e04st).

            //! Helper vars for monitoring.
            std::stringstream monitoring_buffer;
            nagcpp::opt::MonitorOption monitoring_info;

            //! Function for setting box constraints.
            /*!
                \param problem reference to the object of class Problem. Contains information about current box constraints.

                Box constraints can be written in the following form:
                                L <= x <= R
                Where:
                    x - main variable (size N).
                    L - vector, containing lower borders for x (size N).
                    R - vector, containing upper borders for x (size N).
            */
            template <typename PROBLEM_T>
            void set_simple_constraints(PROBLEM_T &problem)
            {
                auto simple_bounds = problem.get_simple_bounds();
                handle_set_simplebounds(this->handle, simple_bounds.first, simple_bounds.second);
            }

            //! Function for setting linear constraints.
            /*!
                \param problem reference to the object of class Problem. Contains information about current linear constraints.

                Linear constraints can be written in the following form:
                                L <= B*x <= R
                Where:
                    x - main variable (size N).
                    B - constant matrix (size M x N)
                    L - vector, containing lower borders for x (size M).
                    R - vector, containing upper borders for x (size M).
            */
            template <typename PROBLEM_T>
            void set_linear_constraints(PROBLEM_T &problem)
            {
                auto linear_bounds = problem.get_linear_bounds();
                int ml = linear_bounds.first.size();                  //!< Number of linear constraints.
                std::vector<nagcpp::types::f77_integer> irowa, icola; //!< Information about sparse matrix.

                //! Construction of basic sparse matrix.
                for (int i = 1; i <= ml; ++i)
                {
                    for (int j = 1; j <= problem.get_nvar(); ++j)
                    {
                        irowa.push_back(i);
                        icola.push_back(j);
                    }
                }

                handle_set_linconstr(this->handle, linear_bounds.first, linear_bounds.second, irowa, icola, problem.get_a_matrix());
            }

            //! Function for setting nonlinear constraints.
            /*!
                \param problem reference to the object of class Problem. Contains information about current nonlinear constraints.

                Linear constraints can be written in the following form:
                                L <= g(x) <= R
                Where:
                    x - main variable (size N)
                    g(x) - constraint function (size of result M).
                    L - vector, containing lower borders for x (size M).
                    R - vector, containing upper borders for x (size M).
            */
            template <typename PROBLEM_T>
            void set_nonlinear_constraints(PROBLEM_T &problem)
            {
                auto nonlinear_bounds = problem.get_nonlinear_bounds();
                int mn = nonlinear_bounds.first.size();               //!< Number of nonlinear constraints.
                std::vector<nagcpp::types::f77_integer> irowa, icola; //!< Information about sparse matrix.

                //! Construction of basic sparse matrix.
                for (int i = 1; i <= mn; ++i)
                {
                    for (int j = 1; j <= problem.get_nvar(); ++j)
                    {
                        irowa.push_back(i);
                        icola.push_back(j);
                    }
                }

                handle_set_nlnconstr(this->handle, nonlinear_bounds.first, nonlinear_bounds.second, irowa, icola);
            }

            //! Function for setting nonlinear objective function.
            /*!
                \param problem reference to the object of class Problem. Contains information about objective function and its linearity.
            */
            template <typename PROBLEM_T>
            void setup_nlnobj(PROBLEM_T &problem)
            {
                std::vector<types::f77_integer> idxfd(problem.get_nvar());
                std::iota(idxfd.begin(), idxfd.end(), 1);
                handle_set_nlnobj(this->handle, idxfd);
            }

            //! Function for setting linear objective function.
            /*!
                \param problem reference to the object of class Problem. Contains information about objective function and its linearity.
            */
            template <typename PROBLEM_T>
            void setup_linobj(PROBLEM_T &problem)
            {
                handle_set_linobj(this->handle, problem.get_lin_coefs());
            }

            //! Function for setting monitoring options.
            void apply_monitoring_parameters()
            {
                this->handle.MonitoringLevel(this->monitoring_info.get_monitoring_level());
                this->handle.MonitoringFile(this->monitoring_info.get_monitoring_unit_number());

                this->handle.PrintLevel(this->monitoring_info.get_print_level());
                this->handle.PrintSolution((this->monitoring_info.get_print_solution() ? "yes" : "no"));
                this->handle.PrintOptions((this->monitoring_info.get_print_options() ? "yes" : "no"));
                this->handle.FOASPrintFrequency(this->monitoring_info.get_foas_print_frequency());
            }

        public:
            //! Constructor.
            /*!
                \param nvar size of variable x.

                Initialization of handle and basic monitoring parameters.
            */
            Solver(types::f77_integer nvar) : handle(nvar)
            {
                //! Initialization of monitoring parameters.
                monitoring_info = MonitorOption(monitoring_buffer);
            }

            //! Function for setting custom monitoring parameters.
            /*!
                \param _monitoring_info object of class MonitorOption, consisting new monitoring parameters.

                Monitoring level can be changed (Basic value = 3).
                Print level can be changed (Basic value = 1).
                FOAS Print frequency can be changed (Basic value = 5).
                Print solution can be toggled ON and OFF (Basic value = True).
                Print options can be toggled ON and OFF (Basic value = False).

                Number of monitoring unit and Monitoring buffer CAN NOT be changed.
            */
            void set_monitoring_info(MonitorOption _monitoring_info)
            {
                this->monitoring_info.set_monitoring_level(_monitoring_info.get_monitoring_level());
                this->monitoring_info.set_print_level(_monitoring_info.get_print_level());
                this->monitoring_info.toggle_print_solution(_monitoring_info.get_print_solution());
                this->monitoring_info.toggle_print_options(_monitoring_info.get_print_options());
                this->monitoring_info.set_foas_print_frequency(_monitoring_info.get_foas_print_frequency());
            }

            //! Function for solving problem with explicitly e04kf.
            /*!
                \param problem object of class Problem, containing all information about the task.

                Does not analyze parameters of the problem. Is not recommended for regular usage.
                Errors can occur, if task have linear and/or nonlinear constraints.
            */
            template <typename PROBLEM_T>
            void solve_bounds_foas(PROBLEM_T &problem)
            {
                apply_monitoring_parameters();

                auto problem_info = problem.get_problem_info();

                if (problem_info["linear_bounds_declared"] || problem_info["nonlinear_bounds_declared"])
                {
                    std::cout << "Wrong format of the problem for solver e04kf.";
                    return;
                }

                if (problem_info["is_linear"])
                {
                    setup_linobj(problem);
                }
                else
                {
                    setup_nlnobj(problem);
                }

                set_simple_constraints(problem);

                handle_solve_bounds_foas(this->handle, problem.get_objfun(), problem.get_objgrd(), nullptr,
                                         problem.get_initial(), this->rinfo, this->stats, this->opt);
            }

            //! Function for solving problem with explicitly e04mt.
            /*!
                \param problem object of class Problem, containing all information about the task.

                Does not analyze parameters of the problem. Is not recommended for regular usage.
                Errors can occur, if task have nonlinear objective function and/or nonlinear constraints.
            */
            template <typename PROBLEM_T>
            void solve_ip_ipm(PROBLEM_T &problem)
            {
                apply_monitoring_parameters();

                auto problem_info = problem.get_problem_info();

                if (!problem_info["is_linear"] || problem_info["nonlinear_bounds_declared"])
                {
                    std::cout << "Wrong format of the problem for solver e04mt.";
                    return;
                }

                setup_linobj(problem);
                set_simple_constraints(problem);
                set_linear_constraints(problem);

                std::vector<double> u;
                handle_solve_lp_ipm(this->handle, problem.get_initial(), u, this->rinfo, this->stats, nullptr);
            }

            //! Function for solving problem with explicitly e04st.
            /*!
                \param problem object of class Problem, containing all information about the task.

                Does not analyze parameters of the problem. Is not recommended for regular usage.
                Can be ineffective with time and memory.
            */
            template <typename PROBLEM_T>
            void solve_ipopt(PROBLEM_T &problem)
            {
                apply_monitoring_parameters();

                auto problem_info = problem.get_problem_info();

                if (problem_info["is_linear"])
                {
                    setup_linobj(problem);
                }
                else
                {
                    setup_nlnobj(problem);
                }

                set_simple_constraints(problem);
                set_linear_constraints(problem);
                set_nonlinear_constraints(problem);

                std::vector<double> u;
                handle_solve_ipopt(this->handle, problem.get_objfun(), problem.get_objgrd(),
                                   problem.get_confun(), problem.get_congrd(), problem.get_hess(),
                                   nullptr, problem.get_initial(), u, this->rinfo, this->stats, this->opt_st);
            }

            //! Function for calling solvers routines.
            /*!
                \param problem object of class Problem, containing all information about the task.

                Additionally analyses parameters, to choose the most optimal solver.
            */
            template <typename PROBLEM_T>
            void solve(PROBLEM_T &problem)
            {
                apply_monitoring_parameters();

                auto problem_info = problem.get_problem_info();

                bool kf_is_applicable = true; //!< Check, if e04kf can be applied.
                bool mt_is_applicable = true; //!< Check, if e04mt can be applied.

                /*! Row of checks on applicability of different solvers,
                    transferring of parameters to the "handle object" */
                if (problem_info["is_linear"])
                {
                    setup_linobj(problem);
                }
                else
                {
                    setup_nlnobj(problem);

                    mt_is_applicable = false;
                }

                if (problem_info["simple_bounds_declared"])
                {
                    set_simple_constraints(problem);
                }

                if (problem_info["linear_bounds_declared"])
                {
                    set_linear_constraints(problem);

                    kf_is_applicable = false;
                }

                if (problem_info["nonlinear_bounds_declared"])
                {
                    set_nonlinear_constraints(problem);

                    kf_is_applicable = false;
                    mt_is_applicable = false;
                }

                std::vector<double> u; //!< Lagrange multipliers (dual variables).

                //! Calls of the respective solvers.
                if (kf_is_applicable)
                {
                    handle_solve_bounds_foas(this->handle, problem.get_objfun(), problem.get_objgrd(), nullptr, problem.get_initial(), this->rinfo, this->stats, this->opt);
                }
                else if (mt_is_applicable)
                {
                    handle_solve_lp_ipm(this->handle, problem.get_initial(), u, this->rinfo, this->stats, nullptr);
                }
                else
                {
                    handle_solve_ipopt(this->handle, problem.get_objfun(), problem.get_objgrd(),
                                       problem.get_confun(), problem.get_congrd(), problem.get_hess(),
                                       nullptr, problem.get_initial(), u, this->rinfo, this->stats, this->opt_st);
                }
            }

            //! Overload of the output operator.
            /*!
                \param out output stream.
                \param solver object of class solver

                Prints out results of the solving process.
            */
            friend std::ostream &operator<<(std::ostream &out, Solver &solver)
            {
                return out << "\n Monitoring Information: \n"
                           << solver.monitoring_buffer.str() << '\n';
            }
        };
    }
}
