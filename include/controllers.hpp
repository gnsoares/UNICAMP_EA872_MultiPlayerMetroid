#ifndef METROID_CONTROLLERS_H
#define METROID_CONTROLLERS_H

#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"
#include "views.hpp"
#include "utils.hpp"


namespace Controllers {

    class Map {
        private:
            Models::Room &room;
            Models::Samus &samus;
            Models:: ShotVector &bullets;
            Views::Map mapView;

        public:
            Map(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets);
            void changeRooms(Models::Room &room);
            void update();
            void metroidPosition();
    };

    class Samus {
        private:
            Models::Samus &samus;
            Views::Samus samusView;

        public:
            Samus(Models::Samus &samus);
            void jump();
            void lookUp();
            void morph();
            void moveLeft();
            void moveRight();
            void update();

            void jumpingAceleration();
            void jumpingPosition();
    };

    class Shots{
        private:
            Models::Shot &shots;
            Models::ShotVector &bullet;
            Models::Samus &samus;
            Views::Shots shotsView;
        public:
            Shots(Models::Shot &shots, Models::ShotVector &bullet, Models::Samus &samus);
            void saveShotPosition();
            void updateShotPosition();
            void update();
    };
}

#endif
