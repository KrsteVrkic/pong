#pragma once

class Divider {
public:
  void Draw(float fieldWidth, float fieldHeight, int dashCount) const;

private:
  static constexpr float widthRatio = 0.005f;
  static constexpr float gapToDashRatio = 0.5f;
};
