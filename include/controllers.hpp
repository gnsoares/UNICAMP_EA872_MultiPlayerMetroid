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
            Models::Samus &samus; /*!< Model (previously allocated)*/
            Models:: ShotVector &bullets; /*!< Model (previously allocated) */
            Views::Map mapView; /*!< View (previously allocated) */

        public:
            /*! \brief Samus controller's constructor
            *  
            *   Receives three models previously allocated
            *  
            * \param a Model (containing Room's infos)
            * \param a Model (containing Samus' infos)
            * \param a Model (containing vector of Shots infos)
            * \return nothing
            */
            Map(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets);
            void changeRooms(Models::Room &room);

            /*! \brief Draw new frame
            *  
            *   Calls a function from View to draw the
            *   images on the screen after the update 
            *   of the objects positions
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void update();

            /*! \brief Calculates metroid's mole force
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void metroidForce();

            /*! \brief Calculates metroid's acceleration
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void metroidAcc();

            /*! \brief Calculates metroid's velocity
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void metroidVel();

            /*! \brief Updates metroid's position
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void metroidPosition();

            /*! \brief Updates metroid's damp-mass-mole movement
            *  
            * Calls functions that update Metroid's attibutes, such as 
            * acceleration, velocity, posiiton and mole force in an order
            * so that the Metroid can execute a mass-mole-damp movement
            * 
            * \param does not have paramethers
            * \return nothing
            */
            void metroidUpdate();
    };

    class Samus {
        private:
            Models::Samus &samus; /*!< Model (previously allocated) */
            Views::Samus samusView; /*!< View (previously allocated) */

        public:

            /*! \brief Samus controller's constructor
            *  
            *   Receives two models previously allocated
            *  
            * \param a Model (containing Samus' infos)
            */
            Samus(Models::Samus &samus);

            /*! \brief Controlls Samus' jump
            *  
            *   Verifies if Samus is jumping and if she
            *   is, sets her state to jumping and call the 
            *   functions to update her velocity and position 
            *   during the jump
            * 
            * \param does not have paramethers
            * \return nothing
            */
            void jump();

            /*! \brief Controlls Samus when shes looking up
            *  
            *   Verifies if Samus is looking up and, if she
            *   is, sets her state as so and call the functions
            *   to make her aim upwards.
            * 
            * \param does not have paramethers
            * \return nothing
            */
            void lookUp();

            /*! \brief Controlls Samus' morphing
            *  
            *   Verifies if Samus has morphing ball and if she
            *   does, sets her state to morphed
            * 
            * \param does not have paramethers
            * \return nothing
            */
            void morph();

            /*! \brief Controlls Samus walking to the left
            *  
            *   Updates Samus' position to the left
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void moveLeft();

            /*! \brief Controlls Samus walking to the right
            *  
            *   Updates Samus' position to the right
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void moveRight();

            /*! \brief Integration between keyboard commands and Samus controller
            *  
            *   Gets updtaded keyboard state and calls functions accordingly
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void update();

            /*! \brief Updates Samus velocity
            *  
            *   Updates Samus velocity while she is jumping
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void jumpingAceleration();

            /*! \brief Updates Samus position
            *  
            *   Updates Samus position while she is jumping
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void jumpingPosition();
    };

    class Shots{
        private:
            Models::ShotVector &bullet; /*!< Model (previously allocated) */
            Models::Samus &samus; /*!< Model (previously allocated) */
            Views::Shots shotsView; /*!< View (previously allocated) */
        public: 
            /*! \brief Shot controller's constructor
            *  
            *   Receives two models previously allocated
            *  
            * \param a Model (containing Samus' infos)
            * \param a Model
            * \return nothing
            */
            Shots(Models::ShotVector &bullet, Models::Samus &samus);

            /*! \brief Allocates Shot Object
            *  
            *   Aloccates Shot Object on a vector previously
            *   define, basing it's initial positions on Samus's
            *   position at the moment the Shot is created
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void saveShotPosition();

            /*! \brief Update Shot Position
            *  
            *   Aloccates Shot Object on a vector previously
            *   define, basing it's initial positions on Samus's
            *   position at the moment the Shot is created
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void updateShotPosition();

            /*! \brief Integration between keyboard commands and shots controller
            *  
            *   Gets updtaded keyboard state and calls functions accordingly
            *  
            * \param does not have paramethers
            * \return nothing
            */
            void update();
    };
}

#endif
