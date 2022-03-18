# ergo-c++ changelog

## 0.11.10  -- 2022-03-18
* Change header dependency checks to be run as tasks (mainly to limit
  concurrency, but also to illuminate what's going on to users).
* Don't run header dependency checks on headers themselves when
  `include-dependencies` is `accurate` (the default), as it is unnecessary in
  that case: that information is only used to reconstruct missing dependencies,
  which only happens in `relaxed` mode.
* XXX: Since 0.11.7, public/private header dependency checking has been broken
  (since it relied on headers not resolving). In general the dependency checking
  should be refactored to make it more consistent and enable better features.

## 0.11.9  -- 2022-03-09
* Use `LD_LIBRARY_PATH` rather than `LD_PRELOAD` for `exec-output` on linux, as
  this interacts better with llvm-symbolizer (used by sanitizers).
  * Previously we favored `LD_PRELOAD` because it avoids caring about file
    SONAMEs, but we've long had the runtime (e.g. abi symlinks) as part of the
    files so it shouldn't be an issue.

## 0.11.8  -- 2022-02-18
* Add a `runtime-direct` field to linked modules to indicate the direct runtime
  dependencies (excluding secondary dependencies).

## 0.11.7  -- 2022-02-16
* Properly set the `runtime-if-used` field for `compiled-module`s based on the
  link arguments.
* Use the full includes when determining header dependencies.
  * In general this will behave better for weird header shenanigans, at the cost
    of possibly forcing dependent headers to be evaluated and accessible.
  * Add an `include-dependencies` option which can be used to revert behavior to
    the old method.

## 0.11.6  -- 2022-01-13
* Correctly handle windows env variable path separators.
* Revert the 0.11.4 change as it causes unacceptable quadratic memory behavior
  which is detrimental in large projects with a lot of nesting.

## 0.11.5  -- 2022-01-13
* Add a `library-paths` optional argument to `toolchain` to ensure toolchains
  that require library paths in the environment are accounted for.
* Add a `tool-exec-env` map and an `exec` function to the value returned from
  `toolchain` to make executing toolchain binaries less error-prone.

## 0.11.4  -- 2022-01-12
* Don't deduplicate module `header-dirs` fields to allow consumers to use these
  to convey disparate metadata for the same root header directory.

## 0.11.3  -- 2021-12-23
* Correctly categorize `env-toolchain` in documentation (to prevent it from
  being evaluated prematurely among other things), and allow strings to be
  passed as `toolchain` overrides (which was the intention based on
  documentation but was not realized in the types provided).
* Ensure a leading `.` is removed in header-deps include paths.

## 0.11.2  -- 2021-12-10
* Pretty-print `compile_commands.json`.

## 0.11.1  -- 2021-12-09
* Always include `-fPIC` by default.
  * This is less surprising when it comes to linking and also allows for more
    sharing of cached object files.
* Fix a caching bug resulting from the cached file dependency results being
  misidentified.

## 0.11.0  -- 2021-12-08
* Update scripts for ergo-1.0.0rc.1.
* Improve correctness/safety of configuration-based caching.

## 0.10.1  -- 2021-11-17
* Improve the behavior of header dependency checking when the compiler fails.
  * Failures are inevitably due to preprocessor behavior which is difficult to
    account for, so reduce the errors to warnings (for header files).

## 0.10.0  -- 2021-11-08
* Change the produced `impl` field of modules to be `link`, and change it to be
  an array of `type:ModuleLink` types.
* Add a `module-link` submodule with basic functions to extract values from the
  `link` field.
* Add `type:ModuleLink` to distinguish linked value types.
* Fix dependency visibility errors being propagated (when checking header
  dependencies).
* Use correct toolchain identity when changing toolchain flags from function
  arguments.

### Breaking Changes
* Any use of `c++:compiled-module` will need to update the `link` field to have
  `ModuleLink`-typed values.
* Any use of `c++:get-output` will need to access the `link` field rather than
  the `impl` field (and access the inner values appropriately with
  `c++:module-link` functions).

## 0.9.8  -- 2021-11-02
* Fix a bug in static library creation.

## 0.9.7  -- 2021-10-20
* Change compilation of `.c` files to use the C compiler.
  * `c-compile-flags` is used to distinguish from C++ compile flags.
* Fix a bug in the detection of private includes used in public headers.
* Fix a bug in file dependency calculation.

## 0.9.6  -- 2021-10-14
* Fix a bug in `exact-name` behavior.

## 0.9.5  -- 2021-09-29
* Fix a bug in nested module change tracking.
  * Changes to nested module files would be missed in subsequent builds.

## 0.9.4  -- 2021-09-21
* Improve concurrent behavior of configuration-based caching.
  * There is a race condition that would cause an error to occur. In lieu of
    additional features/support from the standard library, we avoid the error
    but possibly do extra work.
* Change shallow copies of header files to be symlinks.
  * These behave better with CI caching.

## 0.9.3  -- 2021-09-20
* Fix header tracking! It was broken since the update to ergo rc.0, as
  the semantics around evaluation were being relied upon for correct caching.

## 0.9.2  -- 2021-09-08
* Use shallow copies for header files so `#pragma once` and editors can find the
  original files.
* Drastically improve performance of builds with nested modules with a little
  extra caching.

## 0.9.1  -- 2021-09-07
* Change toolchain to allow arbitrary tool names.
* Optimize header dependency tracking with additional caching.
* Fix toolchain default behavior (a bug was making it default to Unset).
* Fix bug in `header-paths` preventing `all` from working as intended.

## 0.9.0  -- 2021-08-03
* Updated to support ergo-1.0.0-rc.0.
* Expose the `context` value to retrieve the current compilation context.

### Breaking Changes
* Change `options:file-content-cache` to instead be `options:cache-policy`, with
  options of `configuration` and `content`.
* Change modules to store arbitrary values rather than a function that takes the
  context. This changes the paradigm of creating modules to one where a user
  writes expressions (that optionally use `context`) which evaluate to a
  `Module` type, doing any necessary value- or context-dependent work prior to
  creating the `Module`.
* `compile-flags` and `link-flags` arguments now are just arrays; if the context
  is needed, use `context`.
* Change `env-toolchain` to be a value rather than a function.

## 0.8.3  -- 2021-06-23
* Fix a bug with symbolic link creation.
* Correct `static-library-name` to return a name with a `lib` prefix for
  linux/mac.

## 0.8.2  -- 2021-04-07
* Improve behavior of compile-flags/link-flags.
  * Compile-flags for a linked output are inherited only by modules that linked
    output uses. Link-flags are not inherited at all.

## 0.8.1  -- 2021-04-06
* Add `abi-version` option to `dynamic-library`, supporting OS conventions for
  abi versioning.
* Fix `exec-output` on mac when runtime libraries are needed.

## 0.8.0  -- 2021-04-01
* Add `compile-commands` to write a `compile_commands.json` file from outputs.
* Change caching to (by default) only depend on compile flags. Add the `options`
  map to `get-outputs` configuration, which has a `file-content-cache` key which
  may be specified to cache based on file content as well (as it used to).
* Allow `uses` to be distinguished as public/private/export.
  * If a private include is exposed in a public header, an error will occur.
* Add `compiled-module` function for creating modules from pre-compiled outputs.
* Move `exe:exec` to `exec-output`, and improve behavior by using the host os
  and preloading libraries when possible, rather than specifying a library load
  path. This avoids issues with SONAME file lookup.

### Breaking Changes
* A `uses` that's just an array will be interpreted as private visibility,
  whereas in the past it behaved as if it were public visibility.
* `exe:exec` no longer works; `exec-output` should be used instead.

## 0.7.0  -- 2021-03-09
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
