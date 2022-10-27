#include "e04/nagcpp_class_CommE04RA.hpp"

namespace nagcpp
{
    namespace opt
    {
        //! MonitorOption class.
        /*!
            Contains options of the output.
        */
        class MonitorOption
        {
        private:
            //! Monitoring parameters
            int print_level;
            int foas_print_frequency;
            int monitoring_level;
            bool print_solution;
            bool print_options;
            nagcpp::types::f77_integer monitoring_unit_number;

        public:
            //! Empty constructor.
            MonitorOption()
            {
                //! Definition of basic monitoring parameters.
                monitoring_level = 3;

                print_level = 1;
                print_solution = true;
                print_options = false;
                foas_print_frequency = 5;
            }

            //! Constructor.
            /*!
                \param monitoring_buffer output stream for monitoring.
            */
            MonitorOption(std::stringstream &monitoring_buffer)
            {
                //! Definition of basic monitoring parameters.
                monitoring_unit_number = nagcpp::iomanager::GLOBAL_IOMANAGER->register_ostream(monitoring_buffer);
                monitoring_level = 3;

                print_level = 1;
                print_solution = true;
                print_options = false;
                foas_print_frequency = 5;
            }

            //! Function for setting custom monitoring level.
            /*!
                \param _monitoring_level new monitoring level.
            */
            void set_monitoring_level(int _monitoring_level)
            {
                this->monitoring_level = _monitoring_level;
            }

            //! Function for setting custom print level.
            /*!
                \param _print_level new print level.
            */
            void set_print_level(int _print_level)
            {
                this->print_level = _print_level;
            }

            //! Function for setting custom FOAS print frequency level.
            /*!
                \param _foas_print_frequency new FOAS print frequency.
            */
            void set_foas_print_frequency(int _foas_print_frequency)
            {
                this->foas_print_frequency = _foas_print_frequency;
            }

            //! Function for changing solution printing (ON/OFF).
            /*!
                \param toggle_switch toggle switch for printing the solution part. True - ON, False - OFF.
            */
            void toggle_print_solution(bool toggle_switch)
            {
                this->print_solution = toggle_switch;
            }

            //! Function for changing options printing (ON/OFF).
            /*!
                \param toggle_switch toggle switch for printing the options part. True - ON, False - OFF.
            */
            void toggle_print_options(bool toggle_switch)
            {
                this->print_options = toggle_switch;
            }

            //! Set of get-functions for interaction between Solver and MonitorOption classes.

            //! Get monitoring level.
            auto get_monitoring_level()
            {
                return this->monitoring_level;
            }

            //! Get print level.
            auto get_print_level()
            {
                return this->print_level;
            }

            //! Get FOAS print frequency level.
            auto get_foas_print_frequency()
            {
                return this->foas_print_frequency;
            }

            //! Get indication, if solution part should be printed.
            auto get_print_solution()
            {
                return this->print_solution;
            }

            //! Get indication, if options part should be printed.
            auto get_print_options()
            {
                return this->print_options;
            }

            //! Get number of monitoring unit.
            auto get_monitoring_unit_number()
            {
                return this->monitoring_unit_number;
            }
        };
    }
}
