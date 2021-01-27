# ergo-c++ changelog

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
