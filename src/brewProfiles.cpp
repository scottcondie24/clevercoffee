#include "brewProfiles.h"

//name,pressure,flow,volume,temperature,weight,exit_flow_under,exit_flow_over,exit_pressure_over,exit_pressure_under,max_flow_or_pressure,max_flow_or_pressure_range,seconds,exit_type,transition, pumpcontrol;
//  0       1       2   3       4           5       6               7               8                   9                       10              11                      12      13         14           15

BrewPhase springLeverPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"infuse", 0, 8.0, 0, 90.0, 0, 0, 0.0, 4.0, 0, 0, 0.0, 20.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, FLOW},
    {"rise and hold", 8.6, 0.0, 0, 90.0, 0, 0, 0, 0, 0, 0, 0.0, 4.0, EXIT_TYPE_NONE, TRANSITION_FAST, PRESSURE},
    {"decline", 6.0, 0.0, 0, 90.0, 0, 0, 0.0, 0.0, 6.0, 0.0, 0.0, 30.0, EXIT_TYPE_PRESSURE_UNDER, TRANSITION_SMOOTH, PRESSURE},
    {"maintain flow", 0.0, 1.5, 0, 90.0, 0, 0, 0, 0, 0, 0.0, 0.0, 30.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
};
const int springLeverPhasesCount = sizeof(springLeverPhases) / sizeof(BrewPhase);

BrewPhase londiniumPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"pause", 0, 0, 0, 88.0, 0, 0, 0, 0, 0, 0.0, 0.0, 1.0, EXIT_TYPE_NONE, TRANSITION_FAST, FLOW},  //wait for weightBrewed to be reset
    {"fill", 0, 8.0, 0, 88.0, 5.0, 0, 0.0, 3.0, 0, 0.0, 0.0, 20.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, FLOW},
    {"infuse", 3.0, 1.7, 0, 88.0, 4.0, 0, 0, 0, 0, 8.5, 5.0, 30.0, EXIT_TYPE_NONE, TRANSITION_FAST, PRESSURE},        //exits at 4g
    //{"pressure ramp", 8.6, 0.0, 0, 88.0, 0, 0, 1.7, 0.0, 0.0, 0.0, 0.0, 2.0, EXIT_TYPE_FLOW_OVER, TRANSITION_SMOOTH, PRESSURE}, //ramp so OPV doesnt immediately open
    //{"pressure", 8.6, 1.7, 0, 88.0, 0, 0, 1.7, 0.0, 0.0, 0.0, 0.0, 60.0, EXIT_TYPE_FLOW_OVER, TRANSITION_SMOOTH, PRESSURE},
    {"maintain flow", 0.0, 1.7, 0, 88.0, 50.0, 0, 0, 0, 0, 8.0, 0.5, 80.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},    //exits at 50g
};
const int londiniumPhasesCount = sizeof(londiniumPhases) / sizeof(BrewPhase);

BrewPhase lightRoastPhases[] = {
    {"fill", 3.5, 0.0, 0, 92.0, 0, 0, 0, 3.0, 0, 0, 0.0, 12.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, PRESSURE},
    {"fill end", 3.0, 0.0, 0, 92.0, 0, 1.0, 0.0, 0.0, 0, 0, 0.0, 12.0, EXIT_TYPE_FLOW_UNDER, TRANSITION_FAST, PRESSURE},
    {"infuse", 1.5, 0.0, 12.0, 90.0, 0, 0, 0, 0, 0, 0, 0.0, 13.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, PRESSURE},
    {"pressure", 10.0, 0.0, 0, 88.0, 0, 0, 0, 8.0, 0, 0.0, 0.0, 6.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, PRESSURE},
    {"extract", 0.0, 3.4, 0, 88.0, 0, 0, 0, 0, 0, 0.0, 0.0, 30.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
};
const int lightRoastPhasesCount = sizeof(lightRoastPhases) / sizeof(BrewPhase);

BrewPhase sixBarEspressoPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"infuse", 0, 8.0, 0, 90.0, 0, 0, 0.0, 4.0, 0, 0, 0.0, 20.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, FLOW},
    {"rise and hold", 6.0, 0.0, 0, 90.0, 0, 0, 0, 0, 0, 0, 0.0, 16.0, EXIT_TYPE_NONE, TRANSITION_FAST, PRESSURE},
    {"decline", 4.0, 0.0, 0, 90.0, 36.0, 0, 0.0, 0.0, 4.0, 0.0, 0.0, 30.0, EXIT_TYPE_PRESSURE_UNDER, TRANSITION_SMOOTH, PRESSURE},
};
const int sixBarEspressoPhasesCount = sizeof(sixBarEspressoPhases) / sizeof(BrewPhase);

BrewPhase bloomingEspressoPhases[] = {
    {"infuse", 0, 4.0, 0, 92.0, 0, 0, 0, 1.0, 0, 0, 0, 23.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, FLOW},
    {"pause", 0, 0, 0, 92.0, 0, 0, 0, 0, 0, 0, 0, 30.0, EXIT_TYPE_NONE, TRANSITION_FAST, FLOW},
    {"ramp", 0, 2.2, 0, 92.0, 0, 0, 0, 0, 0, 0, 0, 5.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
    {"flow", 0, 2.2, 0, 92.0, 0, 0, 0, 0, 0, 0.0, 0.0, 20.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
};
const int bloomingEspressoPhasesCount = sizeof(bloomingEspressoPhases) / sizeof(BrewPhase);

BrewPhase pressurizedBloomPhases[] = {
    {"fill", 0, 8.0, 0, 93.0, 0, 0, 0, 3.0, 0, 0, 0, 15.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_FAST, FLOW},
    {"pressure", 3.0, 0, 0, 93.0, 0, 0.9, 0, 0, 0, 0, 0, 12.0, EXIT_TYPE_FLOW_UNDER, TRANSITION_FAST, PRESSURE},
    {"hold", 0.1, 0, 0, 88.0, 0, 0, 1.0, 0, 0, 0, 0, 6.0, EXIT_TYPE_FLOW_OVER, TRANSITION_FAST, PRESSURE},
    {"pressure", 11.0, 0, 0.0, 88.0, 0, 0, 0.0, 8.8, 0, 0.0, 0.0, 6.0, EXIT_TYPE_PRESSURE_OVER, TRANSITION_SMOOTH, PRESSURE},
    {"extract", 0.0, 3.5, 0.0, 88.0, 0, 0, 0, 0, 0, 0.0, 0.0, 60.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
};
const int pressurizedBloomPhasesCount = sizeof(pressurizedBloomPhases) / sizeof(BrewPhase);

BrewPhase calibrateFlowPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"2.0mL/s", 0, 2.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 8.0, EXIT_TYPE_NONE, TRANSITION_FAST, FLOW},
    {"4.0mL/s", 0, 4.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 8.0, EXIT_TYPE_NONE, TRANSITION_FAST, FLOW},
    {"6.0mL/s", 0, 6.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 8.0, EXIT_TYPE_NONE, TRANSITION_FAST, FLOW},
    {"8.0mL/s", 0, 8.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 8.0, EXIT_TYPE_NONE, TRANSITION_FAST, FLOW},
};
const int calibrateFlowPhasesCount = sizeof(calibrateFlowPhases) / sizeof(BrewPhase);

BrewPhase testRampPhases[] = {
        //0    1   2   3   4    5  6   7    8   9  10  11   12       13                     14               15
    {"increasing flow", 0, 4.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
    {"decreasing flow", 0, 1.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
    {"increasing flow", 0, 6.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
    {"decreasing flow", 0, 0.0, 0, 88.0, 0, 0, 0, 0, 0, 0, 0.6, 4.0, EXIT_TYPE_NONE, TRANSITION_SMOOTH, FLOW},
};
const int testRampPhasesCount = sizeof(testRampPhases) / sizeof(BrewPhase);

BrewRecipe recipes[] = {
    {"springLever", springLeverPhases, springLeverPhasesCount},
    {"londinium", londiniumPhases, londiniumPhasesCount},
    {"lightRoast", lightRoastPhases, lightRoastPhasesCount},
    {"sixBarEspresso", sixBarEspressoPhases, sixBarEspressoPhasesCount},
    {"bloomingEspresso", bloomingEspressoPhases, bloomingEspressoPhasesCount},
    {"pressurizedBloom", pressurizedBloomPhases, pressurizedBloomPhasesCount},
    {"calibrateFlow", calibrateFlowPhases, calibrateFlowPhasesCount},
    {"testRampFlow", testRampPhases, testRampPhasesCount},
};

const int recipesCount = sizeof(recipes) / sizeof(BrewRecipe);


//these recipes could be written like this for better visibility

/*BrewPhase londiniumPhases[] = {
    {
        .name = "pause",
        .pressure = 0,
        .flow = 0,
        .volume = 0,
        .temperature = 88.0,
        .weight = 0,
        .exit_flow_under = 0,
        .exit_flow_over = 0,
        .exit_pressure_over = 0,
        .exit_pressure_under = 0,
        .max_flow_or_pressure = 0,
        .max_flow_or_pressure_range = 0,
        .seconds = 1.0,
        .exit_type = EXIT_TYPE_NONE,
        .transition = TRANSITION_FAST,
        .pump = FLOW,
    },
    {
        .name = "fill",
        .pressure = 0,
        .flow = 8.0,
        .volume = 0,
        .temperature = 88.0,
        .weight = 5.0,
        .exit_flow_under = 0,
        .exit_flow_over = 0.0,
        .exit_pressure_over = 3.0,
        .exit_pressure_under = 0,
        .max_flow_or_pressure = 0,
        .max_flow_or_pressure_range = 0.0,
        .seconds = 20.0,
        .exit_type = EXIT_TYPE_PRESSURE_OVER,
        .transition = TRANSITION_FAST,
        .pump = FLOW,
    },*/