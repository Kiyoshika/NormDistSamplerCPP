#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib> // srand for setting seeds
#include <ctime> // ^^

#define PI 3.14159

class NormalDistributionSampler {
    private:
        double mu, sigma, lower_bound, upper_bound;

        double density(double x) {
            // normal pdf
            return (1 / (this->sigma*sqrt(2*PI))) * exp( - 0.5*pow(((x - this->mu) / this->sigma), 2) );
        }
    
    public:
        NormalDistributionSampler(double mu, double sigma) {

            this->mu = mu;
            this->sigma = sigma;

            // consider +/- 5 std deviations which should be plenty to capture > 99% of data in normal distribution
            // note: for non-normal data, could use Chebyshev theorem to get ~99% in general, which would be about 10 std deviations
            // but could probably get away with less tbh...(like 6 std deviations which gives about 97%)
            this->lower_bound = mu - 5*sigma;
            this->upper_bound = mu + 5*sigma;
        }

        double *sample(int num_samples) {

            // take a 2D uniform variable, and check if it's within the range of the normal distribution
            std::default_random_engine reng(time(0)); // time(0) uses current time as seed
            std::uniform_real_distribution<> x_unif(lower_bound, upper_bound);
            // max value for normal distribution will be f(mu)
            std::uniform_real_distribution<> y_unif(0, density(this->mu));

            int current_samples = 0;
            double x, y;

            // allocate dynamic pointer "array" size of num_samples
            double *samples = (double*)malloc(sizeof(double)*num_samples);

            while (current_samples < num_samples) {
                x = x_unif(reng);
                y = y_unif(reng);

                if (y <= density(x)) {
                    samples[current_samples] = x;
                    current_samples += 1;
                }
            }

            return samples;
        }

};

int main() {

    // Sample 10 data points from normal distribution with mean 3.1 and std deviation 1.1
    NormalDistributionSampler nds(3.1, 1.1);
    double *normal_samples = nds.sample(10);

    for (int i = 0; i < 10; ++i) {
        std::cout << normal_samples[i] << std::endl;
    }

    free(normal_samples);

    return 0;
}