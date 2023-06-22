#ifndef EDepSim_PhysicsList_h
#define EDepSim_PhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;
namespace EDepSim {class PhysicsListMessenger;}
namespace EDepSim {class ExtraPhysics;}

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v)
{
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : v) {
        s << comma << e;
        comma[0] = ',';
    }
    return s << ']';
}

/// Use the G4PhysListFactory to select a physics list for this run.  The
/// physics list can be set from the PHYSLIST environment variable, or a macro
/// file.  All of the physics lists need to be defined before using the
/// /run/initialize command.
namespace EDepSim {class PhysicsList;}
class EDepSim::PhysicsList: public G4VModularPhysicsList {
public:

    /// Construct the physics list.  If physName is a valid list, then it will
    /// be used.  Otherwise, the physics list will be read first from the
    /// macro file, and then from the PHYSLIST environment variable.  If all
    /// of thoses methods fail, then a G4 provided default will be used.
    explicit PhysicsList(G4String physName);

    virtual ~PhysicsList();

    /// Set the physics list name to be used (this is used by the physics list
    /// messenger.
    void SetPhysicsListName(G4String pName);

    /// Used by GEANT4 to set the cuts defined below.
    virtual void SetCuts();

    /// Set the range cut for photons.
    void SetCutForGamma(G4double);
    
    /// Set the range cut for electrons.
    void SetCutForElectron(G4double);

    /// Set the range cut for positrons.
    void SetCutForPositron(G4double);

    /// Set the range cut for positrons.
    void SetCutForProton(G4double);

    /// Set the recombination fraction for liquid argon (negative for using
    /// nest).
    void SetIonizationModel(bool);
    
private:

    // The physics list requested in the constructor, if any
    G4String fPhysicsListName;

    /// The gamma-ray range cut.
    G4double fCutForGamma;

    /// The electron range cut.
    G4double fCutForElectron;

    /// The positron range cut.
    G4double fCutForPositron;

    /// The proton range cut.
    G4double fCutForProton;

    /// The extra physics list
    EDepSim::ExtraPhysics* fExtra;
    
    /// The messenger to control this class.
    EDepSim::PhysicsListMessenger* fMessenger;

};

#endif
