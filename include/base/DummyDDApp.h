//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef DUMMY_DDAPP_H
#define DUMMY_DDAPP_H

#include "MooseApp.h"

class DummyDDApp;

template <>
InputParameters validParams<DummyDDApp>();

class DummyDDApp : public MooseApp
{
public:
  DummyDDApp(InputParameters parameters);
  virtual ~DummyDDApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s);
};

#endif /* DUMMY_DDAPP_H */
