#include "GameManager.h"
#include "HitBox.h"
#include <memory>
#include <utility>
#include <atomic>

GameManager *GameManager::sInstance;
Weapon w;
//Returns the already existing GameManager or if there isn't one, makes
//a new one and returns it.
GameManager *GameManager::instance() {
    if (!sInstance)
        sInstance = new GameManager;
    return sInstance;
}

int32_t GameManager::generateID() {
    static std::atomic<int32_t> counter{-1};
    return ++counter;
}

GameManager::GameManager():collisionHandler() {
    printf("Create GM\n");
}

GameManager::~GameManager() {
    printf("Destroy GM\n");
}

// Render all objects in level
void GameManager::renderObjects(SDL_Renderer* gRenderer, const float camX, const float camY) {
    for (const auto& m : weaponDropManager) {
        m.second.texture.render(gRenderer, m.second.getX() - camX, m.second.getY() - camY);
    }
    for (const auto& m : marineManager) {
        m.second.texture.render(gRenderer, m.second.getX() - camX, m.second.getY() - camY,
                nullptr, m.second.getAngle());
    }

    for (const auto& o : objectManager) {
        o.second.texture.render(gRenderer, o.second.getX() - camX, o.second.getY() - camY);
    }

    for (const auto& z : zombieManager) {
        z.second.texture.render(gRenderer, z.second.getX() - camX, z.second.getY() - camY,
                nullptr, z.second.getAngle());
    }

    for (const auto& m : turretManager) {
        m.second.texture.render(gRenderer, m.second.getX() - camX, m.second.getY() - camY,
                nullptr, m.second.getAngle());
    }

 	for (const auto& b : barricadeManager) {
		b.second.texture.render(gRenderer, b.second.getX()-camX, b.second.getY()-camY);
	}

}

// Update marine movements. health, and actions
void GameManager::updateMarines(const float delta) {
    for (auto& m : marineManager) {
        m.second.move((m.second.getDX()*delta), (m.second.getDY()*delta), collisionHandler);
    }
}

// Update zombie movements.
void GameManager::updateZombies(const float delta) {
    for (auto& z : zombieManager) {
        z.second.generateRandomMove();
        //z.second.move((z.second.getDX()*delta), (z.second.getDY()*delta), collisionHandler);
    }
}

void GameManager::createMarine(int32_t id) {
    marineManager[id] = Marine();
}

/*
// Create marine add it to manager, returns marine id
int32_t GameManager::createMarine() {
    const int32_t id = generateID();
    marineManager[id] = Marine();
    return id;
}
*/
/*
bool GameManager::createMarine(SDL_Renderer* gRenderer, const float x, const float y){
    const int32_t id = generateID();
    marineManager[id] = Marine();
    if (!marineManager.at(id).texture.loadFromFile("assets/texture/arrow.png", gRenderer)) {
        printf("Failed to load the marine texture!\n");
        deleteMarine(id);
        return false;
    }
    marineManager[id].setPosition(x,y);
    return true;
}
*/

/*
Marine& GameManager::createMarine(int id, SDL_Renderer* gRenderer, float x, float y){
    marineManager[id] = Marine();

    if (!marineManager.at(id).texture.loadFromFile("assets/texture/arrow.png", gRenderer)) {
        printf("Failed to load the marine texture!\n");
        deleteMarine(id);
        exit(1);
    }

    marineManager[id].setPosition(x, y);
    return marineManager[id];
}
*/
void GameManager::deleteMarine(const int32_t id) {
    marineManager.erase(id);
}


// Adds marine to level
bool GameManager::addMarine(const int32_t id, const Marine& newMarine) {
    if (marineManager.count(id)) {
        return false;
    }
    marineManager[id] = newMarine;
    return true;
}
/*
// Get a marine by its id
Marine& GameManager::getMarine(const int32_t id) {
    return marineManager.find(id)->second;
}
*/
// Create Turret add it to manager, returns tower id
int32_t GameManager::createTurret() {
    const int32_t id = generateID();
    turretManager[id] = Turret();
    return id;
}

// Deletes tower from level
void GameManager::deleteTurret(const int32_t id) {
    turretManager.erase(id);
}

// Adds tower to level
bool GameManager::addTurret (const int32_t id, const Turret& newTurret) {
    if (turretManager.count(id)) {
        return false;
    }
    turretManager[id] = newTurret;
    return true;
}

// Create turret add it to turret, returns if success
bool GameManager::createTurret(SDL_Renderer* gRenderer, const float x, const float y) {
    const int32_t id = generateID();
    turretManager[id] = Turret();
    if (!turretManager.at(id).texture.loadFromFile("assets/texture/turret.png", gRenderer)) {
        printf("Failed to load the turret texture!\n");
        deleteTurret(id);
        return false;
    }
    turretManager.at(id).setPosition(x,y);
    return true;
}

// Get a tower by its id
Turret& GameManager::getTurret(const int32_t id) {
    return turretManager.find(id)->second;
}

int32_t GameManager::addZombie(const Zombie& newZombie) {
    const int32_t id = generateID();
    zombieManager[id] = newZombie;
    return id;
}

// Create zombie add it to manager, returns success
bool GameManager::createZombie(SDL_Renderer* gRenderer, const float x, const float y) {
    const int32_t id = generateID();
    zombieManager[id] = Zombie();
    if (!zombieManager.at(id).texture.loadFromFile("assets/texture/zombie.png", gRenderer)) {
        printf("Failed to load the player texture!\n");
        deleteZombie(id);
        return false;
    }
    zombieManager.at(id).setPosition(x,y);
    return true;
}

// Deletes zombie from level
void GameManager::deleteZombie(const int32_t id) {
    zombieManager.erase(id);

}

int32_t GameManager::addObject(const Object& newObject) {
    const int32_t id = generateID();
    objectManager[id] = newObject;
    return id;
}

// Deletes Object from level
void GameManager::deleteObject(const int32_t id) {
    objectManager.erase(id);
}

int32_t GameManager::addWeaponDrop(const WeaponDrop& newWeaponDrop) {
    const int32_t id = generateID();
    weaponDropManager.insert({id, newWeaponDrop});
    return id;
}

// Create weapon drop add it to manager, returns success
bool GameManager::createWeaponDrop(SDL_Renderer* gRenderer, const float x, const float y) {
    const int32_t id = generateID();
    const int randGun = rand() % 2 + 1;

    if(randGun == 1){
        w = Rifle();
    } else if(randGun == 2){
        w = ShotGun();
    }

    weaponDropManager.insert({id, WeaponDrop(w)});

    if(!weaponDropManager.at(id).texture.loadFromFile("assets/texture/shotGun.png", gRenderer)) {
        printf("Failed to load the player texture!\n");
        deleteWeaponDrop(id);
        return false;
    }
    weaponDropManager.at(id).setPosition(x,y);
    return true;
}

// Deletes weapon from level
void GameManager::deleteWeaponDrop(const int32_t id) {
    weaponDropManager.erase(id);
}

// Returns Collision Handler
CollisionHandler& GameManager::getCollisionHandler() {
    return collisionHandler;
}

// Update colliders to current state
void GameManager::updateCollider() {
    collisionHandler = CollisionHandler();

    for (auto& m : marineManager) {
        collisionHandler.quadtreeMov.insert(m.second.movementHitBox.get());
        collisionHandler.quadtreePro.insert(m.second.projectileHitBox.get());
        collisionHandler.quadtreeDam.insert(m.second.damageHitBox.get());
    }

    for (auto& z : zombieManager) {
        collisionHandler.quadtreeMov.insert(z.second.movementHitBox.get());
        collisionHandler.quadtreePro.insert(z.second.projectileHitBox.get());
        collisionHandler.quadtreeDam.insert(z.second.damageHitBox.get());
    }

    for (auto& o : objectManager) {
        collisionHandler.quadtreeMov.insert(o.second.movementHitBox.get());
        collisionHandler.quadtreePro.insert(o.second.projectileHitBox.get());
        collisionHandler.quadtreeDam.insert(o.second.damageHitBox.get());
    }

    for (auto& m : turretManager) {
        collisionHandler.quadtreeMov.insert(m.second.movementHitBox.get());
        collisionHandler.quadtreePro.insert(m.second.projectileHitBox.get());
        collisionHandler.quadtreeDam.insert(m.second.damageHitBox.get());
    }

   	for (auto& b : barricadeManager) {
        if (b.second.isPlaced()) {
            collisionHandler.quadtreeMov.insert(b.second.movementHitBox.get());
            collisionHandler.quadtreeDam.insert(b.second.damageHitBox.get());
        }
	}

    for (auto& m : weaponDropManager) {
        collisionHandler.quadtreePickUp.insert(m.second.pickupHitBox.get());
    }
}

void GameManager::updateMarine(const PlayerData &playerData) {
    marineManager[playerData.playerid].setPosition(playerData.xpos, playerData.ypos);
    marineManager[playerData.playerid].setAngle(playerData.direction);
    marineManager[playerData.playerid].setHealth(playerData.health);
}

void GameManager::updateZombie(const ZombieData &zombieData) {
    if(zombieManager.find(zombieData.zombieid) == zombieManager.end()) {
        createZombie(_renderer, zombieData.xpos, zombieData.ypos);
    } else {
        zombieManager[zombieData.zombieid].setPosition(zombieData.xpos, zombieData.ypos);
    }

    zombieManager[zombieData.zombieid].setAngle(zombieData.direction);
    zombieManager[zombieData.zombieid].setHealth(zombieData.health);
}

// Create barricade add it to manager, returns success
int32_t GameManager::createBarricade(SDL_Renderer* gRenderer, const float x, const float y) {
    const int32_t id = generateID();
    barricadeManager[id] = Barricade();
    if (!barricadeManager.at(id).texture.loadFromFile("assets/texture/barricade.png", gRenderer)) {
        printf("Failed to load the barricade texture!\n");
        deleteBarricade(id);
        return -1;
    }
    barricadeManager.at(id).setPosition(x,y);
    return id;
}


void GameManager::deleteBarricade(const int32_t id) {
	barricadeManager.erase(id);
}
// Get a barricade by its id
Barricade& GameManager::getBarricade(const int32_t id) {
    return barricadeManager.find(id)->second;
}

// Create zombie add it to manager, returns success
int32_t GameManager::createWall(SDL_Renderer* gRenderer, const float x, const float y, const int w, const int h) {
    const int32_t id = generateID();
    objectManager[id] = Wall(w, h);
    printf("%d\n", id);
    if (!objectManager.at(id).texture.loadFromFile("assets/texture/wall.png", gRenderer)) {
        printf("Failed to load the wall texture!\n");
        deleteBarricade(id);
        return -1;
   } else {
        objectManager.at(id).texture.setDimensions(w, h);
    }

    objectManager.at(id).setPosition(x,y);

    return id;
}


void GameManager::setBoundary(SDL_Renderer* gRenderer, const float startX, const float startY, const float endX, const float endY){

    int width = endX - startX + 200;
    int height = 100;

    const float x = startX - 100;
    const float y = startY - 100;

    createWall(gRenderer, x, y, width, height);
    createWall(gRenderer, x, endY, width, height);

    width = 100;
    height = endY - startY + 100;

    createWall(gRenderer, endX, startY, width, height);
    createWall(gRenderer, x, startY, width, height);

    const float sX = (endX + startX)/2 - BASE_WIDTH - 100;
    const float eX = (endX + startX)/2 + BASE_WIDTH + 100;
    const float sY = (endY + startY)/2 - BASE_HEIGHT - 100;
    const float eY = (endY + startY)/2 + BASE_HEIGHT + 100;

    width = eX - sX;
    height = 100;

    createWall(gRenderer, sX, sY, width / 2, height);
    createWall(gRenderer, sX + (width / 4 * 3), sY, width / 4, height);
    createWall(gRenderer, sX, eY, width / 4, height);
    createWall(gRenderer, sX + width / 2 + 100, eY, width / 2, height);

    width = 100;
    height = eY - sY;

    createWall(gRenderer, sX, sY, width, height / 2);
    createWall(gRenderer, sX, sY + (height / 4 * 3), width, height / 4);
    createWall(gRenderer, eX, sY, width, height / 1.5);
    createWall(gRenderer, eX, sY + (height / 4 * 3), width, height / 4);
}

bool GameManager::createZombieWave(SDL_Renderer* gRenderer, const int n){
    std::vector<Point> spawnPoints;

    spawnPoints.push_back(Point(-900, -900));
    spawnPoints.push_back(Point(1900, -900));
    spawnPoints.push_back(Point(2900, -900));
    spawnPoints.push_back(Point(2900, 2900));
    spawnPoints.push_back(Point(1900, 2900));
    spawnPoints.push_back(Point(-900, 2900));

    if(zombieManager.size() >= spawnPoints.size() * 5) {
        unsigned int count = 0;
        std::vector<int32_t> ids;
        for(const auto z : zombieManager) {
            if(count >= spawnPoints.size())
                break;
            ids.push_back(z.first);
            count++;
        }
        for(const auto id : ids) {
            deleteZombie(id);
        }
    }

    for(int i = 0; i < n ; i ++) {
        for(const auto p : spawnPoints)
            createZombie(gRenderer, p.first, p.second);
    }

    return true;

}

//Ey:- Mar 13 17- inserts a player in a map of all players of the game
void GameManager::setPlayerUsername(int32_t id, const char * username) {
    assert(marineManager.find(id) != marineManager.end());
    marineManager[id].setUsername(std::string(username));
}

//Ey:- Mar 13 17- retrieves the user name given a
const std::string& GameManager::getNameFromId(int32_t id) {
    assert(marineManager.find(id) != marineManager.end());
    return marineManager[id].getUsername();
}
