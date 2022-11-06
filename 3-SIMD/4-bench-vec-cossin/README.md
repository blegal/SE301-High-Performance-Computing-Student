# SE301-High-Performance-Computing
 
## SIMD experiments

### Stage 4 - Are some of you over-clocled ?

We have treated our three usual examples, however we did not deal with Sine and Cosine. This is because cosine and sine functions are not classical SIMD instructions. Some software designers have already done the work for you... You can find their source codes here:

https://github.com/reyoung/avx_mathfun/blob/master/avx_mathfun.h
http://gruntthepeon.free.fr/ssemath/sse_mathfun.h
http://gruntthepeon.free.fr/ssemath/neon_mathfun.h


As we have given you a lot of source code so far, you will write everything here. 

1 - Take the source codes from the previous sections (e.g. OpenMP + SIMD) and modify them in order to compare the performances with your SIMD implementation.

2 - You will also create your own approximation of the cosine and sine functions. For this you can use the function below.

```
inline float mycos(float x) noexcept
{
    constexpr float tp = 1.0f / (2.0f * M_PI);
    x *= tp;
    x -= float(0.25f) + std::floor(x + float(.25f));
    x *= float(16.0f) * (std::abs(x) - float(.50f));
    return x;
}
```

3 - Integrate this approach in your benchmark and compare your performances with the one coming from the source codes you have recovered.

have not become masters of SIMD programming, you have understood the basic concepts. You will not have experienced all the subtleties of the thousands of instructions available, nor tested entire data formats, but you should have enough knowledge to speed up our galaxy collision application.

However, before you tackle this application, there is one last step to take.
