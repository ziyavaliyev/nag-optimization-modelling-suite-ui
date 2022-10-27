// Header for nagcpp::opt::handle_set_linconstr (e04rj)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.5.0.0
#ifndef NAGCPP_E04RJ_HPP
#define NAGCPP_E04RJ_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_set_linconstr (e04rj)
    // Define a block of linear constraints to a problem initialized by
    // opt::handle_init (e04ra).
    // opt::handle_set_linconstr (e04rj) is a part of the NAG optimization
    // modelling suite and adds a new block of linear constraints to the problem or
    // modifies an individual linear constraint.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   bl: double, array, shape(nclin)
    //     bl defines the lower bounds of the linear constraints, l_B
    //   bu: double, array, shape(nclin)
    //     bu defines the upper bounds of the linear constraints, u_B
    //   irowb: types::f77_integer, array, shape(nnzb)
    //     irowb specifies one-based row indices of the nnzb nonzeros of the sparse
    //     matrix B in coordinate storage (CS) format.
    //   icolb: types::f77_integer, array, shape(nnzb)
    //     icolb specifies one-based column indices of the nnzb nonzeros of the
    //     sparse matrix B in coordinate storage (CS) format.
    //   b: double, array, shape(nnzb)
    //     b stores the nnzb nonzeros of the sparse matrix B in coordinate storage
    //     (CS) format.
    //   opt: opt::OptionalE04RJ
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       idlc: types::f77_integer, scalar
    //         Optionally, on entry: if idlc = 0, a new block of linear constraints is
    //         added to the model; otherwise, idlc > 0 refers to the number of an
    //         existing linear constraint which will be replaced and nclin must be set
    //         to one
    //         On exit, if not null on entry: if idlc = 0, the number of the last
    //         linear constraint added
    //         default value: 0
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
    //     On entry, opt.idlc = <value>.
    //     Constraint: opt.idlc >= 0.
    //   (errorid 4)
    //     On entry, opt.idlc = <value>.
    //     The given opt.idlc does not match with any existing linear constraint.
    //     The maximum opt.idlc is <value>.
    //   (errorid 6)
    //     On entry, nnzb = <value>.
    //     Constraint: nnzb >= 0.
    //   (errorid 6)
    //     On entry, nclin = <value>.
    //     Constraint: nclin >= 0.
    //   (errorid 6)
    //     On entry, opt.idlc = <value> and nclin = <value>.
    //     Constraint: If opt.idlc > 0, nclin = 1.
    //   (errorid 8)
    //     On entry, i = <value>, irowb[i-1] = <value> and
    //     nclin = <value>.
    //     Constraint: 1 <= irowb[i-1] <= nclin.
    //   (errorid 8)
    //     On entry, i = <value>, icolb[i-1] = <value> and
    //     n = <value>.
    //     Constraint: 1 <= icolb[i-1] <= n.
    //   (errorid 8)
    //     On entry, more than one element of b has row index <value>
    //     and column index <value>.
    //     Constraint: each element of b must have a unique row and column index.
    //   (errorid 10)
    //     On entry, j = <value>, bl[j-1] = <value> and
    //     bu[j-1] = <value>.
    //     Constraint: bl[j-1] <= bu[j-1].
    //   (errorid 10)
    //     On entry, j = <value>, bl[j-1] = <value>,
    //     bigbnd = <value>.
    //     Constraint: bl[j-1] < bigbnd.
    //   (errorid 10)
    //     On entry, j = <value>, bu[j-1] = <value>,
    //     bigbnd = <value>.
    //     Constraint: bu[j-1] > -bigbnd.
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
#define e04rjft_(en_data, handle, nclin, bl, bu, nnzb, irowb, icolb, b, idlc,  \
                 errbuf, ifail, errbuf_length)                                 \
  E04RJFT(en_data, handle, nclin, bl, bu, nnzb, irowb, icolb, b, idlc, errbuf, \
          errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rjft_ E04RJFT
#else
#define E04RJFT e04rjft_
#endif
    extern void NAG_CALL E04RJFT(
      types::engine_data &en_data, void *handle,
      const types::f77_integer &nclin, const double bl[], const double bu[],
      const types::f77_integer &nnzb, const types::f77_integer irowb[],
      const types::f77_integer icolb[], const double b[],
      types::f77_integer &idlc, char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RJ : public utility::Optional {
    private:
      types::f77_integer idlc_value;

    public:
      OptionalE04RJ() : Optional(), idlc_value(0) {}
      OptionalE04RJ &idlc(types::f77_integer value) {
        idlc_value = value;
        return (*this);
      }
      types::f77_integer get_idlc(void) { return idlc_value; }
      template <typename COMM, typename BL, typename BU, typename IROWB,
                typename ICOLB, typename B>
      friend void handle_set_linconstr(COMM &comm, const BL &bl, const BU &bu,
                                       const IROWB &irowb, const ICOLB &icolb,
                                       const B &b, opt::OptionalE04RJ &opt);
    };

    template <typename COMM, typename BL, typename BU, typename IROWB,
              typename ICOLB, typename B>
    void handle_set_linconstr(COMM &comm, const BL &bl, const BU &bu,
                              const IROWB &irowb, const ICOLB &icolb,
                              const B &b, opt::OptionalE04RJ &opt) {
      opt.fail.prepare("opt::handle_set_linconstr (e04rj)");
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
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<BL>::type>
        local_bl(bl);
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<BU>::type>
        local_bu(bu);
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<IROWB>::type>
        local_irowb(irowb);
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<ICOLB>::type>
        local_icolb(icolb);
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<B>::type>
        local_b(b);

      types::f77_integer local_nclin =
        data_handling::get_size(opt.fail, "nclin", local_bl, 1, local_bu, 1);
      types::f77_integer local_nnzb;
      if (!(static_cast<bool>(local_irowb.data))) {
        local_nnzb = 0;
      } else {
        local_nnzb = data_handling::get_size(opt.fail, "nnzb", local_irowb, 1);
      }
      types::f77_integer local_idlc = opt.idlc_value;

      local_b.check(opt.fail, "b", false, local_nnzb);
      if (opt.fail.error_thrown) {
        return;
      }
      local_icolb.check(opt.fail, "icolb", false, local_nnzb);
      if (opt.fail.error_thrown) {
        return;
      }
      local_irowb.check(opt.fail, "irowb", false, local_nnzb);
      if (opt.fail.error_thrown) {
        return;
      }
      local_bu.check(opt.fail, "bu", false, local_nclin);
      if (opt.fail.error_thrown) {
        return;
      }
      local_bl.check(opt.fail, "bl", false, local_nclin);
      if (opt.fail.error_thrown) {
        return;
      }

      e04rjft_(en_data, &comm.handle, local_nclin, local_bl.data, local_bu.data,
               local_nnzb, local_irowb.data, local_icolb.data, local_b.data,
               local_idlc, opt.fail.errbuf, opt.fail.errorid,
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
          opt.fail.append_msg(false, "The problem cannot be modified right "
                                     "now, the solver is running.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 410) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.idlc = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: opt.idlc >= 0.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 411) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.idlc = ", 1, ".");
          opt.fail.append_msg(true, "The given opt.idlc does not match with "
                                    "any existing linear constraint.");
          opt.fail.append_msg(false, "The maximum opt.idlc is ", 2, ".");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 601) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnzb = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nnzb >= 0.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 611) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nclin = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nclin >= 0.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 612) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.idlc = ", 1,
                              " and nclin = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: If opt.idlc > 0, nclin = 1.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 811) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", irowb[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "nclin = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= irowb[i-1] <= nclin.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 812) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", icolb[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= icolb[i-1] <= n.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 813) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(
            false, "On entry, more than one element of b has row index ", 1);
          opt.fail.append_msg(true, "and column index ", 2, ".");
          opt.fail.append_msg(false, "Constraint: each element of b must have "
                                     "a unique row and column index.");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1001) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bl[j-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "bu[j-1] = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bl[j-1] <= bu[j-1].");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1002) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bl[j-1] = ", 2,
                              ",");
          opt.fail.append_msg(true, "bigbnd = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bl[j-1] < bigbnd.");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1003) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bu[j-1] = ", 2,
                              ",");
          opt.fail.append_msg(true, "bigbnd = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bu[j-1] > -bigbnd.");
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
    template <typename COMM, typename BL, typename BU, typename IROWB,
              typename ICOLB, typename B>
    void handle_set_linconstr(COMM &comm, const BL &bl, const BU &bu,
                              const IROWB &irowb, const ICOLB &icolb,
                              const B &b) {
      opt::OptionalE04RJ local_opt;

      handle_set_linconstr(comm, bl, bu, irowb, icolb, b, local_opt);
    }
  }
}
#define e04rj opt::handle_set_linconstr
#endif