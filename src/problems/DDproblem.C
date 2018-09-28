//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DDproblem.h"

#include "MooseApp.h"

registerMooseObject("DummyDDApp", DDproblem);

template <>
InputParameters
validParams<DDproblem>()
{
  InputParameters params = validParams<ExternalProblem>();
  return params;
}

// Constrcutor
DDproblem::DDproblem(const InputParameters & parameters) : ExternalProblem(parameters)
{
}

void
DDproblem::externalSolve()
{
  std::cout << "Solved!!" << std::endl;
}
