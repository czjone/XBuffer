#ifndef XBUFFER_COMMAND_ANALYZER_HPP
#define XBUFFER_COMMAND_ANALYZER_HPP 1
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

namespace XBF
{
using std::string;
using std::vector;

/// Data structure of a program option
struct Option
{
    char type;        // type of option
    char letter;      // single-letter label of an option
    string name;      // long name of an option
                      //	char valtype;  // value type, [BSID], bool: B, string: S, int: I, double: D
    string value_str; // option value as a string
    union {           // option value as a bool, int or double value
        bool value_bool;
        int value_int;
        double value_double;
    };
    string desc; // a short sentence to describe an option
    string meta; // a META word to specify the type of option argument, such as "FILE", "SIZE"

    Option() : type(0), letter(), name(), value_str(), value_double(0.0), desc(), meta() {}
    bool set_value(const char *opt_value);
    bool set_desc_meta(const char *opt_desc);
};

/// Use this class to define program options and parse command line arguments.
class CommandAnalyzer
{
public:
    /// Construct a Anyarg object.
    CommandAnalyzer();

    //@{
    /**
	Add a boolean flag to a program.
	@param name   Long name of a flag. Using hypen to connect multiple words, such as "buffer-size".
	@param letter Single-letter label of a flag, such as 'i'. Set letter to 0 (not '0') if you do not need a short label.
	@param desc   Description of a flag, which will be used to generate usage. Set desc as "" if nothing to say.
	@return       \c true if success, \c false if the flag has been defined.
	@note The default value of flag is \c false.
	*/
    bool add_flag(const char *name, char letter, const char *desc);
    bool add_flag(char letter, const char *desc);
    //@}

    //@{
    /**
	Add a taking-value option to a program.
	@param name   Long name of a flag. Using hypen to connect multiple words, such as "buffer-size".
	@param letter Single-letter label of a flag, such as 'i'. Set letter to 0 if you do not need a short label.
	@param v0     The default value of this option.
	@param desc   Description of a flag, which will be used to generate usage. Set \c desc as "" if nothing to say.
	              If description starts with an \c = (like: "=FILE Name of output file"), the word followed will be treated as
	              a META word, which will be used in the generation of option usage, e.g.: "-f FILE, --filename=FILE".
	@return       \c true if success, \c false if the flag has been defined.
	*/
    // Add an option with a string value
    bool add_option_str(const char *name, char letter, const char *v0, const char *desc);
    bool add_option_str(char letter, const char *v0, const char *desc);

    // Add an option with an integer value
    bool add_option_int(char letter, int v0, const char *desc);
    bool add_option_int(const char *name, char letter, int v0, const char *desc);

    // Add an option with an double value
    bool add_option_double(char letter, double v0, const char *desc);
    bool add_option_double(const char *name, char letter, double v0, const char *desc);
    //@}

    /**
	Parse command line arguments.
	@pre         Flags and options have to be defined by add_flag() and add_option_xxx() before the parsing of command line.
	@param argc  The number of arguments in command line.
	@param argv  Array including all command line arugments.
	@return      \c true if success, \c false if fail.
	@note        The frist elements of \c argv MUST be the name of the program.
	*/
    bool parse_argv(int argc, char **argv);

    //@{
    /**
	Check whether a flag is set to true in the command line.
	@param name   The same name used in add_flag().
	@param letter Single-letter label of a flag.
	@return       \c true if a flag is set in command line, \c false if not.
	*/
    bool is_true(const char *name) const;
    bool is_true(char letter) const;
    //@}

    //@{
    /**
	Get option value.
	@param name   The same name used in add_option_xxx().
	@param letter Single-letter label of a flag, such as 'i'.
	@return       The value of an option. If the value is not assigned in command line, the default value will be returned.
	@note         get_value functions should match with add_option functions. Use get_value_str(), get_value_int(),
	              get_value_double() to get the value of an option whose value is of type string, int and double, respectively.	
	*/
    // Get the value of an option with string values
    const char *get_value_str(const char *name) const;
    const char *get_value_str(char letter) const;

    // Get the value of an option with integer values
    int get_value_int(const char *name) const;
    int get_value_int(char letter) const;

    // Get the value of an option with double values
    double get_value_double(const char *name) const;
    double get_value_double(char letter) const;
    //@}

    /**
	Get the number of non-option arguments.
	@return The count of non-option arguments.
	*/
    int get_argc() const;

    /**
	Get a non-option argument by index
	@param i The index of a non-option arguments, ranging from 0 to get_argc() - 1.
	Non-option arguments are in the same order as they appeared in command line.
	*/
    const char *get_arg(int i) const;

    /**
	Generate well-formatted usage information for options defined for the program.
	@return Usage information as a c-string.
	*/
    const char *auto_usage();

private:
    string prog_name_;    // name of the program
    int argc_;            // count of non-option arguments
    vector<string> argv_; // vector of non-option arguments

    vector<Option> options_; // vector of options

    string help_; // formatted help for options

    CommandAnalyzer(const CommandAnalyzer &); // prevent the copy of a anyarg object

    CommandAnalyzer &operator=(const CommandAnalyzer &); // prevent assignment of anyarg object

    bool is_new_option(const char *name, char letter);

    int get_optind(char letter) const;

    int get_optind(const char *name) const;

    // Show information of all options, for debugging.
    void show_options() const;
};
} // namespace XBF

#endif