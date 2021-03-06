#include "ReadState.hh"

ReadState::ReadState() {}

std::pair<int, int> ReadState::getObjCoords() const {
    return objCoords;
}

std::vector<std::pair<int, int>> ReadState::getSkeletonCoords() const {
    return skeletonCoords;
}

void ReadState::inspectElements(int levelId) {
    std::string fileName = "../levels/level"+std::to_string(levelId)+".txt";
    std::ifstream file(fileName);
    char delimiter = ' ';
    std::string mapKeyword = "mapa:";
    std::string objetivoKeyword = "objetivo:";
    std::string esqueletoKeyword = "esqueleto:";

    // Find mapKeyword
    bool mapFound = false;
    int guessedWidthDimension = -1;
    std::string line;
    while(std::getline(file, line)) {
        if(mapFound) {
            guessedWidthDimension = guessWidthDimension(line, delimiter);
            this->mapDimension = guessedWidthDimension;
            break;
        }
        else {
            if(line.find(esqueletoKeyword) != std::string::npos) {
                // Analizar fila
                size_t pos = line.find(delimiter);  // Find first delimiter
                line.erase(0, pos+1);   // Eliminar palabra de la línea
                size_t newPos = line.find(delimiter);
                std::string coordX = line.substr(0, newPos);
                line.erase(0, newPos+1);
                std::string coordY = line;
                std::pair<int,int> skeletonCoord = {std::stoi(coordX), std::stoi(coordY)};
                skeletonCoords.push_back(skeletonCoord);
                continue;
            }
            if(line.find(objetivoKeyword) != std::string::npos) {
                // Analizar fila
                size_t pos = line.find(delimiter);  // Find first delimiter
                line.erase(0, pos+1);   // Eliminar palabra de la línea
                size_t newPos = line.find(delimiter);
                std::string coordX = line.substr(0, newPos);
                line.erase(0, newPos+1);
                std::string coordY = line;
                this->objCoords = {std::stoi(coordX), std::stoi(coordY)};
            }
            if(line.find(mapKeyword) != std::string::npos) {
                mapFound = true;
            }
        }
    }
    if(!mapFound) {std::cout << "ERROR in level"+std::to_string(levelId)+", "+mapKeyword+" NOT FOUND"; exit(-1);}
    initializeMatrix(file, guessedWidthDimension, line, delimiter);
}

void ReadState::initializeMatrix(std::ifstream& file, int guessedWidthDimension, std::string line, char delimiter) {
    int rowCount = 0;
    matrix = new int*[guessedWidthDimension];
    for(int i=0; i<guessedWidthDimension; ++i) {
        matrix[i] = new int[guessedWidthDimension];
    }

    int a = 0, b = 0;
    do {
        // Analizar fila
        std::string token;
        size_t pos;
        while((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            matrix[a][b++] = std::stoi(token);
            do {
                line.erase(0, 1);   // Eliminar primer elemento de la línea
            } while(line[0] == delimiter);
        }
        matrix[a][b] = std::stoi(line);
        ++a;
        b = 0;

        ++rowCount;
    } while(std::getline(file, line) && rowCount < guessedWidthDimension);
}

int ReadState::guessWidthDimension(std::string line, char delimiter) {
    int width =0;
    size_t pos;
    while((pos = line.find(delimiter)) != std::string::npos) {
        ++width;
        do {
            line.erase(0, 1);   // Eliminar primer elemento de la línea
        } while(line[0] == delimiter);
    }
    return width + 1;   // Cuenta los espacios, asi que devolver el número de espacios más 1
}

int ReadState::getElementFromCelda(int i, int j) {
    return matrix[i][j];
}

std::pair<int, int> ReadState::getPlayerCoords() const {
    int fila = 0;
    int columna = 0;
    for(int i=0; i<this->mapDimension; ++i) {
        for(int j=0; j<this->mapDimension; ++j) {
            if(matrix[i][j] == 5) {
                fila = i;
                columna = j;
            }
        }
    }
    return {fila, columna};
}