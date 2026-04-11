#include "math.h"
#include "../main.h"

using namespace SRL::Math;
using namespace SRL::Types;
using namespace SRL::Math::Types;

// from danny duarte
uint32_t ApproximateIntegerSqrt(uint32_t value)
{
    // Initial variables for approximation
    uint32_t baseValue = 1;                // Base value used to scale the approximation
    uint32_t estimatedValue = value >> 2; // Initial approximation, roughly value / 4

    // Refine the approximation using bit shifts
    while (baseValue < estimatedValue)
    {
        estimatedValue >>= 1;  // Halve the estimated value
        baseValue <<= 1;      // Double the base value
    }

    // Return the refined approximation
    return baseValue + estimatedValue;
}
