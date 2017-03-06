#ifndef QUADTREE_H
#define QUADTREE_H
#include<SDL2/SDL.h>
#include "HitBox.h"
#include <vector>
#include <array>
#include <memory>

constexpr unsigned int BRANCHSIZE = 4;
constexpr unsigned int MAX_OBJECTS = 10;
constexpr unsigned int MAX_LEVELS = 5;

class Quadtree {
public:
    Quadtree(int pLevel, SDL_Rect pBounds);
    ~Quadtree() = default;
    
    Quadtree& operator=(const Quadtree& quad);

    void clear();
    void split();
    unsigned int getTreeSize() const;
    int getIndex(const HitBox *pRect) const;
    void insert(HitBox *pRect);
    std::vector<HitBox *> retrieve(const HitBox *pRect);

    std::vector<HitBox *> objects;

private:
    unsigned int objectCounter;
    unsigned int level;
    SDL_Rect bounds;
    std::array<std::shared_ptr<Quadtree>, BRANCHSIZE> nodes;
};

#endif
