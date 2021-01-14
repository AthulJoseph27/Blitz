#include <unistd.h>
#include <iostream>
#include <sys/ioctl.h>
#include <iomanip>

int argMax(std::vector<double> v)
{
    int index = 0;
    double max = v[0];
    for (int i = 1; i < v.size(); i++)
        if (max < v[i])
        {
            max = v[i];
            index = i;
        }
    return index;
}

int argMin(std::vector<double> v)
{
    int index = 0;
    double min = v[0];
    for (int i = 1; i < v.size(); i++)
        if (min < v[i])
        {
            min = v[i];
            index = i;
        }
    return index;
}

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
    int progress = (int)(fraction * (size.ws_col - 25));
    for (int k = 0; k < progress; k++)
        std::cout << "=";
    for (int k = progress; k < (size.ws_col - 25); k++)
        std::cout << " ";
    std::cout << "] " << std::fixed << std::setprecision(2) << (fraction * 100) << " % \r";
}