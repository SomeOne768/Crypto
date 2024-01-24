cmake_minimum_required(VERSION 3.0)
project(tp7)

# Ensemble des fichiers sources
set(SOURCES src/main.cpp)

# Configuration des options de compilation
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -pedantic -I /usr/X11R6/include")

# Bibliothèques à lier
find_package(X11 REQUIRED)
find_package(Threads REQUIRED)
find_library(GMP_LIBRARY gmp)

# Chemin vers les bibliothèques
set(EXTRA_LIBS ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${GMP_LIBRARY})

# Création de l'exécutable
add_executable(tp7 ${SOURCES})

# Liaison des bibliothèques
target_link_libraries(tp7 ${EXTRA_LIBS})
