//
// Created by User on 3/03/2023.
//

#include "ParticleSimulatorSettings.h"
#include "Enumerators.h"

ParticleSimulatorSettings::ParticleSimulatorSettings(std::string settingsLocation) {

    FILE* saveFile;
    fopen_s(&saveFile, (settingsLocation).c_str(), "r");

    if (access(settingsLocation.c_str(), F_OK) == 0) {

        //std::cout << "File Exists" << std::endl;
    } else {

        std::cout << "File Doesn't Exists" << std::endl;
        return;
    }

    char simName_[32];
    char collisionPhysicsTypeStr_[32];
    char generationTypeStr_[32];
    char colourTypeStr_[32];

    float gravityX;
    float gravityY;

    int specificColourR;
    int specificColourG;
    int specificColourB;
    int specificColourA;

    int lerpStartColourR;
    int lerpStartColourG;
    int lerpStartColourB;
    int lerpStartColourA;

    int lerpEndColourR;
    int lerpEndColourG;
    int lerpEndColourB;
    int lerpEndColourA;

    float positionRangeX;
    float positionRangeY;
    float positionRangeZ;
    float positionRangeW;

    float velocityRangeX;
    float velocityRangeY;
    float velocityRangeZ;
    float velocityRangeW;

    int sizeRangeX;
    int sizeRangeY;

    int massRangeX;
    int massRangeY;

    float elasticityRangeX;
    float elasticityRangeY;

    float frictionRangeX;
    float frictionRangeY;

    // Write all the settings to the file
    // simName, viewWidth, viewHeight, gravityX, gravityY, collisionPhysicsType, generationType, colourType, physicsSteps, shouldRender,
    // detailedParticles, showImpact, numOfParticles, spawnsPerSecond, gridSpaceCols, gridSpaceRows,
    // specificColour_r, specificColour_g, specificColour_b, specificColour_a,
    // lerpStartCol_r, lerpStartCol_g, lerpStartCol_b, lerpStartCol_a,
    // lerpEndCol_r, lerpEndCol_g, lerpEndCol_b, lerpEndCol_a,
    // positionRangeX1, positionRangeY1, positionRangeX2, positionRangeY2,
    // velocityRangeX1, velocityRangeY1, velocityRangeX2, velocityRangeY2,
    // sizeRangeX, sizeRangeY, massRangeX, massRangeY,
    // elasticityRangeX, elasticityRangeY, frictionRangeX, frictionRangeY
    fscanf_s(saveFile, ParticleSimulatorSettingsFormatIn, simName_, 32, &viewWidth, &viewHeight, &gravityX, &gravityY, collisionPhysicsTypeStr_, 32, generationTypeStr_, 32, colourTypeStr_, 32, &physicsSteps, &shouldRender,
              &detailedParticles, &showImpact, &numOfParticles, &spawnsPerSecond, &gridSpaceCols, &gridSpacesRows,
              &specificColourR, &specificColourG, &specificColourB, &specificColourA,
              &lerpStartColourR, &lerpStartColourG, &lerpStartColourB, &lerpStartColourA,
              &lerpEndColourR, &lerpEndColourG, &lerpEndColourB, &lerpEndColourA,
              &positionRangeX, &positionRangeY, &positionRangeZ, &positionRangeW,
              &velocityRangeX, &velocityRangeY, &velocityRangeZ, &velocityRangeW,
              &sizeRangeX, &sizeRangeY, &massRangeX, &massRangeY,
              &elasticityRangeX, &elasticityRangeY, &frictionRangeX, &frictionRangeY);

    CollisionPhysicsTypes collisionPhysicsType_ = CollisionPhysicsStringToEnum(collisionPhysicsTypeStr_);
    GenerationTypes generationType_ = GenerationTypeStringToEnum(generationTypeStr_);
    ColourTypes colourType_ = ColourTypeStringToEnum(colourTypeStr_);

    simName = simName_;
    gravity.SetPosition(gravityX, gravityY);
    collisionPhysicsType = collisionPhysicsType_;
    generationType = generationType_;
    colourType = colourType_;
    specificColour.SetRGBA(specificColourR, specificColourG, specificColourB, specificColourA);
    lerpStartColour.SetRGBA(lerpStartColourR, lerpStartColourG, lerpStartColourB, lerpStartColourA);
    lerpEndColour.SetRGBA(lerpEndColourR, lerpEndColourG, lerpEndColourB, lerpEndColourA);
    positionRange.SetPosition(positionRangeX, positionRangeY, positionRangeZ, positionRangeW);
    velocityRange.SetPosition(velocityRangeX, velocityRangeY, velocityRangeZ, velocityRangeW);
    sizeRange.SetPosition(sizeRangeX, sizeRangeY);
    massRange.SetPosition(massRangeX, massRangeY);
    elasticityRange.SetPosition(elasticityRangeX, elasticityRangeY);
    frictionRange.SetPosition(frictionRangeX, frictionRangeY);

    fclose(saveFile);
}

void ParticleSimulatorSettings::SaveSimulatorSettings() {

    FILE* saveFile;

    // Determine the path that the exe is being run from
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH);
    std::string currentDirectory = std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/"));
    std::string directory = currentDirectory + "/SimulatorSettings/";

    CreateDirectory(directory.c_str(), NULL);
    fopen_s(&saveFile, (directory + simName + ".txt").c_str(), "w+");

    std::string simName_ = simName;
    std::string collisionPhysicsString = EnumToString(collisionPhysicsType);
    std::string generationTypeString = EnumToString(generationType);
    std::string colourTypeString = EnumToString(colourType);

    simName_.resize(32);
    collisionPhysicsString.resize(32);
    generationTypeString.resize(32);
    colourTypeString.resize(32);

    // Write all the settings to the file
    // simName, viewWidth, viewHeight, gravityX, gravityY, collisionPhysicsType, generationType, colourType, physicsSteps, shouldRender,
    // detailedParticles, showImpact, numOfParticles, spawnsPerSecond, gridSpaceCols, gridSpaceRows,
    // specificColour_r, specificColour_g, specificColour_b, specificColour_a,
    // lerpStartCol_r, lerpStartCol_g, lerpStartCol_b, lerpStartCol_a,
    // lerpEndCol_r, lerpEndCol_g, lerpEndCol_b, lerpEndCol_a,
    // positionRangeX1, positionRangeY1, positionRangeX2, positionRangeY2,
    // velocityRangeX1, velocityRangeY1, velocityRangeX2, velocityRangeY2,
    // sizeRangeX, sizeRangeY, massRangeX, massRangeY,
    // elasticityRangeX, elasticityRangeY, frictionRangeX, frictionRangeY
    fprintf_s(saveFile, ParticleSimulatorSettingsFormatOut, simName.c_str(), viewWidth, viewHeight, gravity.GetX(), gravity.GetY(), collisionPhysicsString.c_str(), generationTypeString.c_str(), colourTypeString.c_str(), physicsSteps, shouldRender,
              detailedParticles, showImpact, numOfParticles, spawnsPerSecond, gridSpaceCols, gridSpacesRows,
              specificColour.GetRed(), specificColour.GetGreen(), specificColour.GetBlue(), specificColour.GetAlpha(),
              lerpStartColour.GetRed(), lerpStartColour.GetGreen(), lerpStartColour.GetBlue(), lerpStartColour.GetAlpha(),
              lerpEndColour.GetRed(), lerpEndColour.GetGreen(), lerpEndColour.GetBlue(), lerpEndColour.GetAlpha(),
              positionRange.GetX(), positionRange.GetY(), positionRange.GetZ(), positionRange.GetW(),
              velocityRange.GetX(), velocityRange.GetY(), velocityRange.GetZ(), velocityRange.GetW(),
              (int)sizeRange.GetX(), (int)sizeRange.GetY(), (int)massRange.GetX(), (int)massRange.GetY(),
              elasticityRange.GetX(), elasticityRange.GetY(), frictionRange.GetX(), frictionRange.GetY());
    fclose(saveFile);
}