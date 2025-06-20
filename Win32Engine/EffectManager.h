#pragma once

struct EffectInfo {
  unsigned long long imageIndex_ = 0;

  unsigned long long effectTag_ = 0;

  std::vector<unsigned int> indices_;

  std::vector<unsigned long long> intervals_;

  bool loop_ = false;

  Color8Bit transColor_;

  void* searchHandle_ = nullptr;
};


class Effect;
class Level;

class EffectManager final {
 public:
  JO_API EffectManager();
  JO_API ~EffectManager();

  JO_API static EffectManager* Instance();

  JO_API bool Initialize();

  JO_API bool RegistEffect(unsigned long long effectTag, unsigned long long imageIndex, unsigned int startIndex, unsigned int endIndex, unsigned long long interval, bool loop, const Color8Bit& transColor);
  											  
  JO_API bool RegistEffect(unsigned long long effectTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, unsigned long long interval, bool loop, const Color8Bit& transColor);
											  
  JO_API bool RegistEffect(unsigned long long effectTag, unsigned long long imageIndex, const std::vector<unsigned int>& indices, const std::vector<unsigned long long> intervals, bool loop, const Color8Bit& transColor);

  JO_API Effect* SpawnEffect(Level* level, unsigned long long effectTag, const Vector& position);

 private:
  HashTable effectTable_;
};
