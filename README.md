# ergo c++

This offers general-purpose c++ compilation and linking for ergo. It offers an
abstraction over groups of c++ files/headers called modules (similar
semantically to c++20 modules), where one module represents (optional) files to
compile as well as headers to expose to interface with the compiled files, and
all dependant modules.

Use standard `ergo` documentation features (e.g. `ergo -d path/to/library`) to
view documentation.
