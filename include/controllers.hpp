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
            Models::Room &room; /*!< Model (previously allocated) */
            Views::Map &mapView; /*!< View (previously allocated) */
            int damageCooldown = 0; /*!< Controls damage*/

        public:
            /*! \brief Map controller's constructor
             *
             * Receives a model and a view previously allocated
             *
             * \param room room model
             * \param mapView map view
             * \return nothing
             */
            Map(Models::Room &room, Views::Map &mapView);

            /*! \brief Make a metroid take damage
             *
             * This function also outputs the Metroid's hp to stdout
             * 
             * \param metroid metroid model
             * \return nothing
             */
            void damageMetroid(Models::Metroid &metroid);

            /*! \brief Changes Rooms
            *
            * If Samus goes to another room, calls
            * the functions to generate a new room
            *
            * \param room room model
            * \return nothing
            */       
            void changeRooms(Models::Room &room);

            /*! \brief Updates the state of the map
             *
             * Updates the positions and states of all the elements
             * that compose the map
             *
             * \param shots shots vector
             * \return nothing
             */
            void update(std::vector<Models::Shot> shots);
    };

    class Samus {
        private:
            Models::Samus &samus; /*!< Model (previously allocated) */
            Views::Samus &samusView; /*!< View (previously allocated) */
            int damageCooldown = 0;

        public:

            /*! \brief Samus controller's constructor
             *
             * Receives a model and a view previously allocated
             *
             * \param samus samus model
             * \param samusView samus view
             * \return nothing
             */
            Samus(Models::Samus &samus, Views::Samus &samusView);

            /*! \brief Make Samus take damage
             *
             * This function also outputs the Samus' hp to stdout
             *
             * \return nothing
             */
            void damage();

            /*! \brief Make Samus jump
             * 
             * \return nothing
             */
            void jump();

            /*! \brief Make Samus look up
             * 
             * \return nothing
             */
            void lookUp();

            /*! \brief Make Samus morph
             *
             * \return nothing
             */
            void morph();

            /*! \brief Make Samus move left
             *
             * \return nothing
             */
            void moveLeft();

            /*! \brief Make Samus move right
             *
             * \return nothing
             */
            void moveRight();

            /*! \brief Update Samus' state
             *
             * \param blocks blocks vector
             * \param doors doors vector
             * \param metroids metroids vector
             * \return nothing
             */
            void update(std::vector<Models::Block> blocks, std::vector<Models::Door> doors, std::vector<Models::Metroid> metroids);
    };

    class Shots {
        private:
            std::vector<Models::Shot> &shots; /*!< Model (previously allocated) */
            Views::Shots &shotsView; /*!< View (previously allocated) */
            int shotCooldown = 0; /*!< Controls shots */

        public: 
            /*! \brief Shot controller's constructor
             *
             * Receives a vector of models and a view previously allocated
             *
             * \param shots shots vector
             * \param shotsView shots view
             * \return nothing
             */
            Shots(std::vector<Models::Shot> &shots, Views::Shots &shotsView);

            /*! \brief Creates a shot
             *
             * \return nothing
             */
            void createShot(int x, int y, int vx, int vy);

            /*! \brief Update shots' state
             *
             * \return nothing
             */
            void update(int x, int y, int vx, int vy);
    };
}

#endif
