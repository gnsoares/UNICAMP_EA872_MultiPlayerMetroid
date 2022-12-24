#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Mass {

    private:
        double mass, initial_velocity;

    public:
        Mass(double mass, double initial_velocity = 0) {
            this->mass = mass;
            this->initial_velocity = initial_velocity;
        }
        double get_mass() {
            return mass;
        }
        double get_initial_velocity() {
            return initial_velocity;
        }
};

class Spring {

    private:
        double k, damping, displacement;

    public:
        Spring(double k, double damping = 0, double displacement = 0) {
            this->k = k;
            this->damping = damping;
            this->displacement = displacement;
        }
        void set_displacement(double displacement) {
            this->displacement = displacement;
        }
        double get_k() {
            return k;
        }
        double get_damping() {
            return damping;
        }
        double get_displacement() {
            return displacement;
        }
};

class System {
    // ma + bv + kx = 0

    private:
        Mass* mass;
        Spring* spring;
        string damping;
        double beta, frequency;
        double time, timedelta;

    public:
        System(Mass& mass, Spring& spring, double timedelta) {
            this->mass = &mass;
            this->spring = &spring;
            beta = spring.get_damping() / 2 / mass.get_mass();
            frequency = sqrt(spring.get_k() / mass.get_mass());
            time = 0;
            this->timedelta = timedelta;

            double beta2 = pow(beta, 2);
            double frequency2 = pow(frequency, 2);

            if (frequency2 > beta2) {
                damping = 'under';
            } else if (frequency2 == beta2) {
                damping = 'critical';
            } else {
                damping = 'over';
            }
        }
        double get_current_displacement() {
            return spring->get_displacement();
        }
        void set_next_displacement() {
            spring->set_displacement();
        }
};


int main() {
    double position[50];



    return 0;
}
