/*
 * uFRI.h
 *
 *  Created on: 2017.04.08.
 *
 */

#ifndef UFRI_H_
#define UFRI_H_

#include "stdint.h"
#include "stdlib.h"
#include "math.h"

static struct FRI_UNIVERSE *universes;
static struct FRI_RULEBASE *rulebases;

/*The base element for universes is the UNIVERSE_DATA structure, which stores the x and y coordinates of universe.*/
struct FRI_UNIVERSE_DATA {
	float x;
	float y;
};

/*The UNIVERSE_DATA elements are stored in the UNIVERSE structure as array. The data elements must be arranged in ascending order by x value in the UNIVERSE. The other elements of UNIVERSE are size and capacity, which are for dynamic memory handling. The observation is also stored in the UNIVERSE. This data comes from the input sensors linked to the UNIVERSE.*/
struct FRI_UNIVERSE {
	uint16_t size;
	uint16_t capacity;
	struct FRI_UNIVERSE_DATA *uData;
	float observation;
	float observationValue;
};

struct ANTECEDENT {
	struct FRI_UNIVERSE *predicate;
	uint16_t universeDataForAntecedent;
	float distance;
};

/*The RULE structure has got 4 scalar elements where it stores its own capacity and the number of antecedents and stores the order number of the UNIVERSE_DATA elements in the UNIVERSE, which is the consequent. Also stores the rule distance.*/
struct FRI_RULE {
	uint16_t universeDataForConsequent;
	uint16_t numberOfAntecedents;
	uint16_t capacityOfAntecedents;
	struct ANTECEDENT *antecedents;
	float distance;
};

/*The RULEBASE structure stores the following: its own capacity, pointer for UNIVERSE structure (which stands for consequent) an array for the RULES structure.*/
struct FRI_RULEBASE {
	uint16_t numberOfRules;
	uint16_t capacityOfRules;
	struct FRI_UNIVERSE *consequent;
	struct FRI_RULE *rules;
};

/**
 * Set the antecedent part of the rule by pointer.
 param: Pointer to rule
 param: Pointer to Universe which is the predicate
 param: Id of Universe data which is the antecedent
 */
int FRI_addAntecedentToRuleByPtr(
	struct FRI_RULE *rule,
	struct FRI_UNIVERSE *predicate,
	uint16_t universeDataForAntecedent);

/*set the antecedents for the rule function.
param: identifier of rulebase
param: the identifier of rule
param: the identifier of antecedent universe
param: the identifier of UNIVERSE_DATA element in antecedent universe.
*/
int FRI_addAntecedentToRuleById(
	uint16_t idOfRuleBase,
	uint16_t idOfRule,
	uint16_t antecedentUniverse,
	uint16_t m_universeDataForAntecedent);

int FRI_addUniverseDataByPtr(struct FRI_UNIVERSE *destination, float x, float y);

/*The data elements can be added with this function.
param: identifier of universe
param: x data
param y data
*/
int FRI_addUniverseDataById(uint16_t id, float x, float y);

/*
Compute consequents for all RULEBASEs in the system.
*/
void FRI_calculateAllRuleBases();

/*
Compute the desired rulebase only.
param: ID of desired Rulebase
*/
void FRI_calculateRuleBaseById(uint16_t idOfRuleBase);

/*
Clear all data (rulebases and universes) from the knowledge base.
*/
void FRI_clean();

/*To create universes first one must call this function.
param: Number of Universes to create.
*/
int FRI_createUniverseArray(uint16_t numberOfUniverses);

/*
Get the observation which set. Or get the conclusion.
param: The ID of desired Universe.
*/
float FRI_getObservationById(uint16_t idOfUniverse);

struct FRI_UNIVERSE *FRI_getUniverse(uint16_t idOfUniverse);

/*
Initialization with all zeroes.
*/
int FRI_initZ();

/*
Initializes storage.
param Number of universes used by rules (UINT16MAX)
param Number of rulebases (UINT16MAX)
*/
void FRI_init(uint16_t numberOfUniverses, uint16_t numberOfRulebases);

/*
The knowledge base is stored in rulebases. The first step to create a RULEBASE is done with call this function
param: the number of rulebases to create.
*/
void FRI_initRuleBasesArray(uint16_t m_numberOfRuleBases);

void FRI_initRuleBaseByPtr(
	struct FRI_RULEBASE *rulebase,
	uint16_t numberOfRules,
	struct FRI_UNIVERSE *consequentUniverse);

/*
Initialization of a Rulebase
param: the identifier number of UNIVERSE
param: the number of elements of UNIVERSE_DATA
*/
void FRI_initRuleBaseById(uint16_t idOfRuleBase, uint16_t numberOfRules,
	uint16_t idOfConsequentUniverse);

void FRI_initRuleByPtr(
	struct FRI_RULE *rule,
	uint16_t numberOfAntecedents,
	uint16_t consequentData);

/*
Initialize a rule.
param: the identifier of the rulebase
param: the identifier of the rule
param: the number of antecedents (observations)
param: the consequent UNIVERSE_DATA identifier from consequent UNIVERSE.
*/
void FRI_initRuleById(
	uint16_t idOfRuleBase,
	uint16_t idOfRule,
	uint16_t numberOfAntecedents,
	uint16_t consequentData);

int FRI_initUniverseByPtr(struct FRI_UNIVERSE *universe, uint16_t numberOfUniverseData);

/*
Init a Universe
param: ID of Universe
param: Number of data elements.
*/
int FRI_initUniverseById(uint16_t id, uint16_t numberOfUniverseData);

/*
Sets the input data in the universe.
param: Desired Universe
param: The data.
*/
void FRI_setObservationForUniverseByPtr(struct FRI_UNIVERSE *universe,
	float observation);

void FRI_setObservationForUniverseById(uint16_t id, float observation);

/* Add new Universe data element to the last initialized Universe.
Call after FRI_initUniverseById(id, numberOfElements);
The elements must be in ascending order!
param: x coordinate
param y coordinate */
void FRI_addUniverseElement(float x, float y);

/*
Add new Rule to last initialized rulebase.
Call after FRI_initRuleBaseById()
param: Id of element from Universe for consequent
param: number of antecedents
*/
void FRI_addRuleToRulebase(uint16_t consequentUniverseElementID, uint16_t numberOfAntecedents);

/*
Add new Antecedent to last initialized Rule.
Call after FRI_initRuleById() OR FRI_addRuleToRulebase()
param: ID of Universe for Antecedent
param ID of element from Universe
*/
void FRI_addAntecedentToRule(uint16_t antecedentUniverse, uint16_t elementOfUniverseForAntecedent);
#endif /* UFRI_H_ */
/*
Example for rule description:

universe "distance"
"close" 0 0
"mid" 5 2
"far" 10 10
end

universe "range"
"close" 0 0
"mid" 5 2
"far" 10 10
end

universe "speed"
"low" 0 0
"high" 10 10
end

rulebase "speed"
rule
"low" when "distance" is "close" and "range" is "close"
end
rule
"high" when "distance" is "far" and "range" is "mid"
end
end


****************************************************************
Don't mix the initialization methods!
Simplyfied configuration:

FRI_init(3, 1);

FRI_initUniverseById(0,3); //Universe ID: 0
FRI_addUniverseElement(0, 0);
FRI_addUniverseElement(5, 2);
FRI_addUniverseElement(10, 10);

FRI_initUniverseById(1,3); //Universe ID: 1
FRI_addUniverseElement(0, 0);
FRI_addUniverseElement(5, 2);
FRI_addUniverseElement(10, 10);

FRI_initUniverseById(2,3); //Universe ID: 2
FRI_addUniverseElement(0, 0);
FRI_addUniverseElement(10, 10);

FRI_initRuleBaseById(0, 2, 2); //The consequent Universe ID: 2
FRI_addRuleToRulebase(0, 2);
FRI_addAntecedentToRule(0, 0);
FRI_addAntecedentToRule(1, 0);

FRI_addRuleToRulebase(1, 2);
FRI_addAntecedentToRule(0, 2);
FRI_addAntecedentToRule(1, 1);

for (i = 0; i <= 20; i++) {
FRI_setObservationForUniverseById(0, m_observation);
FRI_setObservationForUniverseById(1, m_observation);
m_observation += 0.5;

FRI_calculateAllRuleBases();

printf("**Rulebase: %lf\n\n", FRI_getObservationById(2));
}

**************************************************************************

Example with minimal config:
FRI_initZ();

FRI_createUniverseArray(3);
FRI_initUniverseById(0, 3);
FRI_addUniverseDataById(0, 0, 0);
FRI_addUniverseDataById(0, 5, 2);
FRI_addUniverseDataById(0, 10, 10);

FRI_initUniverseById(1, 3);
FRI_addUniverseDataById(1, 0, 0);
FRI_addUniverseDataById(1, 5, 2);
FRI_addUniverseDataById(1, 10, 10);

FRI_initUniverseById(2, 2);
FRI_addUniverseDataById(2, 0, 0);
FRI_addUniverseDataById(2, 10, 10);

FRI_initRuleBasesArray(1);
FRI_initRuleBaseById(0, 2, 2);
FRI_initRuleById(0, 0, 2, 0);
FRI_addAntecedentToRuleById(0, 0, 0, 0);
FRI_addAntecedentToRuleById(0, 0, 1, 0);

FRI_initRuleById(0, 1, 2, 1);
FRI_addAntecedentToRuleById(0, 1, 0, 2);
FRI_addAntecedentToRuleById(0, 1, 1, 1);

for (i = 0; i <= 20; i++) {
FRI_setObservationForUniverseById(0, m_observation);
FRI_setObservationForUniverseById(1, m_observation);
m_observation += 0.5;

FRI_calculateAllRuleBases();

printf("**Rulebase: %lf\n\n", FRI_getObservationById(2));

***********************************************************


}*/
