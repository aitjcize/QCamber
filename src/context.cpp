#include "context.h"

#include "code39.h"
#include "context.h"
#include "settings.h"

Context ctx;

Context::Context()
{
  Code39::initPatterns();
  Settings::load("config.ini");

  ctx.bg_color = QColor(SETTINGS->get("Color", "BG").toString());
}
