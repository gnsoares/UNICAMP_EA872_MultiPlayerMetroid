#include <iostream>
#include <string>
using namespace std;

class Coord {

    private:
        int x, y;

    public:
        Coord(int x, int y) {
            this->x = x;
            this->y = y;
        }
        string dump() {
            return "(" + to_string(x) + ", " + to_string(y) + ")";
        }
};

class Cube {

    private:
        int x, y, z;

    public:
        Cube(int x, int y, int z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        int get_volume() {
            return x * y * z;
        }
        string dump() {
            return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
        }
};


int main() {
    Coord coord(50, 10);
    Cube cube(10, 20, 30);

    cout << cube.get_volume() << endl;

    return 0;
}
