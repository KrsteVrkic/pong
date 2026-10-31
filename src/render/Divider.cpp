#include "Divider.hpp"
#include <raylib.h>

void Divider::Draw(float fieldWidth, float fieldHeight, int dashCount) const {
  const float dividerWidth = fieldWidth * widthRatio;
  const float dashHeight =
      fieldHeight / (dashCount + (dashCount - 1) * gapToDashRatio);
  const float dashStep = dashHeight * (1.0f + gapToDashRatio);

  for (int i = 0; i < dashCount; ++i) {
    const float y = i * dashStep;
    DrawRectangleRec(
        Rectangle{fieldWidth / 2.0f - dividerWidth / 2.0f, y,
                  dividerWidth, dashHeight},
        WHITE);
  }
}
