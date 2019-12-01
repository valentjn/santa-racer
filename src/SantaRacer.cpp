/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer.hpp"

#include "Args.hpp"
#include "Globals.hpp"
#include "Setup.hpp"

int main(int argc, char *argv[]) {
  SantaRacer::Args::check_args(argc, argv);
  SantaRacer::Setup::santa_setup();
  SantaRacer::Setup::game->loop();
  SantaRacer::Setup::santa_cleanup();
  return 0;
}