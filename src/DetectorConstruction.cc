//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Author:
// Jacob E Bickus, 2021
// MIT, NSE
// jbickus@mit.edu
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///////////////////////////////////////////////////////////////////////////////

#include "DetectorConstruction.hh"

extern G4bool detTest;
extern G4bool debug;
extern G4bool run_without_chopper;
extern G4bool IntObjTest;

DetectorConstruction::DetectorConstruction(ChopperSetup* Chopper, Collimator* Collimator, Cargo* Cargo, Linac* Linac)
        : G4VUserDetectorConstruction(),
        chop(Chopper), collimator(Collimator), cargo(Cargo), linac(Linac),
        // Attenuator Properties
        attenuatorState(false), attenuatorState2(false), attenuatorState3(false),
        attenThickness(0.001*mm), attenThickness2(0.001*mm), attenThickness3(0.001*mm),
        attenuatorMat("G4_AIR"), attenuatorMat2("G4_AIR"), attenuatorMat3("G4_AIR"),
        // Water Tank properties
        theAngle(150.0), water_size_x(28*cm), water_size_y(225*cm), water_size_z(30*cm),
        // plexi/tape properties
        plexiThickness(0.18*mm), tapeThick(0.01*cm),
        // PMT Properties
        PMT_rmax(25.4*cm), nPMT(8), pc_mat("GaAsP"),
        // Output Properties
        DetectorViewOnly(false), material_verbose(false), checkOverlaps(true),
        // Messenger
        detectorM(NULL)
{
  if(debug)
    std::cout << "DetectorConstruction::DetectorConstruction -> Initialized!" << std::endl;
    
  detectorM = new DetectorMessenger(this);
  SetDefaultNistMaterials();
}

DetectorConstruction::~DetectorConstruction()
{
  delete detectorM;
}

void DetectorConstruction::SetDefaultNistMaterials()
{
  nist = G4NistManager::Instance();
  air = nist->FindOrBuildMaterial("G4_AIR");
  plexiglass = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
  PMT_mat = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
  teflonTape = nist->FindOrBuildMaterial("G4_TEFLON");
  G4cout << "DetectorConstruction::SetDefaultNistMaterials -> Complete." << G4endl;
}

void DetectorConstruction::ConstructAttenuatorMaterial(G4Material* &attenuator, G4Material* &attenuator2, G4Material* &attenuator3)
{
  attenuator = nist->FindOrBuildMaterial(attenuatorMat);
  attenuator2 = nist->FindOrBuildMaterial(attenuatorMat2);
  attenuator3 = nist->FindOrBuildMaterial(attenuatorMat3);
  G4cout << "DetectorConstruction::ConstructAttenuatorMaterial -> Complete." << G4endl;
}

G4LogicalVolume* DetectorConstruction::ConstructAttenuatorsAndPlexiglass(G4LogicalVolume* logicWorld, G4double container_z_pos, G4Material* attenuator, G4Material* attenuator2, G4Material* attenuator3)
{
  // First Attenuation Layer
  // THIS IS THE MOTHER VOLUME INSIDE WORLD ALL OTHER DETECTOR VOLUMES ARE DAUGHTERS OF THIS VOLUME
  G4Box* solidAttenuator = new G4Box("Attenuator1", water_size_x + attenThickness/2. + attenThickness2/2. + attenThickness3/2., water_size_y + attenThickness/2. + attenThickness2/2. + attenThickness3/2.,
                                     water_size_z + attenThickness/2. + attenThickness2/2. + attenThickness3/2.);
  G4LogicalVolume* logicAttenuator = new G4LogicalVolume(solidAttenuator, attenuator, "Attenuator1");

  if(attenuatorState)
  {
    G4cout << G4endl << "DetectorConstruction::Construct -> Attenuator Information" << G4endl;
    G4cout << "----------------------------------------------------------------------" << G4endl;
    G4cout << "DetectorConstruction::Construct -> Attenuator Thickness set to: " << attenThickness << " mm of " << attenuator->GetName() << G4endl;
  }
  else
  {
    attenuatorState2 = false;
    attenThickness2 = 0.001*mm; // of air
    attenuatorState3 = false;
    attenThickness3 = 0.001*mm; // of air
    G4cout<< "DetectorConstruction::Construct -> Second Attenuator State automatically set to Off."
    << G4endl << "DetectorConstruction::Construct -> Third Attenuator State automatically set to Off." << G4endl;
  }

  DetectorInformation* detInfo = DetectorInformation::Instance();
  water_z_pos = detInfo->getRearCollimatorPosition();
  G4double myangle = (180. - theAngle)*pi/180.;

  water_x_pos = tan(myangle)*(container_z_pos - water_z_pos);

  if(debug)
  {
    std::cout << "DetectorConstruction::ConstructAttenuatorsAndPlexiglass -> Water X Position: " << water_x_pos/(cm) << " cm" << std::endl
    << "DetectorConstruction::ConstructAttenuatorsAndPlexiglass -> Water Z Position: " << water_z_pos/(cm) << " cm" << std::endl;
  }

  G4double detDistance = water_x_pos/sin(myangle) + water_size_z;
  G4RotationMatrix* waterRot = new G4RotationMatrix;
  G4RotationMatrix* waterRot2 = new G4RotationMatrix;

  if(detTest)
  {
    new G4PVPlacement(0, G4ThreeVector(0,0,water_size_z), logicAttenuator,
                      "Attenuator1",logicWorld, false, 0, checkOverlaps);
  }
  else
  {
    waterRot->rotateY((180. - theAngle)*deg);
    waterRot2->rotateY((180. + theAngle)*deg);
    new G4PVPlacement(waterRot,
                      G4ThreeVector(water_x_pos,0,water_z_pos), logicAttenuator,
                      "Attenuator1L", logicWorld, false, 0, checkOverlaps);
    new G4PVPlacement(waterRot2,
                      G4ThreeVector(-1*water_x_pos,0,water_z_pos), logicAttenuator,
                      "Attenuator1R", logicWorld, false, 0, checkOverlaps);
  }

// Option to add second layer of low Z attenuation material

  G4Box* solidSecondAttenuator = new G4Box("Attenuator2", water_size_x + attenThickness2/2. + attenThickness3/2., water_size_y+attenThickness2/2. + attenThickness3/2.,
                                           water_size_z+attenThickness2/2. + attenThickness3/2.);
  G4LogicalVolume* logicSecondAttenuator = new G4LogicalVolume(solidSecondAttenuator, attenuator2, "Attenuator2");
  new G4PVPlacement(0,G4ThreeVector(0,0,0), logicSecondAttenuator, "Attenuator2", logicAttenuator, false, 0, checkOverlaps);

  if(attenuatorState2)
    G4cout << "DetectorConstruction::Construct -> Second Attenuator set to: " << attenThickness2 << " mm of " << attenuator2->GetName() << G4endl;
  else
  {
    attenuatorState3 = false;
    attenThickness3 = 0.001*mm; // of air
    G4cout << "DetectorConstruction::Construct -> Third Attenuator automatically set Off." << G4endl;
  }

  // Make third attenuator layer
  G4Box* solidThirdAttenuator = new G4Box("Attenuator3", water_size_x + attenThickness3/2., water_size_y + attenThickness3/2., water_size_z + attenThickness3/2.);
  G4LogicalVolume* logicThirdAttenuator = new G4LogicalVolume(solidThirdAttenuator, attenuator3, "LastLayerAttenuator3");
  new G4PVPlacement(0,G4ThreeVector(0,0,0), logicThirdAttenuator, "LastLayerAttenuator3", logicSecondAttenuator, false, 0, checkOverlaps);

  if(attenuatorState3)
    G4cout << "DetectorConstruction::Construct -> Third Attenuator set to: " << attenThickness3 << " mm of " << attenuator3->GetName() << G4endl;

// Make Water Casing (Plexiglass)

  G4Box* solidCasing = new G4Box("Plexiglass", water_size_x, water_size_y, water_size_z);
  G4LogicalVolume* logicCasing = new G4LogicalVolume(solidCasing, plexiglass, "Plexiglass");
  new G4PVPlacement(0,G4ThreeVector(0,0,0), logicCasing, "Plexiglass", logicThirdAttenuator, false, 0, checkOverlaps);
  G4cout << G4endl << "DetectorConstruction::Construct -> Water Tank Information" << G4endl;
  G4cout << "----------------------------------------------------------------------" << G4endl;
  if(plexiThickness != 0.18*mm)
  {
    G4cout << "DetectorConstruction::Construct -> Plexiglass Thickness Changed to: "
    << plexiThickness << " mm" << G4endl;
  }

  return logicCasing;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4Material *attenuator, *attenuator2, *attenuator3;

  if(!IntObjTest)
    ConstructAttenuatorMaterial(attenuator, attenuator2, attenuator3);

  G4Element *elO = new G4Element("Oxygen", "O", 8, 16.0*g/mole);
  G4Element *elH = new G4Element("Hydrogen", "H", 1, 1.00794*g/mole);
  // Need to have water built by user for raleigh scattering
  G4Material *Water = new G4Material("Water", 0.99802*g/cm3,2, kStateLiquid,273.15, 1); // Name, density, numComponents, state, Temperature, pressure
  Water->AddElement(elH, 1);
  Water->AddElement(elO, 2);

  // Set up Photocathode materials
  G4Element* elGa = new G4Element("Gallium", "Ga", 31, 69.723*g/mole);
  G4Element* elAs = new G4Element("Arsenic", "As", 33, 74.9216*g/mole);
  G4Element* elP = new G4Element("Phosphorous", "P", 15, 30.973762*g/mole);
  G4Material* GaAsP = new G4Material("GaAsP", 4.138*g/cm3, 3, kStateSolid, 293*kelvin, 1*pow(10,-6)*pascal);
  GaAsP->AddElement(elGa, 1);
  GaAsP->AddElement(elAs, 1);
  GaAsP->AddElement(elP, 1);
  G4Element* elCs = new G4Element("Cesium", "Cs", 55, 132.90545*g/mole);
  G4Element* elK = new G4Element("Potassium", "K", 19, 39.0983*g/mole);
  G4Element* elSb = new G4Element("Antimony", "Sb", 51, 121.76*g/mole);
  G4Material * bialkali = new G4Material("Bialkali", 3.29*g/cm3, 3, kStateSolid, 293*kelvin, 1*pow(10,-6)*pascal);
  bialkali->AddElement(elCs,1);
  bialkali->AddElement(elK,2);
  bialkali->AddElement(elSb,1);

  G4double world_size_x = 2.5*m;
  G4double world_size_y = 2.5*m;
  G4double world_size_z = 2.5*m;

  if(detTest)
  {
   world_size_x = 1.*m;
   world_size_z = 1.*m;
  }
  G4Box* solidWorld = new G4Box("World", world_size_x, world_size_y, world_size_z);

  G4LogicalVolume* logicWorld =
          new G4LogicalVolume(solidWorld, //its solid
                              air, //its material
                              "World"); //its name

  // Make Physical volume ** NEVER CHANGE THIS **
  G4VPhysicalVolume* physWorld =
          new G4PVPlacement(0, //no rotation
                            G4ThreeVector(), //at (0,0,0)
                            logicWorld, //its logical volume
                            "World", //its name
                            0, //its mother  volume
                            false, //no boolean operation
                            0, //copy number
                            false); //overlaps checking

  // ********************************************************** World and Materials Complete ************************************************************//
  // Parameters used later
  DetectorInformation* detInfo = DetectorInformation::Instance();
  G4double bremStartPos = detInfo->GetShiftFactor()/(cm);
  detInfo->setBremStartPosition(bremStartPos);
  G4double container_z_pos = 0;

  detInfo->setContainerZPosition(container_z_pos);
  G4double container_edge_position = container_z_pos - 1.2192*m;
  detInfo->setContainerEdgePosition(container_edge_position);
  G4double linac_size = 4.5*cm;
  detInfo->setLinac_Size(linac_size);
  detInfo->setWaterSizeY(water_size_y);
  detInfo->SetCollimatorSize(50*cm);
  detInfo->setRearCollimatorPosition(-linac_size-150*cm);

  if(!detTest)
  {
    if(!run_without_chopper)
    {
      chop->Construct(logicWorld, checkOverlaps);
      collimator->Construct(logicWorld, checkOverlaps);
    }
    cargo->Construct(logicWorld, checkOverlaps);
    cargo->CheckCargoSphereSize();

  }

// ******************************************************** Begin Detector Construction *************************************************************** //

  if(!IntObjTest)
  {
    G4LogicalVolume* logicCasing = ConstructAttenuatorsAndPlexiglass(logicWorld, container_z_pos, attenuator, attenuator2, attenuator3);
    if(tapeThick != 0.01*cm)
    {
      G4cout << "DetectorConstruction::Construct -> Optical Tape Thickness Changed to: "
      << tapeThick << " cm" << G4endl;
    }

  // Make Teflon tape wrap

    G4VSolid* solidTape = new G4Box("Tape", water_size_x-plexiThickness, water_size_y-plexiThickness, water_size_z-plexiThickness);
    G4LogicalVolume* logicTape = new G4LogicalVolume(solidTape, teflonTape, "Tape");
    physTape = new G4PVPlacement(0,G4ThreeVector(0,0,0), logicTape, "Tape", logicCasing, false, 0, checkOverlaps);

  // Tub of water

    G4cout << "DetectorConstruction::Construct -> Water Tank X: " << water_size_x/(cm)<< " cm" << G4endl;
    G4cout << "DetectorConstruction::Construct -> Water Tank Y: " << water_size_y/(cm)<< " cm" << G4endl;
    G4cout << "DetectorConstruction::Construct -> Water Tank Z: " << water_size_z/(cm) << " cm" << G4endl << G4endl;

    G4Box* solidWater = new G4Box("Water", water_size_x-plexiThickness-tapeThick,
                                  water_size_y-plexiThickness-tapeThick,
                                  water_size_z-plexiThickness-tapeThick);
    G4LogicalVolume* logicWater =
            new G4LogicalVolume(solidWater, //its solid
                                Water, //its material
                                "Water"); //its name

    physWater = new G4PVPlacement(0, //no rotation
                                  G4ThreeVector(0,0,0),
                                  logicWater, //its logical volume
                                  "Water", //its name
                                  logicTape, //its mother logical volume
                                  false, //no boolean operation
                                  0, //copy number
                                  checkOverlaps); //overlaps checking

    // Conduct Final Tank Position Check
    if(!detTest && !debug)
    {
      DefDetPositionConstraintUpper(container_z_pos/(m), water_size_z/(m), water_z_pos/(m));
      DefDetPositionConstraintLeft(water_size_x/(m), water_x_pos/(m), 180. - theAngle, water_size_z/(m));
      DefDetPositionConstraintRight(water_size_x/(m), water_x_pos/(m), 180. - theAngle, water_size_z/(m));
    }

  // **************************************************** End of Water Tank Construction Setup ********************************************************* //


  // ************************************************************** Construct PMTs ********************************************************************* //

    G4cout << G4endl << "DetectorConstruction::Construct -> PC and PMT Information" << G4endl;
    G4cout << "----------------------------------------------------------------------" << G4endl;
    G4double PMT_rmin = 0*cm;
    G4cout << "DetectorConstruction::Construct -> PC Radius: " << PMT_rmax/(cm) << " cm" << G4endl;
    G4double PMT_z = 7.62*cm; // 3 in PMT
    G4Tubs* solidPMT = new G4Tubs("PMT", PMT_rmin, PMT_rmax, PMT_z, 0*deg, 360*deg);
    logicPMT = new G4LogicalVolume(solidPMT, PMT_mat, "PMT");

    G4cout << "The Number of PMTs was set to: " << nPMT << G4endl;
    G4double PMT_y_pos;
    std::vector<G4double> PMT_y_posv;
    if(nPMT>1)
    {
      if((PMT_rmax*2)/(cm) > (water_size_y*2./(cm)/nPMT))
      {
        G4cerr << "DetectorConstruction::Construct -> ERROR Too many PMTs to fit on Water Surface!"
        << G4endl << "DetectorConstruction::Construct -> Water Tank Size: " << water_size_y/(cm) << " cm"
        << G4endl << "DetectorConstruction::Construct -> PMT Diameter: " << (PMT_rmax*2.)/(cm) << " Greater than "
        << (water_size_y/(cm)/nPMT) << G4endl;
        exit(10);
      }
      G4double PMT_y_pos_start = 0. - water_size_y + water_size_y/nPMT;
      PMT_y_posv.push_back(PMT_y_pos_start);
      for(G4int i=1;i<nPMT;++i)
      {
        PMT_y_pos = PMT_y_pos_start + i*(PMT_rmax*2.);
        PMT_y_posv.push_back(PMT_y_pos);

        if(checkOverlaps)
        {
          G4cout << "DetectorConstruction::Construct -> PMT Position " << i
                  << " set to " << PMT_y_posv[i-1]/(cm)<< " cm" << G4endl;
        }
      }
    }
    else
    {
      PMT_y_posv.push_back(0);
    }

    if(detTest)
    {
      for(G4int k=0;k<nPMT;++k)
      {
        new G4PVPlacement(0,
                          G4ThreeVector(0, PMT_y_posv[k], water_size_z - PMT_z - 1.0*cm),
                          logicPMT,
                          "PMT",
                          logicWater,
                          false,
                          k,
                          checkOverlaps);
      }
    }
    else
    {
      for(G4int k=0;k<nPMT;++k)
      {
        new G4PVPlacement(0,
                          G4ThreeVector(0, PMT_y_posv[k], -water_size_z + PMT_z + 1.0*cm),
                          logicPMT,
                          "PMT",
                          logicWater,
                          false,
                          k,
                          checkOverlaps);
      }
    }

  // **************************************************** Construct Photocathode ****************************************************** //

  G4double PC_z = 20*nm;
  G4cout << "DetectorConstruction::Construct -> Photocathode material: " << pc_mat << G4endl << G4endl;
  if(pc_mat == "GaAsP")
  {
    PC_mat = GaAsP;
  }
  else if(pc_mat == "Bialkali")
  {
    PC_mat = bialkali;
  }
  else exit(1);

  G4Tubs* solidPhotoCathode = new G4Tubs("PC", PMT_rmin, PMT_rmax, PC_z, 0*deg, 360.*deg);
  logicPC = new G4LogicalVolume(solidPhotoCathode, PC_mat, "PC");
  G4double PMT_window_thickness = 3*mm;
  physPC = new G4PVPlacement(0,
                       G4ThreeVector(0,0,PMT_z-PMT_window_thickness),
                       logicPC,
                       "PC",
                       logicPMT, // daughter of PMT logical
                       false,
                       0,
                       checkOverlaps);



  //
  // ------------ Generate & Add Material Properties Table ------------
  //

    MaterialProperties* mp = new MaterialProperties();
    G4MaterialPropertiesTable* waterMPT = mp->SetWaterProperties();
    Water->SetMaterialPropertiesTable(waterMPT);

    G4MaterialPropertiesTable* casingMPT = mp->SetCasingProperties();
    G4MaterialPropertiesTable* casingOPMPT = mp->SetCasingOpticalProperties();
    G4OpticalSurface *casing_opsurf = new G4OpticalSurface("casingSurface", glisur, polished, dielectric_dielectric);
    plexiglass->SetMaterialPropertiesTable(casingMPT);
    casing_opsurf->SetMaterialPropertiesTable(casingOPMPT);
    new G4LogicalSkinSurface("casing_surf", logicCasing, casing_opsurf);

    G4MaterialPropertiesTable* tapeMPT = mp->SetTapeProperties();
    G4MaterialPropertiesTable* tapeOPMPT = mp->SetTapeOpticalProperties();
    G4OpticalSurface *tape_opsurf = new G4OpticalSurface("tapeSurface",glisur, polishedfrontpainted, dielectric_dielectric);
    tape_opsurf->SetMaterialPropertiesTable(tapeOPMPT);
    teflonTape->SetMaterialPropertiesTable(tapeMPT);
    new G4LogicalBorderSurface("tape_surf", physWater, physTape, tape_opsurf);

    G4MaterialPropertiesTable* pmtMPT = mp->SetPMTProperties();
    G4MaterialPropertiesTable* pmtOPMPT = mp->SetPMTOpticalProperties();
    G4OpticalSurface* PMT_opsurf = new G4OpticalSurface("PMTSurface",unified,polished,dielectric_metal);
    PMT_mat->SetMaterialPropertiesTable(pmtMPT);
    PMT_opsurf->SetMaterialPropertiesTable(pmtOPMPT);

    G4MaterialPropertiesTable* pc_MPT = mp->SetPCProperties(pc_mat);
    G4OpticalSurface* photocath_opsurf= new G4OpticalSurface("photocath_opsurf");
    photocath_opsurf->SetType(dielectric_metal);
    photocath_opsurf->SetFinish(polished);
    photocath_opsurf->SetPolish(1.0);
    photocath_opsurf->SetModel(glisur);
    photocath_opsurf->SetMaterialPropertiesTable(pc_MPT);

    new G4LogicalSkinSurface("photocath_surf", logicPC, photocath_opsurf); // name, physical volume of surface, phsical volume of world?, G4optical surface
    new G4LogicalSkinSurface("PMT_surf", logicPMT, PMT_opsurf);

    G4MaterialPropertiesTable* airMPT = mp->SetAirProperties();
    air->SetMaterialPropertiesTable(airMPT);

  // Material Verbosity to print materials properties tables
    if(material_verbose)
    {
      G4cout << "Material Verbose set to True/On!" << G4endl;
      G4cout << "Material Properties Table for: " << air->GetName() << G4endl;
      airMPT->DumpTable();
      G4cout << "Material Properties Table for: " << teflonTape->GetName() << G4endl;
      tapeOPMPT->DumpTable();
      G4cout << "Material Properties Table for: " << pc_mat << G4endl;
      pc_MPT->DumpTable();
      G4cout << "Material Properties Table for: " << Water->GetName() << G4endl;
      waterMPT->DumpTable();
      G4cout << "Material Properties Table for: " << plexiglass->GetName() << G4endl;
      casingOPMPT->DumpTable();
    }
  }


//always return the physical World!!!
  if(debug)
    G4cout << "DetectorConstruction::Construct -> Constructed!" << G4endl << G4endl;

  return physWorld;
}
/* ************************************************************************************ */

void DetectorConstruction::DefDetPositionConstraintUpper(double container_z_pos, double water_z, double water_z_pos)
{
  G4double upper_boundary = container_z_pos;
  G4double upper_pos = water_z/2. + water_z_pos;

  if(upper_pos > upper_boundary)
  {
    G4cerr << "DetectorConstruction::DefDetPositionConstraintUpper -> ERROR Upper Boundary Constraint Test Failed."
    << G4endl << "Position: " << upper_pos/(m) << " Greater than Boundary: " << upper_boundary/(m) << G4endl;
    exit(1);
  }
}

void DetectorConstruction::DefDetPositionConstraintLeft(double water_x, double water_x_pos, double angle, double water_z)
{
  G4double left_boundary = -0.3048 - 1e-2; // add 1 cm of wiggle room
  angle = angle*pi/180;
  G4double left_pos = -water_x_pos + (water_x*cos(angle) + water_z*sin(angle));

  if(left_pos > left_boundary)
  {
    G4cerr << "DetectorConstruction::DefDetPositionConstraintLeft -> ERROR Left Boundary Constraint Test Failed."
    << G4endl << "Water Size set to: " << water_x << G4endl << "Water Position set to: " << water_x_pos
    << G4endl << "Position: " << left_pos << " Greater than Boundary: " << left_boundary << G4endl;
    exit(1);
  }
  else
  {
    if(checkOverlaps)
    {
      G4cout << "DetectorConstruction::DefDetPositionConstraintLeft -> Left Boundary Constraint Test Passed."
      << G4endl << "Water Size set to: " << water_x << G4endl << "Water Position set to: " << water_x_pos
      << G4endl << "Position: " << left_pos << " Less than Boundary: " << left_boundary << G4endl;
    }
  }
}

void DetectorConstruction::DefDetPositionConstraintRight(double water_x, double water_x_pos, double angle, double water_z)
{
  G4double right_boundary = 0.3048 + 1e-2; // add 1 cm of wiggle room
  angle = angle*pi/180;
  G4double right_pos = water_x_pos - (water_x*cos(angle) + water_z*sin(angle));

  if(right_pos < right_boundary)
  {
    G4cerr << "DetectorConstruction::DefDetPositionConstraintRight -> ERROR Right Boundary Constraint Test Failed."
    << G4endl << "Water Size set to: " << water_x << G4endl << "Water Position Set to: " << water_x_pos
    << G4endl << "Position: " << right_pos << " Less than Boundary: " << right_boundary << G4endl;
    exit(1);
  }
  else
  {
    if(checkOverlaps)
    {
      G4cout << "DetectorConstruction::DefDetPositionConstraintRight -> Right Boundary Constraint Test Passed."
      << G4endl << "Position: " << right_pos << " Greater than Boundary: " << right_boundary << G4endl;
    }
  }

}
