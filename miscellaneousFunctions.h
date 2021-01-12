#include <unistd.h>
#include <iostream>
#include <sys/ioctl.h>
#include <iomanip>

void printProgressBar(long start, long end, long currentIteration)
{

    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    long maxStep = (end - start);

    int i = currentIteration - start;

    std::cout << "[";
    double fraction = ((double)i) / (maxStep - 1);
    if (fraction > 1)
        fraction = 1.00;
    int progress = (int)(fraction * (size.ws_col - 15));

    for (int k = 0; k < progress; k++)
        std::cout << "=";

    std::cout << "] " << std::fixed << std::setprecision(2) << (fraction * 100) << " % \r";
}