
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include <limits>
#include <string>

using namespace std;

// ANSI color codes for console output
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";

class Player {
private:
    int x, y;
    static int limit;
    static int monster_damage;
    static int ninja_damage;
    const int max_limit = 100;

public:
    Player(int x = 0, int y = 0) : x(x), y(y) {
        limit = max_limit;
        monster_damage = 0;
        ninja_damage = 0;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    static int getLimit() { return limit; }
    static int getMonsterDamage() { return monster_damage; }
    static int getNinjaDamage() { return ninja_damage; }

    void move(int newX, int newY) {
        x = max(-10, min(10, newX)); // Restrict to grid bounds
        y = max(-10, min(10, newY));
        cout << GREEN << "Player moved to (" << x << ", " << y << ")" << RESET << endl;
    }

    bool attack(int points, const string& attacker) {
        if (limit > 0) {
            limit = max(0, limit - points);
            if (attacker == "Monster") {
                monster_damage += points;
            } else if (attacker == "Ninja") {
                ninja_damage += points;
            }
            cout << RED << "Attacked by " << attacker << " for " << points 
                 << " damage! Health: " << limit << RESET << endl;
            return true;
        } else {
            cout << RED << "Player has died!" << RESET << endl;
            return false;
        }
    }
};
int Player::limit = 100;
int Player::monster_damage = 0;
int Player::ninja_damage = 0;

class Enemy {
protected:
    Player& player;
public:
    Enemy(Player& p) : player(p) {}
    virtual ~Enemy() = default;
    virtual void distance_attack() = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual string getSymbol() const = 0;
};

class Monster : public Enemy {
private:
    int x, y;
    const int range = 10;

public:
    Monster(int x, int y, Player& p) : Enemy(p), x(x), y(y) {
        cout << YELLOW << "Monster spawned at (" << x << ", " << y << ")" << RESET << endl;
    }

    int getX() const override { return x; }
    int getY() const override { return y; }
    string getSymbol() const override { return "M"; }

    void distance_attack() override {
        int dist = static_cast<int>(sqrt(pow(y - player.getY(), 2) + pow(x - player.getX(), 2)));
        if (dist > range) {
            player.attack(2, "Monster");
        }
    }
};

class Ninja : public Enemy {
private:
    int x, y;
    const int range = 10;

public:
    Ninja(int x, int y, Player& p) : Enemy(p), x(x), y(y) {
        cout << BLUE << "Ninja spawned at (" << x << ", " << y << ")" << RESET << endl;
    }

    int getX() const override { return x; }
    int getY() const override { return y; }
    string getSymbol() const override { return "N"; }

    void distance_attack() override {
        int dist = static_cast<int>(sqrt(pow(y - player.getY(), 2) + pow(x - player.getX(), 2)));
        if (dist <= range) {
            player.attack(1, "Ninja");
        }
    }
};

class Game {
private:
    vector<unique_ptr<Enemy>> enemies;
    Player player;
    vector<pair<int, int>> positions;
    const int max_enemies = 10;
    const int grid_size = 21; // 21x21 grid (-10 to 10)
    mt19937 rng;
    bool game_over;

    void initialize_positions() {
        positions = {
            {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 0},
            {0, 9}, {8, 7}, {6, 5}, {4, 3}, {2, 1}
        };
    }

    void display_map() const {
        vector<vector<string>> grid(grid_size, vector<string>(grid_size, "."));
        
        // Place player
        grid[player.getY() + 10][player.getX() + 10] = GREEN + "P" + RESET;
        
        // Place enemies
        for (size_t i = 0; i < enemies.size(); ++i) {
            int ex = enemies[i]->getX() + 10;
            int ey = enemies[i]->getY() + 10;
            if (ex >= 0 && ex < grid_size && ey >= 0 && ey < grid_size) {
                grid[ey][ex] = enemies[i]->getSymbol() == "M" ? YELLOW + "M" + RESET : BLUE + "N" + RESET;
            }
        }

        // Display grid
        cout << "\nGame Map (P=Player, M=Monster, N=Ninja):\n";
        cout << "   ";
        for (int i = -10; i <= 10; ++i) {
            printf("%2d ", i);
        }
        cout << endl;
        for (int i = grid_size - 1; i >= 0; --i) {
            printf("%2d ", i - 10);
            for (int j = 0; j < grid_size; ++j) {
                cout << grid[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void display_status() const {
        cout << "\n" << GREEN << "Player Health: " << Player::getLimit() << "/100" << RESET << "\n";
        cout << "Player Position: (" << player.getX() << ", " << player.getY() << ")\n";
        cout << "Damage Taken: " << YELLOW << Player::getMonsterDamage() << " from Monsters, "
             << BLUE << Player::getNinjaDamage() << " from Ninjas" << RESET << "\n";
        cout << "Enemies (" << enemies.size() << "/" << max_enemies << "):\n";
        for (size_t i = 0; i < enemies.size(); ++i) {
            cout << "  " << i << ": " << (enemies[i]->getSymbol() == "M" ? YELLOW + "Monster" : BLUE + "Ninja")
                 << RESET << " at (" << enemies[i]->getX() << ", " << enemies[i]->getY() << ")\n";
        }
        display_map();
        cout << "-------------------\n";
    }

    void display_welcome() const {
        cout << YELLOW << R"(
        ==============================
          Welcome to Battle Arena!
        ==============================
        )" << RESET << endl;
        cout << "Objective: Defeat all enemies or survive their attacks!\n";
        cout << "Game Mechanics:\n";
        cout << "  - You start at (0,0) with 100 health.\n";
        cout << "  - " << YELLOW << "Monsters" << RESET << " deal 2 damage if you're more than 10 units away.\n";
        cout << "  - " << BLUE << "Ninjas" << RESET << " deal 1 damage if you're within 10 units.\n";
        cout << "  - Move to avoid or trigger enemy attacks strategically.\n";
        cout << "  - Attack to defeat enemies one by one.\n";
        cout << "  - Win by defeating all " << max_enemies << " enemies, or lose if your health reaches 0.\n";
        cout << "Commands:\n";
        cout << "  move <x> <y> - Move to position (x,y) (range: -10 to 10)\n";
        cout << "  attack       - Attack an enemy\n";
        cout << "  status       - Show game status\n";
        cout << "  quit         - Exit the game\n";
        cout << "Symbols: " << GREEN << "P" << RESET << "=Player, "
             << YELLOW << "M" << RESET << "=Monster, " << BLUE << "N" << RESET << "=Ninja\n";
    }

    bool add_enemy() {
        if (enemies.size() >= max_enemies) {
            cout << RED << "Maximum enemy limit reached!" << RESET << endl;
            return false;
        }

        int idx = enemies.size();
        int x = positions[idx].first;
        int y = positions[idx].second;

        if (idx % 2 == 0) {
            enemies.emplace_back(make_unique<Monster>(x, y, player));
        } else {
            enemies.emplace_back(make_unique<Ninja>(x, y, player));
        }
        return true;
    }

    void enemy_turn() {
        for (auto& enemy : enemies) {
            enemy->distance_attack();
        }
    }

    bool player_attack() {
        if (enemies.empty()) {
            cout << YELLOW << "No enemies to attack!" << RESET << endl;
            return true;
        }

        cout << "Choose an enemy to attack (0 to " << enemies.size() - 1 << "): ";
        int target;
        cin >> target;
        if (cin.fail() || target < 0 || static_cast<size_t>(target) >= enemies.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid enemy index!" << RESET << endl;
            return true;
        }

        enemies.erase(enemies.begin() + target);
        cout << GREEN << "Enemy defeated!" << RESET << endl;
        return true;
    }

public:
    Game() : player(0, 0), rng(static_cast<unsigned>(time(nullptr))), game_over(false) {
        initialize_positions();
    }

    ~Game() = default;

    void run() {
        display_welcome();
        while (!game_over) {
            display_status();
            cout << "Enter command: ";
            string command;
            cin >> command;

            if (command == "move") {
                int x, y;
                if (cin >> x >> y) {
                    player.move(x, y);
                    enemy_turn();
                } else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << RED << "Invalid coordinates!" << RESET << endl;
                }
            } else if (command == "attack") {
                player_attack();
            } else if (command == "status") {
                display_status();
            } else if (command == "quit") {
                cout << YELLOW << "Quitting game..." << RESET << endl;
                break;
            } else {
                cout << RED << "Unknown command! Available: move <x> <y>, attack, status, quit" << RESET << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (enemies.size() < max_enemies && !game_over) {
                add_enemy();
            }

            if (Player::getLimit() <= 0) {
                game_over = true;
                cout << RED << R"(
                ==============================
                    GAME OVER - You Died!
                ==============================
                Death Summary:
                )" << RESET;
                cout << "  Total Damage from " << YELLOW << "Monsters" << RESET << ": " 
                     << Player::getMonsterDamage() << " points\n";
                cout << "  Total Damage from " << BLUE << "Ninjas" << RESET << ": " 
                     << Player::getNinjaDamage() << " points\n";
            } else if (enemies.size() == max_enemies && enemies.empty()) {
                game_over = true;
                cout << GREEN << R"(
                ==============================
                    VICTORY - All Enemies Defeated!
                ==============================
                Battle Summary:
                )" << RESET;
                cout << "  Total Damage from " << YELLOW << "Monsters" << RESET << ": " 
                     << Player::getMonsterDamage() << " points\n";
                cout << "  Total Damage from " << BLUE << "Ninjas" << RESET << ": " 
                     << Player::getNinjaDamage() << " points\n";
            }
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}