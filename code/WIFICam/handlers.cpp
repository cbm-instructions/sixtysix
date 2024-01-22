#include "WifiCam.hpp"
#include <StreamString.h>


void
serveStill()
{
  auto frame = esp32cam::capture();
  if (frame == nullptr) {
    Serial.println("capture() failure");
    server.send(500, "text/plain", "still capture error\n");
    return;
  }
  Serial.printf("capture() success: %dx%d %zub\n", frame->getWidth(), frame->getHeight(),
                frame->size());

  server.setContentLength(frame->size());
  server.send(200,"image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}

void
addRequestHandlers()
{
  server.on("/", HTTP_GET, [] {
   /* server.setContentLength(sizeof(FRONTPAGE));
    server.send(200, "text/html");
    server.sendContent(FRONTPAGE, sizeof(FRONTPAGE));*/
    long width = 1600;
    long height = 1200;
    String format = "jpg";

    auto res = esp32cam::Camera.listResolutions().find(width, height);
    if (!res.isValid()) {
      
      server.send(404, "text/plain", "non-existent resolution\n");
      return;
    }
    if (res.getWidth() != width || res.getHeight() != height) {
      server.sendHeader("Location",
                        String("/") + res.getWidth() + "x" + res.getHeight() + "." + format);
      server.send(302);
      return;
    }

    if (!esp32cam::Camera.changeResolution(res)) {
      Serial.printf("changeResolution(%ld,%ld) failure\n", width, height);
      server.send(500, "text/plain", "changeResolution error\n");
    }
    Serial.printf("changeResolution(%ld,%ld) success\n", width, height);
    serveStill();


  });

};


