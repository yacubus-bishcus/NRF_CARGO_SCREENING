#ifndef StepMessenger_h
#define StepMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4ApplicationState.hh"
#include "G4UIcmdWithAString.hh"
#include "BaseSteppingAction.hh"
#include "G4UIdirectory.hh"

class BaseSteppingAction;
class G4UIcmdWithAString;
class G4UIdirectory;


class StepMessenger: public G4UImessenger
{
public:
  StepMessenger(BaseSteppingAction*);
  ~StepMessenger();

  void SetNewValue(G4UIcommand*, G4String);
private:
  BaseSteppingAction* stepA;
  G4UIcmdWithAString* Cmd;
  G4UIdirectory *myDir;
};

#endif
