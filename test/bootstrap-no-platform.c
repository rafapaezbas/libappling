#include <assert.h>
#include <fs.h>
#include <js.h>
#include <stdbool.h>
#include <stdio.h>
#include <uv.h>

#include "../include/appling.h"

uv_loop_t *loop;

fs_unlink_t unlink_req;

appling_bootstrap_t bootstrap_req;

js_platform_t *js;

bool bootstrap_called = false;

static void
on_bootstrap (appling_bootstrap_t *req, int status) {
  int e;

  bootstrap_called = true;

  assert(status == 0);

  e = js_destroy_platform(js);
  assert(e == 0);
}

static void
on_unlink (fs_unlink_t *req, int status) {
  int e;

  (void) status;

  appling_dkey_t dkey = {0xd2, 0x79, 0x67, 0x8a, 0xb0, 0xeb, 0x04, 0xc8, 0xab, 0x19, 0xdb, 0xa0, 0xd2, 0x8f, 0x44, 0xe2, 0x91, 0x69, 0xb7, 0x14, 0x3f, 0xf6, 0x60, 0x6e, 0x67, 0x1d, 0x84, 0x47, 0xaa, 0xba, 0xc9, 0x10};

  e = appling_bootstrap(loop, js, &bootstrap_req, dkey, "test/fixtures/bootstrap/no-platform", on_bootstrap);
  assert(e == 0);
}

int
main () {
  int e;

  loop = uv_default_loop();

  e = js_create_platform(loop, NULL, &js);
  assert(e == 0);

  e = fs_unlink(loop, &unlink_req, "test/fixtures/bootstrap/no-platform/current", on_unlink);
  assert(e == 0);

  e = uv_run(loop, UV_RUN_DEFAULT);
  assert(e == 0);

  assert(bootstrap_called);

  return 0;
}
