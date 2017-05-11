# Software Development Plan

1. Description
    * A university project that allows its user to create, save and load star systems. 
    * Numerical method for ordinary differential equations, Cauchy problem, star system simulation, graphics, file operations.
2. Design
    * Initial thoughts in UML -- in Star_Forge_Concept.pdf
    * Changes:
         * Rethought rough option, now rough and accurate methods are Runge–Kutta and Dormand-Prince methods respectively
         * Load doesn't show information about the system
         * Parameters of existing planets and stars are not shown
         * There are no distinctions between stars and planets -- everything is considered a celestial body
    * Limitations -- no more than ~320 objects in a system, for optimal performance no textures heavier than 1Mb
    * Environment - Linux, g++
3. Development
    * Components (Interface)
    * Responsibilities in UML (a work in progress)
    * Development environment - c++11, SFML (audio, system, window, graphics libraries)
    * No tests yet
    * Integration 
4. Milestones
    * 20.4.17 -- Added load, save and directory preview functions
    * 21.4.17 -- Added Dormand-Prince method, expand
    * 21.4.17 -- Optimized Phase_space structure
    * 25.4.17 -- SDP created
    
