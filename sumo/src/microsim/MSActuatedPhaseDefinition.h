#ifndef MSActuatedPhaseDefinition_h
#define MSActuatedPhaseDefinition_h

#include "MSPhaseDefinition.h"
#include <utils/options/OptionsSubSys.h>
#include <utils/options/OptionsCont.h>

/**
 * The definition of a single phase.
 * We moved it out of the main class to allow later template
 * parametrisation.
 */
class MSActuatedPhaseDefinition : public MSPhaseDefinition{
public:
    /// The minimum duration of the phase
    int minDuration;

    /// The maximum duration of the phase
    int maxDuration;

    /// stores the timestep of the last on-switched of the phase
    MSNet::Time _lastSwitch;


    /// constructor
    MSActuatedPhaseDefinition(size_t durationArg,
        const std::bitset<64> &driveMaskArg, const std::bitset<64> &breakMaskArg,
		const std::bitset<64> &yellowMaskArg,
        int minDurationArg, int maxDurationArg)
        : MSPhaseDefinition(durationArg, driveMaskArg,
            breakMaskArg, yellowMaskArg), _lastSwitch(0)
    {
        _lastSwitch = OptionsSubSys::getOptions().getInt("b");
        // defines minDuration
		int minDurationDefault = 10;
		if  (minDurationArg < 0) {
			if (durationArg < minDurationDefault) {
				minDuration = durationArg;
			}
			else {
				minDuration = minDurationDefault;
			}
		}
		else {
			minDuration = minDurationArg;
			}
        // defines maxDuration (maxDuration is only used in MSAcuatedTraffifLight Logic)
		int maxDurationDefault = 30; 
		if  (maxDurationArg < 0 ) {
			if (durationArg > maxDurationDefault) {
				maxDuration = durationArg;
			}
			else {
				maxDuration = maxDurationDefault;
			}
		}
		else {
			maxDuration = maxDurationArg;
			}
    }

    /// destructor
    ~MSActuatedPhaseDefinition() { }

};

#endif
