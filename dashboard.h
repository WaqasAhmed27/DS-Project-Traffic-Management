#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "trafficNetwork.h"
#include "trafficSignal.h"
#include "congestion.h"
#include "roadClosures.h"
#include "EVHandling.h"

#include<fstream>
#include<string>
#include<iostream>

class Dashboard {
public:
    void Simulate();
};

#endif