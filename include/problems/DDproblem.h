//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef DDPROBLEM_H
#define DDPROBLEM_H

#include "ExternalProblem.h"
//#include "LoopLink.h"

class DDproblem;

template <>
InputParameters validParams<DDproblem>();

/**
 * ExternalProblem derived class that just exercises a portion of the new interface. It demonstrates
 * the limited interface necessary for creating a external problem wrapper.
 */

class DDproblem : public ExternalProblem
{
public:
  DDproblem(const InputParameters & parameters);

  /**
   * Solve is implemented to providing syncing to/from the "transfer" mesh.
   ExternalProblem::solve()
   {
      syncSolutions(Direction::TO_EXTERNAL_APP);
      externalSolve();
      syncSolutions(Direction::FROM_EXTERNAL_APP);
    }
   */
  //virtual void solve() override final;

  /**
   * External problems should provide an override for converged, not inherit the default from
   * FEProblem that provides a reasonable implementation.
   */
   virtual bool converged() override { return true; }

  /**
   * New interface for solving an External problem. "solve()" is finalized here to provide
   * callbacks for solution syncing.
   */
   virtual void externalSolve() override;

  /**
   * Method to transfer data to/from the external application to the associated transfer mesh.
   */
   virtual void syncSolutions(Direction /*direction*/) override {}

  /**
   * Method called to add AuxVariables to the simulation. These variables would be the fields
   * that should either be saved out with the MOOSE-formatted solutions or available for
   * transfer to variables in Multiapp simulations.
   */
   //virtual void addExternalVariables() override {}
};

#endif /* DDPROBLEM_H */
