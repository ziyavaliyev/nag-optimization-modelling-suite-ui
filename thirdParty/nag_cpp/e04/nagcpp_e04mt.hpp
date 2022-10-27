// Header for nagcpp::opt::handle_solve_lp_ipm (e04mt)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.5.0.0
#ifndef NAGCPP_E04MT_HPP
#define NAGCPP_E04MT_HPP

#include "utility/nagcpp_callback_handling.hpp"
#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_macros.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include "utility/nagcpp_utility_print_rec.hpp"

namespace nagcpp {
  namespace opt {
    // handle_solve_lp_ipm (e04mt)
    // Linear programming (LP), sparse, interior point method (IPM).
    // Note: this function uses optional algorithmic parameters, see also:
    // opt::handle_opt_set (e04zm), opt::handle_opt_get (e04zn).
    // opt::handle_solve_lp_ipm (e04mt) is a solver from the NAG optimization
    // modelling suite for large-scale Linear Programming (LP) problems based on an
    // interior point method (IPM).

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   x: double, array, shape(nvar)
    //     Optionally, on entry: the input of x is reserved for future releases of
    //     the NAG Library and it is ignored at the moment.
    //     On exit, if not null on entry: the final values of the variables x
    //   u: double, array, shape(nnzu)
    //     Note: if nnzu > 0, u holds Lagrange multipliers (dual variables) for the
    //     bound constraints and linear constraints.
    //     Optionally, on entry: the input of u is reserved for future releases of
    //     the NAG Library and it is ignored at the moment.
    //     On exit, if not null on entry: the final values of the variables u
    //   rinfo: double, array, shape(100)
    //     On exit, if not null on entry: error measures and various indicators of
    //     the algorithm (see Algorithmic Details for details)
    //   stats: double, array, shape(100)
    //     On exit, if not null on entry: solver statistics
    //   monit: void, function
    //     monit is provided to enable you to monitor the progress of the optimization

    //     parameters:
    //       comm: opt::CommE04RA
    //         Communication structure.
    //       rinfo: double, array, shape(100)
    //         Error measures and various indicators at the end of the current
    //         iteration as described in rinfo
    //       stats: double, array, shape(100)
    //         Solver statistics at the end of the current iteration as described in
    //         stats, however, elements 2, 3, 5, 9, 10, 11 and 15 refer to the
    //         quantities in the last iteration rather than accumulated over all
    //         iterations through the whole algorithm run
    //   opt: opt::OptionalE04MT
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // other parameters:
    //   Defaults: valueless
    //     This special keyword may be used to reset all options to their default
    //     values
    //   Infinite Bound Size: double
    //     Default = 10^20
    //     This defines the "infinite" bound bigbnd in the definition of the problem
    //     constraints
    //   LP Presolve: char
    //     Default = "FULL"
    //     This parameter allows you to reduce the level of presolving of the problem
    //     or turn it off completely
    //   LPIPM Algorithm: char
    //     Default = "PRIMAL-DUAL"
    //     As described in Algorithmic Details, opt::handle_solve_lp_ipm (e04mt)
    //     implements the infeasible Primal-Dual algorithm, see The
    //     Infeasible-interior-point Primal-Dual Algorithm, and the homogeneous
    //     Self-Dual algorithm, see Homogeneous Self-Dual Algorithm
    //   LPIPM Centrality Correctors: types::f77_integer
    //     Default = 6
    //     This parameter controls the number of centrality correctors (see Weighted
    //     Multiple Centrality Correctors) used at each iteration
    //   LPIPM Iteration Limit: types::f77_integer
    //     Default = 100
    //     The maximum number of iterations to be performed by
    //     opt::handle_solve_lp_ipm (e04mt)
    //   LPIPM Max Iterative Refinement: types::f77_integer
    //     Default = 5
    //     This parameter controls the maximum number of iterative refinement
    //     iterations (see Solving the KKT System) used at each main iteration when
    //     "LPIPM System Formulation" = "Normal Equations"
    //   LPIPM Scaling: char
    //     Default = "ARITHMETIC"
    //     This parameter controls the type of scaling to be applied on the
    //     constraint matrix A before solving the problem
    //   LPIPM Monitor Frequency: types::f77_integer
    //     Default = 0
    //     This parameter defines the frequency of how often function monit is called
    //   LPIPM Stop Tolerance: double
    //     Default = sqrt(epsilon)
    //     This parameter sets the value epsilon_1 which is the tolerance for the
    //     convergence measures in the stopping criteria, see Stopping Criteria
    //   LPIPM Stop Tolerance 2: double
    //     Default = epsilon^0.6
    //     This parameter sets the additional tolerance epsilon_2 used in the
    //     stopping criteria for the Self-Dual algorithm, see Stopping Criteria
    //   LPIPM System Formulation: char
    //     Default = "AUTO"
    //     As described in Solving the KKT System, opt::handle_solve_lp_ipm (e04mt)
    //     can internally work either with the normal equations formulation
    //     [equation] or with the augmented system [equation]
    //   Monitoring File: types::f77_integer
    //     Default = -1
    //     If i >= 0, the unit number for the secondary (monitoring) output
    //   Monitoring Level: types::f77_integer
    //     Default = 4
    //     This parameter sets the amount of information detail that will be printed
    //     by the solver to the secondary output
    //   Print File: types::f77_integer
    //     Default = advisory message unit number
    //     If i >= 0, the unit number for the primary output of the solver
    //   Print Level: types::f77_integer
    //     Default = 2
    //     This parameter defines how detailed information should be printed by the
    //     solver to the primary output
    //   Print Options: char
    //     Default = "YES"
    //     If "Print Options" = "YES", a listing of options will be printed to the
    //     primary and secondary output
    //   Print Solution: char
    //     Default = "NO"
    //     If "Print Solution" = "X", the final values of the primal variables are
    //     printed on the primary and secondary outputs
    //   Stats Time: char
    //     Default = "NO"
    //     This parameter allows you to turn on timings of various parts of the
    //     algorithm to give a better overview of where most of the time is spent
    //   Task: char
    //     Default = "MINIMIZE"
    //     This parameter specifies the required direction of the optimization

    // error_handler::ErrorException
    //   (errorid 1)
    //     comm.handle has not been initialized.
    //   (errorid 1)
    //     comm.handle does not belong to the NAG optimization modelling suite,
    //     has not been initialized properly or is corrupted.
    //   (errorid 1)
    //     comm.handle has not been initialized properly or is corrupted.
    //   (errorid 2)
    //     This solver does not support the model defined in the handle.
    //   (errorid 2)
    //     The problem is already being solved.
    //   (errorid 4)
    //     On entry, nvar = <value>,
    //     expected value = <value>.
    //     Constraint: nvar must match the current number of variables
    //     of the model in the comm.handle.
    //   (errorid 5)
    //     On entry, nnzu = <value>.
    //     nnzu does not match the size of the Lagrangian multipliers
    //     for constraints.
    //     The correct value is either 0 or <value>.
    //   (errorid 5)
    //     On entry, nnzu = <value>.
    //     nnzu does not match the size of the Lagrangian multipliers
    //     for constraints.
    //     The correct value is 0 for no constraints.
    //   (errorid 51)
    //     The problem was found to be primal infeasible.
    //   (errorid 52)
    //     The problem was found to be dual infeasible.
    //   (errorid 53)
    //     The problem seems to be primal or dual infeasible,
    //     the algorithm was stopped.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument was a vector of size <value>.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     The size for the supplied array could not be ascertained.
    //   (errorid 10602)
    //     On entry, the raw data component of <value> is null.
    //   (errorid 10603)
    //     On entry, unable to ascertain a value for <value>.
    //   (errorid 10605)
    //     On entry, the communication class <value> has not been initialized
    //     correctly.
    //   (errorid 10703)
    //     An exception was thrown during IO (writing).
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::CallbackEarlyTermination
    //   (errorid 20)
    //     User requested termination during a monitoring step.

    // error_handler::WarningException
    //   (errorid 22)
    //     Maximum number of iterations exceeded.
    //   (errorid 24)
    //     No progress, stopping early.
    //   (errorid 50)
    //     Suboptimal solution.

    // error_handler::CallbackException
    //   (errorid 10701)
    //     An exception was thrown in a callback.
    //   (errorid 10702)
    //     The memory address for an array in a callback has changed.

    extern "C" {
#ifndef E04MTFT_MONIT
#define E04MTFT_MONIT                                                     \
  std::function<void(                                                     \
    const data_handling::CallbackAddresses *, types::engine_data &,       \
    opt::CommE04RA &,                                                     \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &, \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &)>
#endif

#ifndef E04MTFT_MONITH
#define E04MTFT_MONITH                                                         \
  void(NAG_CALL * monith)(const E04MTFT_MONIT &, types::engine_data &, void *, \
                          const double[], const double[], void *, void *,      \
                          types::f77_integer &)
#endif

#if defined(_WIN32) && defined(USE_STDCALL)
#define e04mtft_(en_data, print_rec, print_rech, handle, nvar, x, nnzu, u, \
                 rinfo, stats, monit, monith, iuser, ruser, errbuf, ifail, \
                 errbuf_length)                                            \
  E04MTFT(en_data, print_rec, print_rech, handle, nvar, x, nnzu, u, rinfo, \
          stats, monit, monith, iuser, ruser, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04mtft_ E04MTFT
#else
#define E04MTFT e04mtft_
#endif
    extern void NAG_CALL E04MTFT(
      types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
      void *handle, const types::f77_integer &nvar, double x[],
      const types::f77_integer &nnzu, double u[], double rinfo[],
      double stats[], const E04MTFT_MONIT &, E04MTFT_MONITH, void *iuser,
      void *ruser, char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04MT : public utility::Optional {
    public:
      OptionalE04MT() : Optional() {}
      template <typename COMM, typename X, typename U, typename RINFO,
                typename STATS, typename MONIT>
      friend void handle_solve_lp_ipm(COMM &comm, X &&x, U &&u, RINFO &&rinfo,
                                      STATS &&stats, MONIT &&monit,
                                      opt::OptionalE04MT &opt);
    };

    void e04mt_monith(const E04MTFT_MONIT &monit, types::engine_data &en_data,
                      void *handle, const double *rinfo, const double *stats,
                      void *iuser, void *ruser, types::f77_integer &inform) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      opt::CommE04RA local_comm(handle);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_rinfo(
        rinfo, 100);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_stats(
        stats, 100);
      data_handling::CallbackAddresses *callbacks =
        static_cast<data_handling::CallbackAddresses *>(en_data.wrapptr2);

      try {
        monit(callbacks, en_data, local_comm, local_rinfo, local_stats);

      } catch (const error_handler::CallbackEarlyTermination &e) {
        // user threw an early termination exception
        NAG_UNUSED_PARAMETER(e);
        en_data.hlperr = 0;
        inform = -1;
        ep->eptr = std::current_exception();

      } catch (...) {
        // callback threw an exception
        en_data.hlperr = error_handler::HLPERR_USER_EXCEPTION;
        ep->eptr = std::current_exception();
      }

      if ((rinfo != local_rinfo.data()) && (stats != local_stats.data())) {
        // address of an array changed
        en_data.hlperr = error_handler::HLPERR_ARRAY_POINTER_CHANGED;
        return;
      }
    }

    template <typename MONIT_RINFO, typename MONIT_STATS, typename MONIT>
    struct e04mt_monit_cs {
      static void
        run(const data_handling::CallbackAddresses *callbacks,
            types::engine_data &en_data, opt::CommE04RA &comm,
            const utility::array1D<double, data_handling::ArgIntent::IntentIN>
              &rinfo,
            const utility::array1D<double, data_handling::ArgIntent::IntentIN>
              &stats) {
        MONIT &monit =
          *((typename std::remove_reference<MONIT>::type *)(*callbacks)
              .address[0]);

        auto local_rinfo = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, MONIT_RINFO>(rinfo);
        auto local_stats = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, MONIT_STATS>(stats);

        monit(comm, local_rinfo.get(), local_stats.get());
      }
    };

    template <>
    struct e04mt_monit_cs<std::nullptr_t, std::nullptr_t, std::nullptr_t> {
      static void
        run(const data_handling::CallbackAddresses *callbacks,
            types::engine_data &en_data, opt::CommE04RA &comm,
            const utility::array1D<double, data_handling::ArgIntent::IntentIN>
              &rinfo,
            const utility::array1D<double, data_handling::ArgIntent::IntentIN>
              &stats) {
        return;
      }
    };

    template <typename COMM, typename X, typename U, typename RINFO,
              typename STATS, typename MONIT>
    void handle_solve_lp_ipm(COMM &comm, X &&x, U &&u, RINFO &&rinfo,
                             STATS &&stats, MONIT &&monit,
                             opt::OptionalE04MT &opt) {
      opt.fail.prepare("opt::handle_solve_lp_ipm (e04mt)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      error_handler::ExceptionPointer ep;
      en_data.wrapptr1 = &ep;
      static_assert(std::is_same<COMM, utility::NoneCopyableComm>::value ||
                      std::is_same<COMM, opt::CommE04RA>::value,
                    "Invalid type for comm: must be either "
                    "utility::NoneCopyableComm or opt::CommE04RA");
      if (!(comm.check())) {
        opt.fail.raise_error_comm_invalid("comm");
        if (opt.fail.error_thrown) {
          return;
        }
      }
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<X>::type>
        local_x(x);
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<U>::type>
        local_u(u);
      data_handling::CallbackAddresses callbacks(1);
      en_data.wrapptr2 = static_cast<void *>(std::addressof(callbacks));
      callbacks.address[0] = callback_handling::function_to_void_pointer(monit);

      void *local_print_rec = static_cast<void *>(&opt.iomanager);
      types::f77_integer vl_e04pta_nvar;
      types::f77_integer vl_e04pta_nnzu;
      types::f77_integer vl_e04pta_nnzuc;
      types::f77_integer vl_e04pta_nnzua;
      types::f77_integer vl_e04pta_ifail;
      engine_routines::e04ptan_(&comm.handle, vl_e04pta_nvar, vl_e04pta_nnzu,
                                vl_e04pta_nnzuc, vl_e04pta_nnzua,
                                vl_e04pta_ifail);

      if (!(local_x.data)) {
        local_x.resize(x, vl_e04pta_nvar);
      }
      if (!(local_u.data)) {
        local_u.resize(u, vl_e04pta_nnzu);
      }
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<RINFO>::type>
        local_rinfo(rinfo);
      local_rinfo.resize(rinfo, static_cast<types::f77_integer>(100));
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<STATS>::type>
        local_stats(stats);
      local_stats.resize(stats, static_cast<types::f77_integer>(100));
      using local_monit_rinfo_t = callback_handling::get_argument_type_t<
        1, callback_handling::argument_type_of_t<
             typename std::remove_reference<MONIT>::type>>;
      using local_monit_stats_t = callback_handling::get_argument_type_t<
        2, callback_handling::argument_type_of_t<
             typename std::remove_reference<MONIT>::type>>;
      auto local_monit =
        e04mt_monit_cs<local_monit_rinfo_t, local_monit_stats_t,
                       typename std::remove_reference<MONIT>::type>::run;
      void *local_iuser = nullptr;
      void *local_ruser = nullptr;

      local_stats.check(opt.fail, "stats", true,
                        static_cast<types::f77_integer>(100));
      if (opt.fail.error_thrown) {
        return;
      }
      local_rinfo.check(opt.fail, "rinfo", true,
                        static_cast<types::f77_integer>(100));
      if (opt.fail.error_thrown) {
        return;
      }
      local_u.check(opt.fail, "u", true, vl_e04pta_nnzu);
      if (opt.fail.error_thrown) {
        return;
      }
      if (!(local_u.data)) {
        vl_e04pta_nnzu = 0;
      }
      local_x.check(opt.fail, "x", true, vl_e04pta_nvar);
      if (opt.fail.error_thrown) {
        return;
      }

      e04mtft_(en_data, local_print_rec, utility::print_rech, &comm.handle,
               vl_e04pta_nvar, local_x.data, vl_e04pta_nnzu, local_u.data,
               local_rinfo.data, local_stats.data, local_monit, e04mt_monith,
               local_iuser, local_ruser, opt.fail.errbuf, opt.fail.errorid,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 100) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle has not been initialized.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 101) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle does not belong to the NAG "
                                     "optimization modelling suite,");
          opt.fail.append_msg(false, "has not been initialized properly or is "
                                     "corrupted.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 102) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle has not been initialized "
                                     "properly or is corrupted.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 201) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "This solver does not support the model "
                                     "defined in the handle.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 202) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The problem is already being solved.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 401) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, nvar = ", 1, ",");
          opt.fail.append_msg(true, "expected value = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: nvar must match the current "
                                     "number of variables");
          opt.fail.append_msg(false, "of the model in the comm.handle.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 502) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnzu = ", 1, ".");
          opt.fail.append_msg(false, "nnzu does not match the size of the "
                                     "Lagrangian multipliers");
          opt.fail.append_msg(true, "for constraints.");
          opt.fail.append_msg(false, "The correct value is either 0 or ", 2,
                              ".");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 503) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnzu = ", 1, ".");
          opt.fail.append_msg(false, "nnzu does not match the size of the "
                                     "Lagrangian multipliers");
          opt.fail.append_msg(true, "for constraints.");
          opt.fail.append_msg(false, "The correct value is 0 for no "
                                     "constraints.");
        } else if (opt.fail.ierr == 20) {
          opt.fail.set_errorid(20, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "User requested termination during a "
                                     "monitoring step.");
          opt.fail.append_exception_msg(en_data);
        } else if (opt.fail.ierr == 22) {
          opt.fail.set_errorid(22, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Maximum number of iterations exceeded.");
        } else if (opt.fail.ierr == 24) {
          opt.fail.set_errorid(24, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "No progress, stopping early.");
        } else if (opt.fail.ierr == 50) {
          opt.fail.set_errorid(50, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Suboptimal solution.");
        } else if (opt.fail.ierr == 51) {
          opt.fail.set_errorid(51, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The problem was found to be primal "
                                     "infeasible.");
        } else if (opt.fail.ierr == 52) {
          opt.fail.set_errorid(52, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The problem was found to be dual "
                                     "infeasible.");
        } else if (opt.fail.ierr == 53) {
          opt.fail.set_errorid(53, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The problem seems to be primal or dual "
                                     "infeasible,");
          opt.fail.append_msg(false, "the algorithm was stopped.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_x.copy_back(x);
      local_u.copy_back(u);
      local_rinfo.copy_back(rinfo);
      local_stats.copy_back(stats);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM, typename X, typename U, typename RINFO,
              typename STATS, typename MONIT>
    void handle_solve_lp_ipm(COMM &comm, X &&x, U &&u, RINFO &&rinfo,
                             STATS &&stats, MONIT &&monit) {
      opt::OptionalE04MT local_opt;

      handle_solve_lp_ipm(comm, x, u, rinfo, stats, monit, local_opt);
    }
  }
}
#define e04mt opt::handle_solve_lp_ipm
#endif
