/// @file   waveadvance.h
/// @author Ramses van Zon
/// @date   March 6, 2022
/// @brief  Module for numerically evolving the wave field one step in time. 


#ifndef WAVEADVANCEH
#define WAVEADVENCEH

#include "parameters.h"
#include "wavefields.h"

/// @brief advance wave one timestep
/// @param  w       The wavefields struct to advance
/// @param  params  The basic parameters for the simulation
/// @param  derives The derived parameters for the simulation

void advance_wave(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs);

void advance_wave_dgemv(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs,
                  rmatrix<double> G);

void advance_wave_dgbmv(WaveFields& w,
                  const InputParameters& params,
                  const DerivedParameters& derivs,
                  rmatrix<double> G_band);
#endif
