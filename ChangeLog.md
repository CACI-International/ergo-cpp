# ergo-c++ changelog

## 0.3.3  -- Unreleased
* Fix bug with compiler invocation for header tracking.
  * The invocation did not pass the PATH environment variable, which breaks
    e.g. ccache.
* Improve task behavior (ergo >= beta.6).

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
