#include <iostream>
#include <vector>
#include <random>
#include <memory>

class MapSimplified {
public:
    static std::shared_ptr<std::vector<std::vector<bool>>> createMap(int gridSize) {
        auto map = std::make_shared<std::vector<std::vector<bool>>>(gridSize, std::vector<bool>(gridSize, true));

        (*map)[0][gridSize - 1] = (*map)[gridSize - 1][0] = (*map)[gridSize - 1][gridSize - 1] = false;

        double pathProbability = 0.9;

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<double> distribution(0.0, 1.0);
                double randomValue = distribution(gen);

                if (randomValue < pathProbability) {
                    (*map)[i][j] = false;
                }
            }
        }

        return map;
    }
};
