#pragma once

class ImageEditLevel final
    : public Level {
 public:
  ImageEditLevel();
  ~ImageEditLevel();

void BeginPlay() override;

void Tick(unsigned long long deltaTime) override;

};