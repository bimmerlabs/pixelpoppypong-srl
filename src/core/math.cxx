#include "math.h"
#include "../main.h"

using namespace SRL::Math;
using namespace SRL::Types;
using namespace SRL::Math::Types;

// SRL::Math::Random<int32_t> rng = SRL::Math::Random<int32_t>(15);

// Random<int32_t> rng(99999999); // Create RNG with a seed

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

// #define MY_RANDOM_M             (2147483647)
// #define MY_RANDOM_A             (16807)
// #define MY_RANDOM_Q             (MY_RANDOM_M / MY_RANDOM_A)
// #define MY_RANDOM_R             (MY_RANDOM_M % MY_RANDOM_A)

// int32_t                             my_random_seed = 1;

// int32_t                             my_random(int32_t max)
// {
    // my_random_seed = MY_RANDOM_A * (my_random_seed % MY_RANDOM_Q) - MY_RANDOM_R * (my_random_seed / MY_RANDOM_Q);
    // if (my_random_seed <= 0)
        // my_random_seed += MY_RANDOM_M;
    // return my_random_seed % max + 1;
// }

// int32_t my_random_range(int32_t min, int32_t max) { // replace
    // // DateTime time = DateTime::Now();
    // // Random<int32_t> rng(time.Second());
    // // Random<int32_t> rng(9999999);
    // int32_t number = rnd.GetNumber();
    // // int32_t number = my_random(9999999);
    // return min + (number % ABS(max - min) + 1); // modulus
// }

// // Precomputed sine values
// static const FIXED sineTable[91] = {
    // 0, 1143, 2287, 3429, 4571, 5711, 6850, 7986, 9120,
    // 10252, 11380, 12504, 13625, 14742, 15854, 16961, 18064, 19160,
    // 20251, 21336, 22414, 23486, 24550, 25606, 26655, 27696, 28729,
    // 29752, 30767, 31772, 32767, 33753, 34728, 35693, 36647, 37589,
    // 38521, 39440, 40347, 41243, 42125, 42995, 43852, 44695, 45525,
    // 46340, 47142, 47929, 48702, 49460, 50203, 50931, 51643, 52339,
    // 53019, 53683, 54331, 54963, 55577, 56175, 56755, 57319, 57864,
    // 58393, 58903, 59395, 59870, 60326, 60763, 61183, 61583, 61965,
    // 62328, 62672, 62997, 63302, 63589, 63856, 64103, 64331, 64540,
    // 64729, 64898, 65047, 65176, 65286, 65376, 65446, 65496, 65526,
    // 65536,
// };

// // Function to get sine from the precomputed table
// FIXED my_fixed_sine(int angle) {
    // if (angle <= 90) 
        // return sineTable[angle];
    // else if (angle <= 180) 
        // return sineTable[180 - angle];  // Mirror for 90°-180°
    // else if (angle <= 270) 
        // return -sineTable[angle - 180]; // Negative for 180°-270°
    // else 
        // return -sineTable[360 - angle]; // Negative mirror for 270°-360°
// }