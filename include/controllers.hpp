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
            *   Receives a model and a view previously allocated
            *
            * \param a Model (containing Room's infos)
            * \param a View (contining Map's infos)
            * \return nothing
            */
            Map(Models::Room &room, Views::Map &mapView);

            /*! \Calculates Metroid's Life
            *
            * This function also prints the Metroid's life
            * so the player can know this information
            * 
            * \param a Model (containing Metroid's infos)
            * \return nothing
            */
            void damageMetroid(Models::Metroid &metroid);

            /*! \brief Changes Rooms
            *
            *   If Samus goes to another room, calls
            *   the functions to generate a new room
            *
            * \param a Model (contaning Room's infos)
            * \return nothing
            */       
            void changeRooms(Models::Room &room);

            /*! \brief Draw new frame
            *
            *   Calls a function from View to draw the
            *   images on the screen after the update 
            *   of the objects positions
            *
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
             * Receives two models previously allocated
             *
             * \param a Model (containing Samus' infos)
             */
            Samus(Models::Samus &samus, Views::Samus &samusView);

            /*! \Calculates Samus's Life
            *
            * This function also prints tSamus' life
            * so the player can know this information
            *
            * \return nothing
            */
            void damage();

            /*! \brief Controlls Samus' jump
             *
             * Verifies if Samus is jumping and if she
             * is, sets her state to jumping and call the 
             * functions to update her velocity and position 
             * during the jump
             * 
             * \return nothing
             */
            void jump();

            /*! \brief Controlls Samus when shes looking up
             *
             * Verifies if Samus is looking up and, if she
             * is, sets her state as so and call the functions
             * to make her aim upwards.
             * 
             * \return nothing
             */
            void lookUp();

            /*! \brief Controlls Samus' morphing
            *
            *   Verifies if Samus has morphing ball and if she
            *   does, sets her state to morphed
            * 
            * \return nothing
            */
            void morph();

            /*! \brief Controlls Samus walking to the left
            *
            *   Updates Samus' position to the left
            *
            * \return nothing
            */
            void moveLeft();

            /*! \brief Controlls Samus walking to the right
            *
            *   Updates Samus' position to the right
            *
            * \return nothing
            */
            void moveRight();

            /*! \brief Integration between keyboard commands and Samus controller
            *
            *   Gets updtaded keyboard state and calls functions accordingly
            *
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
            *   Receives two models previously allocated
            *
            * \param a Model (containing Samus' infos)
            * \param a Model (containing Shot's infos)
            * \return nothing
            */
            Shots(std::vector<Models::Shot> &shots, Views::Shots &shotsView);

            /*! \brief Allocates Shot Object
            *
            *   Aloccates Shot Object on a vector previously
            *   define, basing it's initial positions on Samus's
            *   position at the moment the Shot is created
            *
            * \return nothing
            */
            void createShot(int x, int y, int vx, int vy);

            /*! \brief Integration between keyboard commands and shots controller
            *
            *   Gets updtaded keyboard state and calls functions accordingly
            *
            * \return nothing
            */
            void update(int x, int y, int vx, int vy);
    };
}

#endif
