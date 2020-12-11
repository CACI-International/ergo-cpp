# ergo c++

This offers general-purpose c++ compilation and linking for ergo. It offers an
abstraction over groups of c++ files/headers called modules (similar
semantically to c++20 modules), where one module represents (optional) files to
compile as well as headers to expose to interface with the compiled files, and
all dependant modules. Modules are simply ergo maps with specific keys, so
anyone can manually create a module if they want.

## API

This ergo project will attempt to read the environment variables CXX and AR to
determine the c++ compiler and object file archiver to use, and will default to
`c++` and `ar` when each respective variable is absent. It assumes the c++
compiler is also a frontend for linking.

This project evaluates to a map with the following values exposed:

### get-output _config_ _value_
Most of the functions take a context to return the final value. This function
creates and applies the context to a value returned by the other functions. The
keys in `config` are as follows:

* `project-root` (required) - the root directory of the project, used for user-friendly debug
  paths
* `cflags` - an array of global compilation flags to use
* `lflags` - an array of global linking flags to use

Additional keys in `config` are passed in a map to cflags/lflags functions for
`exe`, `dynamic-library`, `static-library`, and `module`.


`value` should be a value returned by `module`, `exe`, `dynamic-library`, or
`static-library`.

The specific values returned once the context is applied are described for each
function.

### module _dir_ _config_
A function for creating a module. Provide a module directory (only used with
"auto" configurations) and a configuration. The configuration may be the string
"auto" for automatic behavior (taking all .cpp and .h files from the given
directory), or it may be a map with the following (optional) keys:

* `files` - an array of the files to compile, or "auto"
* `headers` - an array of the headers to expose, "auto", or a map of directory to
  headers to expose (recursively the same structure)
* `uses` - an array of the modules that this module depends upon
* `cflags` - a function from extra context arguments to an array of extra
  compile flags

This returns a value which should be passed to `get-output`, and will
return a map with the following keys:

* `impl` - an array of compiled object files
* `header-dirs` - an array of header directories exported by the module (including
  inherited directories from dependant modules)
* `header-deps` - a map of header paths to their resolved files
* `runtime` - an array of any additional requirements of the module (inherited
  from dependant modules)

When resolving header dependencies, the compiler will be invoked with
`ERGO_CPP_HEADER_DEPENDS` defined in the preprocessor. If there are any
conditional preprocessing steps that may fail, you may check for this and adjust
logic appropriately.

### exe _config_
Compile a module into an executable. `config` must be a map with the following
keys:

* `name` (required) - the name of the executable
* `module` (required) - the module from which to create an executable
* `cflags` - a function from extra context arguments to an array of extra
  compile flags
* `lflags` - a function from extra context arguments to an array of extra link
  flags

This returns a value which should be passed to `get-output`, and will return a
map with compatible keys for a module as well as the following keys:

* `file` - the compiled executable
* `exec` - a function which will run the executable with `std exec` with the
  runtime appropriately set up


### dynamic-library _config_
Compile a module into a dynamic library. `config` must be a map with the
following keys:

* `name` (required) - the name of the dynamic library
* `module` (required) - the module from which to create a dynamic library
* `cflags` - a function from extra context arguments to an array of extra
  compile flags
* `lflags` - a function from extra context arguments to an array of extra link
  flags

This returns a value which should be passed to `get-output`, and will return a
map with compatible keys for a module as well as the following keys:

* `file` - the compiled dynamic library
* `runtime-if-used` - an array of additional runtime requirements if this
  library is used as an input to other modules


### static-library _config_
Compile a module into a static library. `config` must be a map with the
following keys:

* `name` (required) - the name of the static library
* `module` (required) - the module from which to create a static library
* `cflags` - a function from extra context arguments to an array of extra
  compile flags

The static library will contain all dependant module files. This returns a value
which should be passed to `get-output`, and will return a map with compatible
keys for a module as well as the following keys:

* `file` - the static archive

### target-os
The detected target OS of the toolchain. One of `windows`, `linux`, `mac`, or
`unsupported`.

### name
A map containing functions to create file names for the target OS (adding
appropriate prefixes and suffixes), including:
* `static-library` for static library names
* `dynamic-library` for dynamic library names
* `exe` for executable names

Note that all other functions automatically create appropriate names.
