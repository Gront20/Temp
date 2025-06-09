
#pragma once
#include <wayland-client.h>
#include "input-method-unstable-v1-client-protocol.h"

class InputMethod
{
public:
    InputMethod(struct wl_display* display);
    void sendText(const QString& text);

private:
    static void handleActivate(void* data,
                               zwp_input_method_v1* im,
                               zwp_input_method_context_v1* context);

    struct wl_registry* registry = nullptr;
    struct zwp_input_method_v1* input_method = nullptr;
    struct zwp_input_method_context_v1* context = nullptr;
    uint32_t serial = 0;
};
