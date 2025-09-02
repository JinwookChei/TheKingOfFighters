#pragma once


class ImageLoadTimeCheck final
    : public Level {
 public:
  ImageLoadTimeCheck();

  ~ImageLoadTimeCheck();

  void BeginPlay() override;

  void Tick(unsigned long long deltaTick) override;

};