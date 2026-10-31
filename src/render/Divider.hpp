#pragma once

class Divider {
public:
  void Draw(float fieldWidth, float fieldHeight, int dashCount,
            float offsetX = 0.0f, float offsetY = 0.0f) const;

private:
  static constexpr float widthRatio = 0.005f;
  static constexpr float gapToDashRatio = 0.5f;
};
