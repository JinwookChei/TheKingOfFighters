#pragma once

class IoriSkillHandler
    : public SkillHandler
{
 public:
  IoriSkillHandler();
  ~IoriSkillHandler() override;

  bool RegistSkills() override;

  private:
  void GaishikiMutan();

  void ShikiYamiBarai108();

  void HyakushikiOniyaki();

  void ShikiAoiHana127();

  void ShikiYaOtome1211();

  void ActiveUra306shikiShika();

  void Ura306shikiShika();
};
