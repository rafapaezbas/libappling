#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <uv.h>

#include "../include/appling.h"
#include "fixtures/app.h"

#define EXE "test/fixtures/app/" APPLING_RUNTIME "/" APPLING_TEST_EXE

uv_loop_t *loop;

appling_resolve_t req;
appling_process_t process;

static void
on_resolve (appling_resolve_t *req, int status, const appling_platform_t *platform) {
  appling_link_t link = {
    .key = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc",
    .data = "",
  };

  appling_app_t app = {
    .platform = *platform,
    .exe = EXE,
    .key = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
  };

  int err = appling_launch(loop, &process, &link, &app, NULL);
  assert(err == UV_EINVAL);
}

int
main () {
  loop = uv_default_loop();

  int err = appling_resolve(loop, &req, "test/fixtures", on_resolve);
  assert(err == 0);

  uv_run(loop, UV_RUN_DEFAULT);

  return 0;
}
