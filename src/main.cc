#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "FTFP_BERT.hh"
#include "G4SystemOfUnits.hh"

#include "include/HepMCG4AsciiReader.hh"

#include <iostream>

// --- Minimal Detector ---
class MinimalDetector : public G4VUserDetectorConstruction {
public:
    G4VPhysicalVolume* Construct() override {
        G4NistManager* nist = G4NistManager::Instance();
        G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

        G4Box* worldBox = new G4Box("World", 1*m, 1*m, 1*m);
        G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, air, "World");
        G4VPhysicalVolume* worldPhys = new G4PVPlacement(
            nullptr, G4ThreeVector(), worldLog, "World", nullptr, false, 0
        );

        std::cout << "[Detector] World volume constructed (2x2x2 m, Air)" << std::endl;
        return worldPhys;
    }
};

// --- Main ---
int main() {
    std::cout << "=== Geant4 CMake Test ===" << std::endl;

    G4RunManager* runManager = new G4RunManager();

    runManager->SetUserInitialization(new MinimalDetector());
    runManager->SetUserInitialization(new FTFP_BERT());

    runManager->Initialize();

    std::cout << "=== Success! Geant4 initialized correctly ===" << std::endl;

    delete runManager;
    return 0;
}
