#ifndef AI_ANSWER_ARRAY_H
#define AI_ANSWER_ARRAY_H
#include <cstdint>
#include <array>
#include <initializer_list>
#include <algorithm>

namespace AIAnswer {
  template <typename T, std::uint8_t N = 6>
  class array {
   private:
    T sequence[N];
    std::uint8_t pos;
   public:
    std::array<float, 8> probs;
    constexpr array() : sequence{}, pos(0), probs() { }
    constexpr std::uint8_t size() noexcept { return N; }
    constexpr std::uint8_t position() noexcept { return pos; }
    std::int8_t maxProbabilityNumber() noexcept
    {
      auto max_it = std::max_element(probs.begin(), probs.end());
      return static_cast<std::int8_t>(std::distance(probs.begin(), max_it));
    }
    void push_back(const T& value) noexcept
    {
      if(pos >= N)  pos = 0;
      sequence[pos] = value;
      ++pos;
    }

    void push_back(std::initializer_list<T> values) noexcept
    {
      for(auto value : values)
        push_back(value);
    }

    constexpr T at(const std::uint8_t i) noexcept
    {
      return sequence[i];
    }

    constexpr T operator[](const std::uint8_t i) noexcept
    {
      return sequence[i];
    }

    std::int8_t handwriting() noexcept
    {
      if(sequence[0] == cast(0))  addProb(0, 1);
      if(sequence[0] == cast(1))  addProb(2, 3, 4, 5, 6, 7);

      if(sequence[1] == cast(0))  addProb(0, 1, 2, 3, 7);
      if(sequence[1] == cast(1))  addProb(4, 5, 6);

      if(sequence[2] == cast(0))  addProb(1, 3, 5, 7);
      if(sequence[2] == cast(1))  addProb(0, 2, 4, 6);

      if(sequence[3] == cast(0))  addProb(4);
      if(sequence[3] == cast(1))  addProb(0, 1, 2, 3, 5, 6, 7);

      if(sequence[4] == cast(0))  addProb(1, 2, 7);
      if(sequence[4] == cast(1))  addProb(0, 3, 4, 5, 6);

      if(sequence[5] == cast(0))  addProb();
      if(sequence[5] == cast(1))  addProb(1, 2, 3, 4, 5, 6, 7);

      return maxProbabilityNumber();
    }

    std::int8_t digitalNumber() noexcept
    {
      if(sequence[0] == cast(0))  addProb(1, 4);
      if(sequence[0] == cast(1))  addProb(0, 2, 3, 5, 6, 7);

      if(sequence[1] == cast(0))  addProb(0, 1, 7);
      if(sequence[1] == cast(1))  addProb(2, 3, 4, 5, 6);

      if(sequence[2] == cast(0))  addProb(1, 4, 7);
      if(sequence[2] == cast(1))  addProb(0, 2, 3, 5, 6);

      if(sequence[3] == cast(0))  addProb(1, 3, 4, 5, 7);
      if(sequence[3] == cast(1))  addProb(0, 2, 6);

      if(sequence[4] == cast(0))  addProb(5, 6);
      if(sequence[4] == cast(1))  addProb(0, 1, 2, 3, 4, 7);

      if(sequence[5] == cast(0))  addProb(1, 2, 3, 7);
      if(sequence[5] == cast(1))  addProb(0, 4, 5, 6);

      return maxProbabilityNumber();
    }

    constexpr T cast(int i) { return static_cast<T>(i); }

    template <class... Args>
    void addProb(const Args&... args)
    {
      for(int i : std::initializer_list<int>{args...})
        probs[i] += 1.0 / size();
    }

  };
}



#endif
