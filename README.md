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
`c++` and `ar` when each respective variable is absent.

This project evaluates to a map/module with the following values exposed.

### apply-context _project-root_ _cflags_ _lflags_ _value_
Most of the functions take a context to return the final value. This function
creates and applies the context to a value returned by the other functions. The
arguments are as follows:

* project-root - the root directory of the project, used for user-friendly debug
  paths
* cflags - an array of global compilation flags to use
* lflags - an array of global linking flags to use
* value - a value returned by `module`, `exe`, `dynamic-library`, or
  `static-library`

The specific values returned once the context is applied are described for each
function.

### module _dir_ _config_
A function for creating a module. Provide a module directory (only used with
"auto" configurations) and a configuration. The configuration may be the string
"auto" for automatic behavior (taking all .cpp and .h files from the given
directory), or it may be a map with the following (optional) keys:

* files - an array of the files to compile, or "auto"
* headers - an array of the headers to expose, or "auto"
* uses - an array of the modules that this module depends upon

This returns a value which should be passed to the context function, and will
return a map with the following keys:

* impl - an array of compiled object files
* header-dirs - an array of header directories exported by the module (including
  inherited directories from dependant modules)
* runtime - an array of any additional requirements of the module (inherited
  from dependant modules)


### exe _name_ _mod_
Compile a module into an executable. The name is mainly used for making readable
debug info. Additional keyword arguments `cflags` and `lflags` may be used to
add flags for all files compiled and linked for this executable. This returns a
value which should be passed to the context function, and will return a map with
compatible keys for a module as well as the following keys:

* file - the compiled executable
* exec - a function which will run the executable with `std exec` with the
  runtime appropriately set up


### dynamic-library _name_ _mod_
Compile a module into a dynamic library. The name is mainly used for making
readable debug info. Additional keyword arguments `cflags` and `lflags` may be
used to add flags for all files compiled and linked for this dynamic library.
This returns a value which should be passed to the context function, and will
return a map with compatible keys for a module as well as the following keys:

* file - the compiled dynamic library
* runtime-if-used - an array of additional runtime requirements if this library
  is used as an input to other modules


### static-library _name_ _mod_
Compile a module into a static library. The name is mainly used for making
readable debug info. Additional keyword argument `cflags` may be used to add
flags for all files compiled for this static library. The static library will
contain all dependant module files. This returns a value which should be passed
to the context function, and will return a map with compatible keys for a module
as well as the following keys:

* file - the static archive
