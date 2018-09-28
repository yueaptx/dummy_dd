//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ClimbVelocity.h"

registerMooseObject("DummyDDApp", ClimbVelocity);

template <>
InputParameters
validParams<ClimbVelocity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("value", 0.0, "Scalar value used for our auxiliary calculation");
  params.addRequiredCoupledVar("coupled", "Coupled variable");
  return params;
}

ClimbVelocity::ClimbVelocity(const InputParameters & parameters)
  : AuxKernel(parameters),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _coupled_val(coupledValue("coupled")),

    // Set our member scalar value from InputParameters (read from the input file)
    _value(getParam<Real>("value"))
{
}

/**
 * Auxiliary Kernels override computeValue() instead of computeQpResidual().  Aux Variables
 * are calculated either one per elemenet or one per node depending on whether we declare
 * them as "Elemental (Constant Monomial)" or "Nodal (First Lagrange)".  No changes to the
 * source are necessary to switch from one type or the other.
 */
Real
ClimbVelocity::computeValue()
{
  //std::cout << (*_current_node)(0) << std::endl;

  //return _coupled_val[_qp] * 1e-9;
  return (*_current_node)(0) * 1e-2;
}


/*
Take a look at the AuxKernl.C file!!!
Line 38 shows that we need to add the addRequiredParam named "variable"
From line 230 is how it gives the value to the "variable"


*/
