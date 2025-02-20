#include "comparison.h"

void bruteforceCheck() {
    uint32_t nu = 1;
    //uint64_t nu = 1;
    float nuf;
    while (nu != 0) {
        nuf = toFloat(nu);
        //if (isFinite(nuf) != std::isfinite(nuf)) std::cout << nuf << std::endl;
        //if (isInfinity(nuf) != std::isinf(nuf)) std::cout << nuf << std::endl;
        //if (fpclassify(nuf) != std::fpclassify(nuf)) std::cout << nuf << std::endl;
        //if (clamp(nuf, 23.23f, 2343.23423f) != std::clamp(nuf, 23.23f, 2343.23423f)) std::cout << nuf << std::endl;
        if (lessThan(nuf, nuf + FLT_EPSILON) != (nuf < (nuf + FLT_EPSILON))) std::cout << nuf << std::endl;
        nu++;
    }
}

int main()
{
    bruteforceCheck();
    return 0;
}
