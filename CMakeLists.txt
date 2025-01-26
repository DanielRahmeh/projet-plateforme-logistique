# Version minimale de CMake
cmake_minimum_required(VERSION 3.10)
 
# Nom du projet
project(projet VERSION 1.0)
 
 
# Choix du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

 
# Définir les fichiers source et header séparément
set(SOURCES
    main.cpp
    src/Plateforme.cpp
    src/Region.cpp
    src/Manutention.cpp
    src/Transporteur.cpp
    src/Simulation.cpp
)
 
set(HEADERS)
 
# Ajouter l'exécutable
add_executable(projet ${SOURCES} ${HEADERS})