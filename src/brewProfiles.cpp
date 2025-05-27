#include "brewProfiles.h"

//name,pressure,flow,volume,temperature,weight,exit_flow_under,exit_flow_over,exit_pressure_over,exit_pressure_under,max_flow_or_pressure,max_flow_or_pressure_range,seconds,exit_type;
//  0       1       2   3       4           5       6               7               8                   9                       10              11                      12      13

BrewPhase advancedSpringLeverPhases[] = {
    {"infuse", 0, 8.0, 0, 88.0, 0, 0, 6.0, 6.0, 0, 0, 0.6, 10.0, EXIT_TYPE_PRESSURE_OVER},
    {"rise and hold", 9.0, 8.0, 0, 88.0, 0, 0, 6.0, 11.0, 0, 0, 0.6, 3.0, EXIT_TYPE_PRESSURE_OVER},
    {"decline", 6.0, 8.0, 0, 88.0, 0, 0, 1.2, 11.0, 6.0, 1.5, 0.6, 30.0, EXIT_TYPE_PRESSURE_UNDER},
    {"maintain flow", 3.0, 1.5, 0, 88.0, 0, 0, 6.0, 11.0, 0, 6.0, 0.6, 30.0, EXIT_TYPE_FLOW_OVER},
};
const int advancedSpringLeverPhasesCount = sizeof(advancedSpringLeverPhases) / sizeof(BrewPhase);

BrewPhase weissAdvancedSpringLeverPhases[] = {
    {"infuse", 0, 8.0, 0, 90.0, 0, 0, 6.0, 6.0, 0, 0, 0.6, 10.0, EXIT_TYPE_PRESSURE_OVER},
    {"rise and hold", 9.0, 8.0, 0, 90.0, 0, 0, 6.0, 11.0, 0, 0, 0.6, 3.0, EXIT_TYPE_PRESSURE_OVER},
    {"decline", 6.0, 8.0, 0, 90.0, 0, 0, 1.2, 11.0, 6.0, 1.5, 0.6, 30.0, EXIT_TYPE_PRESSURE_UNDER},
    {"flow limit", 3.0, 1.5, 0, 90.0, 0, 0, 6.0, 11.0, 0, 6.0, 0.6, 30.0, EXIT_TYPE_FLOW_OVER},
};
const int weissAdvancedSpringLeverPhasesCount = sizeof(weissAdvancedSpringLeverPhases) / sizeof(BrewPhase);

BrewPhase bestPracticeLightRoastPhases[] = {
    {"Preinfusion fill", 3.0, 6.8, 100.0, 92.0, 0, 0, 1.0, 3.0, 0, 0, 0.6, 12.0, EXIT_TYPE_PRESSURE_OVER},
    {"Preinfusion fill end", 3.0, 6.8, 100.0, 92.0, 0, 1.0, 1.0, 3.0, 0, 0, 0.6, 12.0, EXIT_TYPE_FLOW_UNDER},
    {"Preinfusion dripping", 1.5, 6.8, 12.0, 90.0, 0, 0, 1.0, 1.5, 0, 0, 0.6, 13.0, EXIT_TYPE_FLOW_OVER},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE},       //check whats going on here
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE},
};
const int bestPracticeLightRoastPhasesCount = sizeof(bestPracticeLightRoastPhases) / sizeof(BrewPhase);

BrewPhase bloomingEspressoPhases[] = {
    {"preinfusion start", 1.0, 4.0, 500.0, 97.5, 0, 0, 6.0, 4.0, 0, 0, 0.6, 2.0, EXIT_TYPE_PRESSURE_OVER},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE},
    {"", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, EXIT_TYPE_NONE},
    {"ramp", 4.0, 2.2, 500.0, 92.0, 0, 0, 6.0, 11.0, 0, 0, 0, 5.0, EXIT_TYPE_NONE},
    {"flat flow", 4.0, 2.2, 500.0, 92.0, 0, 0, 6.0, 11.0, 0, 8.6, 0.6, 20.0, EXIT_TYPE_NONE},
    {"reset temperature", 4.0, 0, 500.0, 98.0, 0, 0, 6.0, 11.0, 0, 0, 0, 1.0, EXIT_TYPE_NONE},
};
const int bloomingEspressoPhasesCount = sizeof(bloomingEspressoPhases) / sizeof(BrewPhase);

BrewRecipe recipes[] = {
    {"advancedSpringLever", advancedSpringLeverPhases, advancedSpringLeverPhasesCount},
    {"weissAdvancedSpringLever", weissAdvancedSpringLeverPhases, weissAdvancedSpringLeverPhasesCount},
    {"bestPracticeLightRoast", bestPracticeLightRoastPhases, bestPracticeLightRoastPhasesCount},
    {"bloomingEspresso", bloomingEspressoPhases, bloomingEspressoPhasesCount},
};

const int recipesCount = sizeof(recipes) / sizeof(BrewRecipe);