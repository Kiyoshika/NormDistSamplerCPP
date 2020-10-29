# NormDistSamplerCPP
An example implementation for creating a Gaussian Random Number generator. Returns a pointer to N doubles (specified by user's size).

# How to use (example):
```c++
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
```
