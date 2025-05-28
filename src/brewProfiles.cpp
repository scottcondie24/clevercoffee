#include "brewProfiles.h"

//name,pressure,flow,volume,temperature,weight,exit_flow_under,exit_flow_over,exit_pressure_over,exit_pressure_under,max_flow_or_pressure,max_flow_or_pressure_range,seconds,exit_type,transition;
//  0       1       2   3       4           5       6               7               8                   9                       10              11                      12      13         14

BrewPhase calibrateFlowPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"2.0mL/s", 0, 2.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
    {"4.0mL/s", 0, 4.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
    {"6.0mL/s", 0, 6.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
    {"8.0mL/s", 0, 8.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
};
const int calibrateFlowPhasesCount = sizeof(calibrateFlowPhases) / sizeof(BrewPhase);

BrewPhase testRampPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"increasing flow", 0, 4.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
    {"decreasing flow", 0, 1.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
    {"increasing flow", 0, 6.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
    {"decreasing flow", 0, 0.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
};
const int testRampPhasesCount = sizeof(testRampPhases) / sizeof(BrewPhase);

BrewPhase advancedSpringLeverPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"infuse", 0, 8.0, 0, 88.0, 0, 0, 6.0, 6.0, 0, 0, 0.6, 10.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, "flow"},
    {"rise and hold", 9.0, 8.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 3.0, EXIT_TYPE_NONE, TRANSITION_FAST, "pressure"},
    {"decline", 6.0, 8.0, 0, 88.0, 0, 0, 1.2, 11.0, 6.0, 1.5, 0.6, 30.0, EXIT_TYPE_PRESSURE_UNDER, TRANSITION_SMOOTH, "pressure"},
    {"maintain flow", 3.0, 1.5, 0, 88.0, 0, 0, 0, 0, 0, 6.0, 0.6, 30.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
};
const int advancedSpringLeverPhasesCount = sizeof(advancedSpringLeverPhases) / sizeof(BrewPhase);

BrewPhase bestPracticeLightRoastPhases[] = {
    {"Preinfusion fill", 3.0, 6.8, 100.0, 92.0, 0, 0, 1.0, 3.0, 0, 0, 0.6, 12.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, "pressure"},
    {"Preinfusion fill end", 3.0, 6.8, 100.0, 92.0, 0, 1.0, 1.0, 3.0, 0, 0, 0.6, 12.0, EXIT_TYPE_FLOW_UNDER, TRANSITION_FAST, "pressure"},
    {"Preinfusion dripping", 1.5, 6.8, 12.0, 90.0, 0, 0, 0, 0, 0, 0, 0.6, 13.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "pressure"},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE, TRANSITION_NONE, "none"},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE, TRANSITION_NONE, "none"},
};
const int bestPracticeLightRoastPhasesCount = sizeof(bestPracticeLightRoastPhases) / sizeof(BrewPhase);

BrewPhase bloomingEspressoPhases[] = {
    {"preinfusion start", 1.0, 4.0, 500.0, 97.5, 0, 0, 0, 0, 0, 0, 0.6, 2.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE, TRANSITION_NONE, "none"},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE, TRANSITION_NONE, "none"},
    {"ramp", 4.0, 2.2, 500.0, 92.0, 0, 0, 0, 0, 0, 0, 0, 5.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
    {"flat flow", 4.0, 2.2, 500.0, 92.0, 0, 0, 0, 0, 0, 8.6, 0.6, 20.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
    {"reset temperature", 4.0, 0, 500.0, 98.0, 0, 0, 0, 0, 0, 0, 0, 1.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
};
const int bloomingEspressoPhasesCount = sizeof(bloomingEspressoPhases) / sizeof(BrewPhase);

BrewPhase adaptiveV2Phases[] = {
    {"Prefill", 3.0, 8.0, 100.0, 93.0, 0, 0, 0, 0, 0, 0, 0.6, 5.0, EXIT_TYPE_NONE, TRANSITION_FAST, "flow"},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE, TRANSITION_NONE, "none"},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE, TRANSITION_NONE, "none"},
    {"Dripping", 0.1, 6.8, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 6.0, EXIT_TYPE_NONE, TRANSITION_FAST, "pressure"},
    {"Pressurize", 11.0, 0, 100.0, 88.0, 0, 0, 6.0, 8.8, 0, 3.5, 0.6, 6.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_SMOOTH, "pressure"},
    {"Extraction start", 3.0, 1.5, 0, 88.0, 0, 0, 6.0, 0, 0, 9.5, 0.6, 0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, "flow"},
    {"Extraction", 3.0, 3.5, 100.0, 88.0, 0, 0, 0, 0, 0, 9.5, 0.6, 60.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, "flow"},
};
const int adaptiveV2PhasesCount = sizeof(adaptiveV2Phases) / sizeof(BrewPhase);

BrewRecipe recipes[] = {
    {"calibrateFlow", calibrateFlowPhases, calibrateFlowPhasesCount},
    {"testRampFlow", testRampPhases, testRampPhasesCount},
    {"advancedSpringLever", advancedSpringLeverPhases, advancedSpringLeverPhasesCount},
    {"bestPracticeLightRoast", bestPracticeLightRoastPhases, bestPracticeLightRoastPhasesCount},
    {"bloomingEspresso", bloomingEspressoPhases, bloomingEspressoPhasesCount},
    {"adaptiveV2", adaptiveV2Phases, adaptiveV2PhasesCount},
};

const int recipesCount = sizeof(recipes) / sizeof(BrewRecipe);