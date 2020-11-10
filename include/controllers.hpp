#ifndef METROID_CONTROLLERS_H
#define METROID_CONTROLLERS_H

#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"
#include "views.hpp"


namespace Controllers {

    class Map {
        private:
            Models::Room &room;
            Models::Samus &samus;
            Views::Map mapView;

        public:
            Map(Models::Room &room, Models::Samus &samus);
            void changeRooms(Models::Room &room);
            void update();
    };

    class Metroid {
        private:
            Models::Metroid &metroid;

        public:
            Metroid(Models::Metroid &metroid);
            void moleForce();
            void acceleration();
            void velocity();
            void position();
            void uniformMovement();
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
}

#endif
