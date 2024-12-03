/*
 * uFRI.c
 *
 *  Created on: 2017.04.08.
 *
 */

#include "uFRI.h"

const float dimension_sqrt[] = { 1, 1, 1.414213562, 1.732050808, 2, 2.236067977,
		2.449489743, 2.645751311, 2.828427125, 3, 3.16227766, 3.31662479,
		3.464101615, 3.605551275, 3.741657387, 3.872983346, 4, 4.123105626,
		4.242640687, 4.358898944, 4.472135955, 4.582575695, 4.69041576,
		4.795831523, 4.898979486, 5, 5.099019514, 5.196152423, 5.291502622,
		5.385164807, 5.477225575, 5.567764363, 5.656854249, 5.744562647,
		5.830951895, 5.916079783, 6, 6.08276253, 6.164414003, 6.244997998,
		6.32455532, 6.403124237, 6.480740698, 6.557438524, 6.633249581,
		6.708203932, 6.782329983, 6.8556546, 6.92820323, 7, 7.071067812,
		7.141428429, 7.211102551, 7.280109889, 7.348469228, 7.416198487,
		7.483314774, 7.549834435, 7.615773106, 7.681145748, 7.745966692,
		7.810249676, 7.874007874, 7.937253933, 8, 8.062257748, 8.124038405,
		8.185352772, 8.246211251, 8.306623863, 8.366600265, 8.426149773,
		8.485281374, 8.544003745, 8.602325267, 8.660254038, 8.717797887,
		8.774964387, 8.831760866, 8.888194417, 8.94427191, 9, 9.055385138,
		9.110433579, 9.16515139, 9.219544457, 9.273618495, 9.327379053,
		9.38083152, 9.433981132, 9.486832981, 9.539392014, 9.591663047,
		9.643650761, 9.695359715, 9.746794345, 9.797958971, 9.848857802,
		9.899494937, 9.949874371, 10, 10.04987562, 10.09950494, 10.14889157,
		10.19803903, 10.24695077, 10.29563014, 10.34408043, 10.39230485,
		10.44030651, 10.48808848, 10.53565375, 10.58300524, 10.63014581,
		10.67707825, 10.72380529, 10.77032961, 10.81665383, 10.86278049,
		10.90871211, 10.95445115, 11, 11.04536102, 11.09053651, 11.13552873,
		11.18033989, 11.22497216, 11.26942767, 11.3137085, 11.35781669,
		11.40175425, 11.44552314, 11.48912529, 11.53256259, 11.5758369,
		11.61895004, 11.66190379, 11.70469991, 11.74734012, 11.78982612,
		11.83215957, 11.87434209, 11.91637529, 11.95826074, 12, 12.04159458,
		12.08304597, 12.12435565, 12.16552506, 12.20655562, 12.24744871,
		12.28820573, 12.32882801, 12.36931688, 12.40967365, 12.4498996,
		12.489996, 12.52996409, 12.56980509, 12.60952021, 12.64911064,
		12.68857754, 12.72792206, 12.76714533, 12.80624847, 12.84523258,
		12.88409873, 12.92284798, 12.9614814, 13, 13.03840481, 13.07669683,
		13.11487705, 13.15294644, 13.19090596, 13.22875656, 13.26649916,
		13.3041347, 13.34166406, 13.37908816, 13.41640786, 13.45362405,
		13.49073756, 13.52774926, 13.56465997, 13.60147051, 13.6381817,
		13.67479433, 13.7113092, 13.74772708, 13.78404875, 13.82027496,
		13.85640646, 13.89244399, 13.92838828, 13.96424004, 14, 14.03566885,
		14.07124728, 14.10673598, 14.14213562, 14.17744688, 14.2126704,
		14.24780685, 14.28285686, 14.31782106, 14.35270009, 14.38749457,
		14.4222051, 14.45683229, 14.49137675, 14.52583905, 14.56021978,
		14.59451952, 14.62873884, 14.6628783, 14.69693846, 14.73091986,
		14.76482306, 14.79864859, 14.83239697, 14.86606875, 14.89966443,
		14.93318452, 14.96662955, 15, 15.03329638, 15.06651917, 15.09966887,
		15.13274595, 15.16575089, 15.19868415, 15.23154621, 15.26433752,
		15.29705854, 15.32970972, 15.3622915, 15.39480432, 15.42724862,
		15.45962483, 15.49193338, 15.5241747, 15.55634919, 15.58845727,
		15.62049935, 15.65247584, 15.68438714, 15.71623365, 15.74801575,
		15.77973384, 15.8113883, 15.84297952, 15.87450787, 15.90597372,
		15.93737745, 15.96871942
};

static uint16_t numberOfUniverses;
static uint16_t numberOfRuleBases;
static uint16_t lastInitializedUniverse;
static uint16_t lastInitializedRule;
static uint16_t lastInitializedRuleBase;

int FRI_initZ() {
	numberOfUniverses = 0;
	numberOfRuleBases = 0;
	return 0;
}

void FRI_init(uint16_t numberOfUniverses, uint16_t p_numberOfRulebases) {
	FRI_createUniverseArray(numberOfUniverses);
	FRI_initRuleBasesArray(p_numberOfRulebases);


}

float FRI_linear_interpolation(struct FRI_UNIVERSE *universe)
{
	uint16_t i;
	uint16_t selectedIndex = 0;
	for (i = 0; i < universe->size-1; ++i) {
		if (universe->observation >= universe->uData[i].x&&universe->observation <= universe->uData[i+1].x) {
			selectedIndex = i;
			break;
		}


	}
	float m = (universe->uData[selectedIndex + 1].y - universe->uData[selectedIndex].y)
		/ (universe->uData[selectedIndex + 1].x - universe->uData[selectedIndex].x);

	float b = -m * universe->uData[selectedIndex].x + universe->uData[selectedIndex].y;

	return m * universe->observation + b;

}

int FRI_createUniverseArray(uint16_t m_numberOfUniverses) {
	numberOfUniverses = m_numberOfUniverses;
	lastInitializedUniverse = 0;
	universes = calloc(numberOfUniverses, sizeof(struct FRI_UNIVERSE));
	if (universes == NULL) {
		return -1;
	}
	return 0;
}
int FRI_initUniverseByPtr(struct FRI_UNIVERSE *universe, uint16_t numberOfUniverseData) {
	universe->capacity = numberOfUniverseData;
	universe->size = 0;
	universe->uData = calloc(numberOfUniverseData,
		sizeof(struct FRI_UNIVERSE_DATA));
	return 0;
}

int FRI_initUniverseById(uint16_t id, uint16_t numberOfUniverseData) {
	lastInitializedUniverse = id;
	return  FRI_initUniverseByPtr(&universes[id], numberOfUniverseData);
}

int FRI_addUniverseDataByPtr(struct FRI_UNIVERSE *destination, float x, float y) {
	if (destination->size < destination->capacity) {
		destination->uData[destination->size].x = x;
		destination->uData[destination->size].y = y;
		destination->size++;
		return destination->size;
	}
	return -1;
}

int FRI_addUniverseDataById(uint16_t id, float x, float y) {
	return FRI_addUniverseDataByPtr(&universes[id], x, y);
}

void FRI_setObservationForUniverseByPtr(struct FRI_UNIVERSE *universe, float observation) {
	universe->observation = observation;
	universe->observationValue = FRI_linear_interpolation(universe);
}

void FRI_setObservationForUniverseById(uint16_t id, float observation) {
	if (id < numberOfUniverses) {
		FRI_setObservationForUniverseByPtr(&universes[id], observation);
	}
}

void FRI_calculateDistanceForRule(struct FRI_RULE *rule) {
#define RULE_ANTECEDENT_DISTANCE rule->antecedents[i].distance
#define NUMBER_OF_ANTECEDENTS rule->numberOfAntecedents
	//#define OBSERVATION_VALUE rule->antecedents[i].predicate
#define OBSERVATION_VALUE (rule->antecedents[i].predicate)->observationValue
#define ANTECEDENT_UNIVERSE rule->antecedents[i].universeDataForAntecedent
#define ANTECEDENT_VALUE rule->antecedents[i].predicate->uData[ANTECEDENT_UNIVERSE].y
	uint16_t i;
	float distance = 0;
	for (i = 0; i < NUMBER_OF_ANTECEDENTS; ++i) {
		RULE_ANTECEDENT_DISTANCE = fabs(ANTECEDENT_VALUE - OBSERVATION_VALUE);
		distance += RULE_ANTECEDENT_DISTANCE * RULE_ANTECEDENT_DISTANCE;
	}
	if (NUMBER_OF_ANTECEDENTS < 255) {
		rule->distance = sqrtf(distance)
			/ dimension_sqrt[NUMBER_OF_ANTECEDENTS];
	}
	else
	{
		rule->distance = sqrtf(distance)
			/ sqrtf(NUMBER_OF_ANTECEDENTS);
	}
}

void FRI_shepard(struct FRI_RULEBASE *rulebase) {

#define RULEBASE_RULE_SIZE rulebase->numberOfRules
#define RULE_DISTANCE rulebase->rules[i].distance
#define RULE_CONSEQUENT rulebase->rules[i].universeDataForConsequent
#define RULE_CONSEQUENT_Y rulebase->consequent->uData[RULE_CONSEQUENT].y
#define RULEBASE_CONCLUSION rulebase->consequent->observation

	uint16_t i = 0;
	float sumOfWeights = 0;
	//	float sumOfWeightedConsequents = 0;
	float weight = 0;
	uint16_t nExactHits = 0;
	RULEBASE_CONCLUSION = 0;
	//count hits
	for (i = 0; i < RULEBASE_RULE_SIZE; i++)
	{
		if (RULE_DISTANCE == 0) {
			nExactHits++;
			RULEBASE_CONCLUSION += RULE_CONSEQUENT_Y;
		}
	}
	if (nExactHits > 0) {
		RULEBASE_CONCLUSION /= nExactHits;
	}
	else {
		//Shepard interpolation
		for (i = 0; i < RULEBASE_RULE_SIZE; ++i) {
			weight = 1.0f / (RULE_DISTANCE);
			//weight = 1.0 / powf(RULE_DISTANCE,2);
			sumOfWeights += weight;
			RULEBASE_CONCLUSION += weight* (RULE_CONSEQUENT_Y);

		}
		RULEBASE_CONCLUSION /= sumOfWeights;
	}


}

void FRI_initRuleBasesArray(uint16_t m_numberOfRuleBases) {
	numberOfRuleBases = m_numberOfRuleBases;
	lastInitializedRule = 0;
	lastInitializedRuleBase = 0;
	rulebases = calloc(numberOfRuleBases, sizeof(struct FRI_RULEBASE));
}

void FRI_initRuleBaseByPtr(struct FRI_RULEBASE *rulebase, uint16_t capacityOfRules, struct FRI_UNIVERSE *consequentUniverse) {
	rulebase->capacityOfRules = capacityOfRules;
	rulebase->consequent = consequentUniverse;
	rulebase->rules = calloc(capacityOfRules, sizeof(struct FRI_RULE));
}

void FRI_initRuleBaseById(uint16_t idOfRuleBase, uint16_t numberOfRules, uint16_t idOfUniverse) {
	FRI_initRuleBaseByPtr(&rulebases[idOfRuleBase], numberOfRules, &universes[idOfUniverse]);
	lastInitializedRuleBase = idOfRuleBase;
	lastInitializedRule = 0;

}

void FRI_initRuleByPtr(struct FRI_RULE *rule, uint16_t capacityOfAntecedents, uint16_t consequentData) {
	rule->capacityOfAntecedents=capacityOfAntecedents;
	rule->universeDataForConsequent = consequentData;
	rule->antecedents = calloc((capacityOfAntecedents), sizeof(struct ANTECEDENT));

}

void FRI_initRuleById(uint16_t idOfRuleBase, uint16_t idOfRule, uint16_t numberOfAntecedents, uint16_t consequentData) {
	if (rulebases[idOfRuleBase].numberOfRules < rulebases[idOfRuleBase].capacityOfRules) {
		FRI_initRuleByPtr(&rulebases[idOfRuleBase].rules[idOfRule], numberOfAntecedents, consequentData);
		rulebases[idOfRuleBase].numberOfRules++;
		lastInitializedRule = idOfRule;
	}
}

int FRI_addAntecedentToRuleByPtr(struct FRI_RULE *rule, struct FRI_UNIVERSE *m_predicate, uint16_t m_universeDataForAntecedent) {
	int state = 0;

	if(rule->numberOfAntecedents<rule->capacityOfAntecedents)
	{
		rule->antecedents[rule->numberOfAntecedents].predicate = m_predicate;
		rule->antecedents[rule->numberOfAntecedents].universeDataForAntecedent = m_universeDataForAntecedent;
		state = rule->numberOfAntecedents++;
	}
	else {
		state = -1;
	}
	return state;
}

int FRI_addAntecedentToRuleById(uint16_t idOfRuleBase, uint16_t idOfRule, uint16_t idOfAntecedentUniverse, uint16_t m_universeDataForAntecedent) {
	return FRI_addAntecedentToRuleByPtr(&rulebases[idOfRuleBase].rules[idOfRule], &universes[idOfAntecedentUniverse], m_universeDataForAntecedent);
}

float FRI_getObservationById(uint16_t idOfUniverse) {
	if (idOfUniverse < numberOfUniverses) {
		return universes[idOfUniverse].observation;
	}
	else {
		return INT16_MIN;
	}
}

struct FRI_UNIVERSE *FRI_getUniverse(uint16_t idOfUniverse) {
	return &universes[idOfUniverse];
}

void FRI_calculateAllRuleBases() {
	uint16_t i, j;

	for (i = 0; i < numberOfRuleBases; ++i) {
		for (j = 0; j < rulebases[i].numberOfRules; ++j) {
			FRI_calculateDistanceForRule(&rulebases[i].rules[j]);
		}
		FRI_shepard(&rulebases[i]);

	}
}

void FRI_addUniverseElement(float x, float y) {
	FRI_addUniverseDataById(lastInitializedUniverse, x, y);

}

void FRI_addRuleToRulebase(uint16_t consequentUniverseData, uint16_t numberOfAntecedents) {
	FRI_initRuleById(lastInitializedRuleBase, lastInitializedRule, numberOfAntecedents, consequentUniverseData);
	lastInitializedRule++;
}

void FRI_addAntecedentToRule(uint16_t antecedentUniverse, uint16_t elementOfUniverseForAntecedent) {
	FRI_addAntecedentToRuleById(lastInitializedRuleBase, lastInitializedRule-1, antecedentUniverse, elementOfUniverseForAntecedent);
}

void FRI_calculateRuleBaseById(uint16_t idOfRuleBase) {
	uint16_t i;
	for (i = 0; i < rulebases[idOfRuleBase].numberOfRules; ++i) {
		FRI_calculateDistanceForRule(&rulebases[idOfRuleBase].rules[i]);
	}
	FRI_shepard(&rulebases[idOfRuleBase]);
}


void FRI_clean() {
	int i,j;
	for(i=0;i<numberOfUniverses; i++){
			free(universes[i].uData);
	}
	for(i=0;i<numberOfRuleBases; i++){
		for(j=0; j<rulebases[i].numberOfRules;j++){

			free(rulebases[i].rules[j].antecedents);

		}
		free(rulebases[i].rules);
	}

	free(universes);
	free(rulebases);
	numberOfRuleBases = 0;
	numberOfUniverses = 0;
}
