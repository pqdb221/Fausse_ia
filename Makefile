# Variables de compilation
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Nom de l'exécutable final
TARGET = fausse-ia

# Règle principale (par défaut)
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): fausse-ia.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) fausse-ia.cpp

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET)

.PHONY: all clean
