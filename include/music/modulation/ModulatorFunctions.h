#pragma once

#include "MelodyParameter.h"

class ModulatorFunctions {
protected:
public:
	static ModulatorFunction * ExpGainMelodyFunction;
	static ModulatorFunction * ExpLossMelodyFunction;
	static ModulatorFunction * LinearIncreaseMelodyFunction;
	static ModulatorFunction * LinearDecreaseMelodyFunction;
	static ModulatorFunction * SinMelodyFunction;
};