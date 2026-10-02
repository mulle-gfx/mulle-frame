### 0.8.1

Various small improvements

## 0.8.0



feature: support `add_subdirectory` consumption with transitive dependency targets

* Library can now be built and linked as a subdirectory of another CMake project
* Dependencies resolve to CMake targets and are propagated transitively via ``target_link_libraries`,` so consumers only need to link the library
* Whole-archive (all-load) dependencies keep their semantics for in-tree consumers
* Multi-reflect header trees are filtered so only the active config headers are used at build time


### 0.7.56

Various small improvements
