//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "DummyDDTestApp.h"
#include "DummyDDApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<DummyDDTestApp>()
{
  InputParameters params = validParams<DummyDDApp>();
  return params;
}

DummyDDTestApp::DummyDDTestApp(InputParameters parameters) : MooseApp(parameters)
{
  DummyDDTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

DummyDDTestApp::~DummyDDTestApp() {}

void
DummyDDTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  DummyDDApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"DummyDDTestApp"});
    Registry::registerActionsTo(af, {"DummyDDTestApp"});
  }
}

void
DummyDDTestApp::registerApps()
{
  registerApp(DummyDDApp);
  registerApp(DummyDDTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
DummyDDTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  DummyDDTestApp::registerAll(f, af, s);
}
extern "C" void
DummyDDTestApp__registerApps()
{
  DummyDDTestApp::registerApps();
}
