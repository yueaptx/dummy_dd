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
  params.addRequiredCoupledVar("coupled", "Coupled variable");
  params.addParam<Real>("value", 0.0, "Scalar value used for our auxiliary calculation");
  params.addParam<Real>("diffusivity", 1.18e-5, "[m^2/s], diffusion coefficient pre-exponential");
  params.addParam<Real>("Uvd", "[eV], vacancy migration energy");
  params.addParam<Real>("Uvf", "[eV], vacancy formation energy");
  params.addParam<Real>("kB", 1.3806e-23 ,"m^2kg/s^2/K], Boltzmann constant");
  params.addParam<Real>("eV2J", 1.60218e-19 ,"[J/eV], convert eV to Joules");
  params.addParam<Real>("T", "[K], temperature");
  params.addParam<Real>("burgers", "[m], burger's vector magnitude");
  return params;
}

ClimbVelocity::ClimbVelocity(const InputParameters & parameters)
  : AuxKernel(parameters),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _coupled_val(coupledValue("coupled")),

    // Set our member scalar value from InputParameters (read from the input file)
    _value(getParam<Real>("value")),

    _diffusivity(getParam<Real>("diffusivity")),
    _Uvd(getParam<Real>("Uvd")),
    _Uvf(getParam<Real>("Uvf")),
    _kB(getParam<Real>("kB")),
    _eV2J(getParam<Real>("eV2J")),
    _T(getParam<Real>("T")),
    _Dv(_diffusivity * exp(- _Uvd * _eV2J / _kB / _T)),
    _burgers(getParam<Real>("burgers")),
    _c0(exp(- _Uvf * _eV2J / _kB / _T))
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

  const Real PI = 3.1415926;
  Real _vc = 2 * PI * _Dv / _burgers / std::log(1e-6/16/_burgers) * (_c0 * 2 - _coupled_val[_qp]);
  std::cout << "The climb velocity is " << _vc << std::endl;
  return _vc;

  //return _coupled_val[_qp] * 1e-9;
  //return (*_current_node)(0) * 1e-2;
}


/*
Take a look at the AuxKernl.C file!!!
Line 38 shows that we need to add the addRequiredParam named "variable"
From line 230 is how it gives the value to the "variable"


*/
