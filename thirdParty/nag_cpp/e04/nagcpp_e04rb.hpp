// Header for nagcpp::opt::handle_set_group (e04rb)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.5.0.0
#ifndef NAGCPP_E04RB_HPP
#define NAGCPP_E04RB_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_set_group (e04rb)
    // Define a set of variables which form a second-order cone to a problem
    // initialized by opt::handle_init (e04ra).
    // opt::handle_set_group (e04rb) is a part of the NAG optimization modelling
    // suite and modifies a model by either adding a new, or replacing, or deleting
    // an existing quadratic or rotated quadratic cone constraint.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   gtype: std::string, scalar
    //     The type of the cone constraint
    //   group: types::f77_integer, array, shape(lgroup)
    //     G^i, the indices of the variables in the constraint
    //   idgroup: types::f77_integer, scalar
    //     On entry:
    //     idgroup = 0
    //     A new cone constraint is created
    //     idgroup > 0
    //     i, the ID number of the existing constraint to be deleted or replaced
    //     On exit: if idgroup = 0 on entry, the ID number of the new cone constraint
    //     is returned
    //   opt: opt::OptionalE04RB
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     comm.handle has not been initialized.
    //   (errorid 1)
    //     comm.handle does not belong to the NAG optimization modelling suite,
    //     has not been initialized properly or is corrupted.
    //   (errorid 1)
    //     comm.handle has not been initialized properly or is corrupted.
    //   (errorid 2)
    //     The problem cannot be modified right now, the solver is running.
    //   (errorid 4)
    //     On entry, idgroup = <value>.
    //     The given idgroup does not match with any cone constraint already defined.
    //   (errorid 5)
    //     On entry, lgroup = <value>.
    //     Constraint: lgroup >= 0.
    //   (errorid 5)
    //     On entry, gtype = <value> and lgroup = <value>.
    //     Constraint: if gtype = "QUAD" or "Q", lgroup = 0 or lgroup >= 2.
    //   (errorid 5)
    //     On entry, gtype = <value> and lgroup = <value>.
    //     Constraint: if gtype = "RQUAD" or "R", lgroup = 0 or lgroup >= 3.
    //   (errorid 6)
    //     On entry, gtype = <value>.
    //     Constraint: gtype = "QUAD", "Q", "RQUAD" or "R".
    //   (errorid 7)
    //     On entry, idgroup = <value>.
    //     Constraint: idgroup >= 0.
    //   (errorid 8)
    //     On entry, k = <value>, group[k-1] = <value> and
    //     n = <value>.
    //     Constraint: 1 <= group[k-1] <= n.
    //   (errorid 9)
    //     On entry, group[i-1] = group[j-1] = <value>
    //     for i = <value> and j = <value>.
    //     Constraint: elements in group cannot repeat.
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
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define e04rbft_(en_data, handle, gtype, lgroup, group, idgroup, errbuf, \
                 ifail, gtype_length, errbuf_length)                     \
  E04RBFT(en_data, handle, gtype, gtype_length, lgroup, group, idgroup,  \
          errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rbft_ E04RBFT
#else
#define E04RBFT e04rbft_
#endif
    extern void NAG_CALL E04RBFT(
      types::engine_data &en_data, void *handle,
      const char *gtype NAG_STDCALL_LEN(gtype_length),
      const types::f77_integer &lgroup, const types::f77_integer group[],
      types::f77_integer &idgroup, char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(gtype_length)
        NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RB : public utility::Optional {
    public:
      OptionalE04RB() : Optional() {}
      template <typename COMM, typename GROUP>
      friend void handle_set_group(COMM &comm, const std::string gtype,
                                   const GROUP &group,
                                   types::f77_integer &idgroup,
                                   opt::OptionalE04RB &opt);
    };

    template <typename COMM, typename GROUP>
    void handle_set_group(COMM &comm, const std::string gtype,
                          const GROUP &group, types::f77_integer &idgroup,
                          opt::OptionalE04RB &opt) {
      opt.fail.prepare("opt::handle_set_group (e04rb)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
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
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<GROUP>::type>
        local_group(group);

      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_gtype(gtype);
      types::f77_integer local_lgroup;
      if (!(static_cast<bool>(local_group.data))) {
        local_lgroup = 0;
      } else {
        local_lgroup =
          data_handling::get_size(opt.fail, "lgroup", local_group, 1);
      }

      local_group.check(opt.fail, "group", false, local_lgroup);
      if (opt.fail.error_thrown) {
        return;
      }

      e04rbft_(en_data, &comm.handle, local_gtype.data, local_lgroup,
               local_group.data, idgroup, opt.fail.errbuf, opt.fail.errorid,
               local_gtype.string_length, opt.fail.errbuf_length);

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
          opt.fail.append_msg(false, "The problem cannot be modified right "
                                     "now, the solver is running.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 401) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, idgroup = ", 1, ".");
          opt.fail.append_msg(false, "The given idgroup does not match with "
                                     "any cone constraint already defined.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 501) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, lgroup = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: lgroup >= 0.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 502) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, gtype = ", 1,
                              " and lgroup = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: if gtype = \"QUAD\" or "
                                     "\"Q\", lgroup = 0 or lgroup >= 2.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 503) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, gtype = ", 1,
                              " and lgroup = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: if gtype = \"RQUAD\" or "
                                     "\"R\", lgroup = 0 or lgroup >= 3.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 601) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, gtype = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: gtype = \"QUAD\", \"Q\", "
                                     "\"RQUAD\" or \"R\".");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 701) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, idgroup = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: idgroup >= 0.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 801) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, k = ", 1, ", group[k-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= group[k-1] <= n.");
        } else if (opt.fail.ierr == 9 && opt.fail.ifmt == 901) {
          opt.fail.set_errorid(9, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, group[i-1] = group[j-1] = ", 1);
          opt.fail.append_msg(true, "for i = ", 2, " and j = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: elements in group cannot "
                                     "repeat.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM, typename GROUP>
    void handle_set_group(COMM &comm, const std::string gtype,
                          const GROUP &group, types::f77_integer &idgroup) {
      opt::OptionalE04RB local_opt;

      handle_set_group(comm, gtype, group, idgroup, local_opt);
    }
  }
}
#define e04rb opt::handle_set_group
#endif
