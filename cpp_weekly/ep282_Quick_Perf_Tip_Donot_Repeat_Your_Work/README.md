
# In this tutorial video Jason talks about how writing an efficient code which does not repeats logic may result in better performance

. For more info visit tutorial video: https://www.youtube.com/watch?v=IcoNGRL-K5c&list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&index=283
. For benchmark : 
.Static const version:	https://quick-bench.com/q/6tdzeLsowuUm4IK6m01798k42X4
.constexpr version:	https://quick-bench.com/q/3Ll7b7q0gOl7qSRvLBqKAvrdIZI


# Following is code for benchmark

// ---------------------------------------------------------------------------
// PrimeCPP.cpp : Dave's Garage Prime Sieve in C++
// ---------------------------------------------------------------------------

#include <chrono>
#include <ctime>
#include <iostream>
#include <bitset>
#include <map>
#include <cstring>
#include <cmath>

namespace dave {
class prime_sieve
{
  private:

      int sieveSize = 0;
      unsigned char * rawbits = nullptr;
      const std::map<const int, const int> myDict = 
      {
            { 10 , 1 },                 // Historical data for validating our results - the number of primes
            { 100 , 25 },               // to be found under some limit, such as 168 primes under 1000
            { 1000 , 168 },
            { 10000 , 1229 },
            { 100000 , 9592 },
            { 1000000 , 78498 },
            { 10000000 , 664579 },
            { 100000000 , 5761455 }
      };

      bool validateResults()
      {
          if (myDict.end() == myDict.find(sieveSize))
              return false;
          return myDict.find(sieveSize)->second == countPrimes();
      }

      bool GetBit(unsigned int index)
      {
          if (index % 2 == 0)
              return false;
          index = index / 2;
          return ((rawbits[index / 8]) & (1 << (index % 8))) != 0;
      }

      void ClearBit(unsigned int index)
      {
          if (index % 2 == 0)
          {
              printf("You're setting even bits, which is sub-optimal.\n");
              return;
          }
          index = index / 2;
          rawbits[index / 8] &= ~(1 << (index % 8));
      }

  public:

      prime_sieve(int n)
      {
          sieveSize = n;
          rawbits = (unsigned char *) malloc(n / 8 + 1);
          if (rawbits)
            memset(rawbits, 0xff, n / 8 + 1);
      }

      ~prime_sieve()
      {
          free(rawbits);
      }

      void runSieve()
      {
          int factor = 3;
          int q = sqrt(sieveSize);

          while (factor < q)
          {
              for (int num = factor; num < sieveSize; num++)
              {
                  if (GetBit(num))
                  {
                      factor = num;
                      break;
                  }
              }
              for (int num = factor * 3; num < sieveSize; num += factor * 2)
                  ClearBit(num);
               
              factor += 2;
          }
      }

      void printResults(bool showResults, double duration, int passes)
      {
          if (showResults)
              printf("2, ");

          int count = 1;
          for (int num = 3; num <= sieveSize; num++)
          {
              if (GetBit(num))
              {
                  if (showResults)
                      printf("%d, ", num);
                  count++;
              }
          }

          if (showResults)
              printf("\n");
          
          printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %d, Count: %d, Valid: %d\n", 
                 passes, 
                 duration, 
                 duration / passes, 
                 sieveSize, 
                 count, 
                 validateResults());
      }

      int countPrimes()
      {
          int count = 0;
          for (int i = 0; i < sieveSize; i++)
              if (GetBit(i))
                  count++;
          return count;
      }
};
}

template<typename Key, typename Value, size_t Size>
struct ConstexprMap
{
  std::array<std::pair<Key, Value>, Size> values;

  constexpr auto end() const { return std::end(values); }
  constexpr auto find(const Value v) const { 
    return std::find_if(std::begin(values), std::end(values), 
      [v](const auto value) { return value.first == v; });
  }

};

namespace jason {
class prime_sieve
{
  private:

      int sieveSize = 0;
      unsigned char * rawbits = nullptr;

      static const auto &myDict() {
      static const std::map<const int, const int> dict = 
      {
            { 10 , 1 },                 // Historical data for validating our results - the number of primes
            { 100 , 25 },               // to be found under some limit, such as 168 primes under 1000
            { 1000 , 168 },
            { 10000 , 1229 },
            { 100000 , 9592 },
            { 1000000 , 78498 },
            { 10000000 , 664579 },
            { 100000000 , 5761455 }
      };
      return dict;
      }

      bool validateResults()
      {
          if (myDict().end() == myDict().find(sieveSize))
              return false;
          return myDict().find(sieveSize)->second == countPrimes();
      }

      bool GetBit(unsigned int index)
      {
          if (index % 2 == 0)
              return false;
          index = index / 2;
          return ((rawbits[index / 8]) & (1 << (index % 8))) != 0;
      }

      void ClearBit(unsigned int index)
      {
          if (index % 2 == 0)
          {
              printf("You're setting even bits, which is sub-optimal.\n");
              return;
          }
          index = index / 2;
          rawbits[index / 8] &= ~(1 << (index % 8));
      }

  public:

      prime_sieve(int n)
      {
          sieveSize = n;
          rawbits = (unsigned char *) malloc(n / 8 + 1);
          if (rawbits)
            memset(rawbits, 0xff, n / 8 + 1);
      }

      ~prime_sieve()
      {
          free(rawbits);
      }

      void runSieve()
      {
          int factor = 3;
          int q = sqrt(sieveSize);

          while (factor < q)
          {
              for (int num = factor; num < sieveSize; num++)
              {
                  if (GetBit(num))
                  {
                      factor = num;
                      break;
                  }
              }
              for (int num = factor * 3; num < sieveSize; num += factor * 2)
                  ClearBit(num);
               
              factor += 2;
          }
      }

      void printResults(bool showResults, double duration, int passes)
      {
          if (showResults)
              printf("2, ");

          int count = 1;
          for (int num = 3; num <= sieveSize; num++)
          {
              if (GetBit(num))
              {
                  if (showResults)
                      printf("%d, ", num);
                  count++;
              }
          }

          if (showResults)
              printf("\n");
          
          printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %d, Count: %d, Valid: %d\n", 
                 passes, 
                 duration, 
                 duration / passes, 
                 sieveSize, 
                 count, 
                 validateResults());
      }

      int countPrimes()
      {
          int count = 0;
          for (int i = 0; i < sieveSize; i++)
              if (GetBit(i))
                  count++;
          return count;
      }
};
}



constexpr auto count = 1000000;

static void orig(benchmark::State& state) {
  for (auto _ : state) {
    dave::prime_sieve sieve(1000000);
    sieve.runSieve();
    //benchmark::DoNotOptimize(sieve);
  }
}
BENCHMARK(orig);

static void modified(benchmark::State& state) {
  for (auto _ : state) {
    jason::prime_sieve sieve(1000000);
    sieve.runSieve();
    //benchmark::DoNotOptimize(sieve);
  }
}
BENCHMARK(modified);







template<typename Key, typename Value, size_t Size>
struct ConstexprMap
{
  std::array<std::pair<Key, Value>, Size> values;

  constexpr auto end() const { return std::end(values); }
  constexpr auto find(const Value v) const { 
    return std::find_if(std::begin(values), std::end(values), 
      [v](const auto value) { return value.first == v; });
  }

};

namespace jason {
class prime_sieve
{
  private:

      int sieveSize = 0;
      unsigned char * rawbits = nullptr;

      static const auto &myDict() {
      static constexpr ConstexprMap<const int, const int, 8> dict =  
      //static const std::map<const int, const int> dict = 
      {{
            std::pair{ 10 , 1 },                 // Historical data for validating our results - the number of primes
            std::pair{ 100 , 25 },               // to be found under some limit, such as 168 primes under 1000
            std::pair{ 1000 , 168 },
            std::pair{ 10000 , 1229 },
            std::pair{ 100000 , 9592 },
            std::pair{ 1000000 , 78498 },
            std::pair{ 10000000 , 664579 },
            std::pair{ 100000000 , 5761455 }
      }};
      return dict;
      }

      bool validateResults()
      {
          if (myDict().end() == myDict().find(sieveSize))
              return false;
          return myDict().find(sieveSize)->second == countPrimes();
      }

      bool GetBit(unsigned int index)
      {
          if (index % 2 == 0)
              return false;
          index = index / 2;
          return ((rawbits[index / 8]) & (1 << (index % 8))) != 0;
      }

      void ClearBit(unsigned int index)
      {
          if (index % 2 == 0)
          {
              printf("You're setting even bits, which is sub-optimal.\n");
              return;
          }
          index = index / 2;
          rawbits[index / 8] &= ~(1 << (index % 8));
      }

  public:

      prime_sieve(int n)
      {
          sieveSize = n;
          rawbits = (unsigned char *) malloc(n / 8 + 1);
          if (rawbits)
            memset(rawbits, 0xff, n / 8 + 1);
      }

      ~prime_sieve()
      {
          free(rawbits);
      }

      void runSieve()
      {
          int factor = 3;
          int q = sqrt(sieveSize);

          while (factor < q)
          {
              for (int num = factor; num < sieveSize; num++)
              {
                  if (GetBit(num))
                  {
                      factor = num;
                      break;
                  }
              }
              for (int num = factor * 3; num < sieveSize; num += factor * 2)
                  ClearBit(num);
               
              factor += 2;
          }
      }

      void printResults(bool showResults, double duration, int passes)
      {
          if (showResults)
              printf("2, ");

          int count = 1;
          for (int num = 3; num <= sieveSize; num++)
          {
              if (GetBit(num))
              {
                  if (showResults)
                      printf("%d, ", num);
                  count++;
              }
          }

          if (showResults)
              printf("\n");
          
          printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %d, Count: %d, Valid: %d\n", 
                 passes, 
                 duration, 
                 duration / passes, 
                 sieveSize, 
                 count, 
                 validateResults());
      }

      int countPrimes()
      {
          int count = 0;
          for (int i = 0; i < sieveSize; i++)
              if (GetBit(i))
                  count++;
          return count;
      }
};
}



constexpr auto count = 1000000;


static void modified_constexpr(benchmark::State& state) {
  for (auto _ : state) {
    jason::prime_sieve sieve(1000000);
    sieve.runSieve();
    //benchmark::DoNotOptimize(sieve);
  }
}
BENCHMARK(modified_constexpr);


# END OF FILE
