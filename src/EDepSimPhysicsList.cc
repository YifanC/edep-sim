#include "EDepSimPhysicsList.hh"
#include "EDepSimPhysicsListMessenger.hh"
#include "EDepSimException.hh"
#include "EDepSimExtraPhysics.hh"

// -- include physics list header
#include "lists/MyQGSP_BERT_ArHP.hh"

#include <EDepSimLog.hh>

#include <G4OpticalPhysics.hh>

#include <G4LossTableManager.hh>

#include <G4ProcessManager.hh>
#include <G4ParticleTypes.hh>
#include <G4ParticleTable.hh>

#include <G4PhysListFactory.hh>

#include <G4Gamma.hh>
#include <G4Electron.hh>
#include <G4Positron.hh>
#include <G4Proton.hh>

#include <G4ProcessTable.hh>

#include <G4SystemOfUnits.hh>

#include <unistd.h>

EDepSim::PhysicsList::PhysicsList(G4String physName)
    : G4VModularPhysicsList() {

    fPhysicsListName = "";
    EDepSimLog("Is the physicsList name empty? : " << fPhysicsListName.empty());

    G4LossTableManager::Instance();
    defaultCutValue  = 1.*mm;
    fCutForGamma     = defaultCutValue;
    fCutForElectron  = defaultCutValue;
    fCutForPositron  = defaultCutValue;
    fCutForProton    = defaultCutValue;
    
    fMessenger = new EDepSim::PhysicsListMessenger(this);

    SetVerboseLevel(1);

    G4PhysListFactory factory;
    G4VModularPhysicsList* phys = nullptr;

    // -- Check for the physics list in the following order of priority:
    //    1) Try to use the list provided to the PhysicsList constuctor.
    //       This is passed down w/ the -p input argument
    //    2) Check the environment variable PHYSLIST
    //    3) Fall back on QGSP_BERT if none are provided or requested
    //       list is not registered or DNE

    // Check to see if the physics list has been overridden from the
    // environment variable PHYSLIST
    char* list = getenv("PHYSLIST");
    if ( !physName.empty() ) { // -- Request the physics list provided
      fPhysicsListName = physName;
    } else if (list) { // -- Fall back on the ENV var, if set
      fPhysicsListName = list;
    } else {
      fPhysicsListName = "QGSP_BERT"; // -- use the default physics list
    }

    EDepSimLog("Asking for physics list named: " << fPhysicsListName);

    // -- Get the G4VModularPhysicsList
    if ( factory.IsReferencePhysList(fPhysicsListName) )
    {
      phys =factory.GetReferencePhysList(fPhysicsListName);
    }
    else if ( fPhysicsListName == "MyQGSP_BERT_ArHP" )
    {
      phys = new MyQGSP_BERT_ArHP();

      // Set proton cut value to 0 for producing low energy recoil nucleus
      fCutForProton = 0.*mm;
    } else {
      EDepSimLog("Requested physics list (" << fPhysicsListName
              << ") does not exist or is not registered");
      EDepSimLog("Available phyiscs lists: " << factory.AvailablePhysLists() );
    }

    if ( phys!=nullptr) {
        EDepSimLog("Using physics list w/ name: " << fPhysicsListName);
    }

    // Use the default physics list.
    if ( phys == nullptr ) {
        EDepSimLog("Set the default physics list");
        phys =factory.GetReferencePhysList("QGSP_BERT");
    }

    if (phys == nullptr) {
        EDepSimLog("Available phyiscs lists: " << factory.AvailablePhysLists() );
        EDepSimThrow("No physics list was created.");
    }

    // Transfer the physics list from the factory to this one.
    for (G4int i = 0; ; ++i) {
        G4VPhysicsConstructor* elem =
            const_cast<G4VPhysicsConstructor*> (phys->GetPhysics(i));
        if (elem == NULL) break;
        G4cout << "RegisterPhysics: " << elem->GetPhysicsName() << G4endl;
        RegisterPhysics(elem);
    }

    // Add our specific lists.
    fExtra = new EDepSim::ExtraPhysics();
    RegisterPhysics(fExtra);
    RegisterPhysics(new G4OpticalPhysics());

}

EDepSim::PhysicsList::~PhysicsList() {
    delete fMessenger;
}

void EDepSim::PhysicsList::SetCuts() {
    if (verboseLevel >0) {
        G4cout << "EDepSim::PhysicsList::SetCuts:";
        G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length")
               << G4endl;
    }

    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma
    SetCutValue(fCutForGamma, "gamma");
    SetCutValue(fCutForElectron, "e-");
    SetCutValue(fCutForPositron, "e+");
    SetCutValue(fCutForProton, "proton");

    if (verboseLevel>0) DumpCutValuesTable();
}

void EDepSim::PhysicsList::SetCutForGamma(G4double cut) {
    fCutForGamma = cut;
    SetParticleCuts(fCutForGamma, G4Gamma::Gamma());
    G4cout  << "Setting cut for Gammas to: " << fCutForGamma
            << G4endl;
}

void EDepSim::PhysicsList::SetCutForElectron(G4double cut) {
    fCutForElectron = cut;
    SetParticleCuts(fCutForElectron, G4Electron::Electron());
    G4cout  << "Setting cut for Electrons to: " << fCutForElectron
            << G4endl;
}

void EDepSim::PhysicsList::SetCutForPositron(G4double cut) {
    fCutForPositron = cut;
    SetParticleCuts(fCutForPositron, G4Positron::Positron());
    G4cout  << "Setting cut for Positrons to: " << fCutForPositron
            << G4endl;
}

void EDepSim::PhysicsList::SetCutForProton(G4double cut) {
    fCutForProton = cut;
    SetParticleCuts(fCutForProton, G4Proton::Proton());
    G4cout  << "Setting cut for Proton to: " << fCutForProton
            << G4endl;
}

void EDepSim::PhysicsList::SetIonizationModel(bool b) {
    fExtra->SetIonizationModel(b);
    G4cout  << "Setting ionization models: " << fCutForGamma
            << G4endl;
}
