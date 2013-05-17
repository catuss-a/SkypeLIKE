//
// main.cpp for  in /home/champi_d//AdvancedCPP/Babel
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//
// Started on  Tue Nov 15 16:45:21 2011 alexandre champion
// Last update Sun Dec  4 11:59:59 2011 alexandre champion
//

#include "NinaOS.hpp"
#include "Babel.hpp"

int		main()
{
  NINA::Init	init;
  Babel* application;

  try
    {
      application = new Babel;
      application->run();
    }
  catch (std::exception& e)
    {
      std::cerr << "exception caught: " << e.what() << std::endl;
    }
  catch (...)
    {
      std::cerr << "uncaught exception" << std::endl;
    }
  return 0;
}
