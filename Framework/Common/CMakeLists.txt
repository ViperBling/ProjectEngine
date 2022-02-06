add_library(Common 
Allocator.cpp
BaseApplication.cpp
GraphicsManager.cpp
MemoryManager.cpp
ProjectEngine.cpp)

target_link_libraries(Common GeomMath)