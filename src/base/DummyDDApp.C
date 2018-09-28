#include "DummyDDApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<DummyDDApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

DummyDDApp::DummyDDApp(InputParameters parameters) : MooseApp(parameters)
{
  DummyDDApp::registerAll(_factory, _action_factory, _syntax);
}

DummyDDApp::~DummyDDApp() {}

void
DummyDDApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"DummyDDApp"});
  Registry::registerActionsTo(af, {"DummyDDApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
DummyDDApp::registerApps()
{
  registerApp(DummyDDApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
DummyDDApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  DummyDDApp::registerAll(f, af, s);
}
extern "C" void
DummyDDApp__registerApps()
{
  DummyDDApp::registerApps();
}
