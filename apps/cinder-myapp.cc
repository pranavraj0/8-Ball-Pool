#include <pool_app.h>

using pool::PoolApp;

void prepareSettings(PoolApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PoolApp, ci::app::RendererGl, prepareSettings);
