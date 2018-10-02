//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef CLIMBVELOCITY_H
#define CLIMBVELOCITY_H

#include "AuxKernel.h"

// Forward Declarations
class ClimbVelocity;

template <>
InputParameters validParams<ClimbVelocity>();

/**
 * Coupled auxiliary value
 */
class ClimbVelocity : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  ClimbVelocity(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _coupled_val;

  Real _value;

  Real _diffusivity;
  Real _Uvd;
  Real _Uvf; //[eV], vacancy formation energy
  const Real _kB;
  const Real _eV2J;
  Real _T;
  Real _Dv;
  const Real _burgers;
  Real _c0; // equilibrium concentation in defect-free crystal
};

#endif // CLIMBVELOCITY_H
