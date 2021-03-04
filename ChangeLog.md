# ergo-c++ changelog

## 0.7.0  -- TBD
* Update to ergo beta.9.
* Improve type checking and performance using new ergo standard library
  functions.

## 0.6.6  -- 2021-03-02
* Add `object-dump` to the toolchain definition.
* Fix the detection of c++ library and c++ abi.
  * C++ library wasn't always working (depending on cassert include).
  * C++ abi was getting false positives, so the detection file has been
    improved to only use the c preprocessor (which we didn't realize was
    possible before).
* Fix naming of outputs.
  * `exact-name` detection was incorrect.

## 0.6.5  -- 2021-02-11
* Correctly track headers in `header-dirs` output for each module.
  * Previously there was a bug where, if a header was changed, it did not
    consider it different and did not generate a new header directory.
* Add `c-compiler` and `c-compile-flags` to the toolchain in support of building
  external libraries.
* Add `exact-name` to be able to indicate that a target's conventions shouldn't
  be applied to the name of a file.
  * This is more for nice bookkeeping, since you can still always rename the
    file when copying it.

## 0.6.4  -- 2021-02-04
* Allow `compiler` and `archiver` to be specified as paths to binaries

## 0.6.3  -- 2021-02-02
* Use `#include <cassert>` rather than c++20's `#include <version>` in stdlib detection.
* Fix `static-library` functionality.

## 0.6.2  -- 2021-02-01
* Add C++ library and ABI detection keys to the toolchain target map
* Fix linker errors on macOS, which groups everything by default

## 0.6.1  -- 2021-01-27
* Fix deduplication function that broke with syntax changes in ergo 8.
* Deduplicate runtime and impl lists in modules.

## 0.6.0  -- 2021-01-25
* Simplify `headers` and `files` definitions. Remove support for `auto` for
  both, as well as for `module`.
* Add `all-files` and `header-paths` to replace functionality previously built-in
  to `module`.

## 0.5.1  -- 2021-01-25
* Allow headers to be plain strings (to be interpreted as relative paths).

## 0.5.0  -- 2021-01-21
* Toolchains to be used are now parameterized.
  * Use `toolchain` to create a toolchain from a configuration, and pass it into
    `get-output`.
  * The previous `target` functions are now in the produced toolchain.
* Add `env-toolchain` to get a toolchain based on the environment.
* Update to ergo beta.8.
* Use a `Module` type for c++ modules.
* Allow paths in `files` and `headers` to be relative. Do not require specifying
  the relative directory (it will default to the executing script's directory),
  though it can be set with the non-positional argument `relative-dir` to the
  `module` function.

## 0.4.0  -- 2020-12-11
* Fix bug with compiler invocation for header tracking.
  * The invocation did not pass the PATH environment variable, which breaks
    e.g. ccache.
* Improve task behavior (ergo >= beta.6).
* Add a preprocessor value (`ERGO_CPP_HEADER_DEPENDS`) when checking header dependencies.
  * This allows code to avoid problematic preprocessor directives.
* Change functions to take named arguments.
* Support setting cflags directly on modules.

## 0.3.2  -- 2020-11-20
* Fix bug with file names and `target-os`.

## 0.3.1  -- 2020-11-18
* Fix export bug for naming functions.

## 0.3.0  -- 2020-11-17
* Update for ergo 1.0.0-beta.4.
* With new features from the latest ergo, add header tracking.
* Support header layout descriptions.

## 0.2.1  -- 2020-10-23
* Support ccache and fix the invocation to detect the target os.
* Improve how runtime file dependencies are linked.
* Expose some of the internally-derived values like target-os and the name conventions.

## 0.2.0  -- 2020-10-07
* Update for ergo 1.0.0-beta.2.
* Change `context` function to `apply-context`.

## 0.1.0  -- 2020-09-21
* Initial release of the module.
